using System.Globalization;
using System.Security.Cryptography;
using System.Text.Json;
using Mono.Cecil;
using Mono.Cecil.Cil;

record PatchEntry(string File, string OriginalSha256, string PatchedSha256);
record Manifest(int Format, string Group, PatchEntry[] Files);
record Replacement(string Destination, string Source, string BeforeHash, string AfterHash);

static class PatchBundle
{
    private const string Binding = "System.ServiceModel.NetNamedPipeBinding";
    private const string SecurityMode = "System.ServiceModel.NetNamedPipeSecurityMode";
    private static readonly JsonSerializerOptions Json = new(JsonSerializerDefaults.Web) { WriteIndented = true };

    public static void Prepare(string root, string bundle, string group)
    {
        var targets = Targets.For(group);
        string relative = Path.GetRelativePath(root, bundle);
        if (relative != ".." && !relative.StartsWith(".." + Path.DirectorySeparatorChar, StringComparison.Ordinal))
            throw new IOException("Choose a bundle directory outside the ISTA installation.");
        if (Directory.Exists(bundle) || File.Exists(bundle))
            throw new IOException("Choose a new bundle directory.");

        foreach (var target in targets)
            Files.RequireHash(Files.Within(root, target.File), target.OriginalSha256);

        string keyPath = Files.Within(root, Targets.KeyFile);
        if (!File.Exists(keyPath))
            throw new FileNotFoundException("The matching signing key is required from your own installation.", keyPath);

        byte[] key = File.ReadAllBytes(keyPath);
        string stage = bundle + "." + Guid.NewGuid().ToString("N") + ".staging";
        try
        {
            Directory.CreateDirectory(stage);
            byte[] publicKey = PublicKeyFromSnk(key);
            var entries = new List<PatchEntry>();
            foreach (var target in targets)
            {
                string original = Path.Combine(stage, "originals", target.File);
                string patched = Path.Combine(stage, "patched", target.File);
                Directory.CreateDirectory(Path.GetDirectoryName(original)!);
                Directory.CreateDirectory(Path.GetDirectoryName(patched)!);
                File.Copy(Files.Within(root, target.File), original);
                Files.RequireHash(original, target.OriginalSha256);
                Patch(original, patched, target, key, publicKey);
                entries.Add(new(target.File, target.OriginalSha256, Files.Hash(patched)));
            }

            var manifest = new Manifest(1, group, entries.ToArray());
            File.WriteAllText(Path.Combine(stage, "manifest.json"), JsonSerializer.Serialize(manifest, Json) + "\n");
            Directory.Move(stage, bundle);
            Console.WriteLine($"Prepared {entries.Count} files and saved their originals in {bundle}");
        }
        finally
        {
            CryptographicOperations.ZeroMemory(key);
            if (Directory.Exists(stage))
                Directory.Delete(stage, recursive: true);
        }
    }

    public static void Install(string root, string bundle, bool restore)
    {
        var manifest = JsonSerializer.Deserialize<Manifest>(
            File.ReadAllText(Files.Within(bundle, "manifest.json")), Json);
        if (manifest is null || manifest.Format != 1 || manifest.Files is null)
            throw new InvalidDataException("Unsupported or incomplete bundle manifest.");
        var targets = Targets.For(manifest.Group);
        var entries = manifest.Files.ToDictionary(entry => entry.File, StringComparer.Ordinal);
        if (entries.Count != targets.Length)
            throw new InvalidDataException("The bundle does not contain a complete patch group.");

        using var installLock = File.Open(Files.Within(root, ".bmw-tools.lock"),
            FileMode.OpenOrCreate, FileAccess.ReadWrite, FileShare.None);

        var replacements = new List<Replacement>();
        foreach (var target in targets)
        {
            if (!entries.TryGetValue(target.File, out var entry) || entry.OriginalSha256 != target.OriginalSha256)
                throw new InvalidDataException($"The bundle does not match the supported original: {target.File}");
            string original = Files.Within(bundle, "originals/" + target.File);
            string patched = Files.Within(bundle, "patched/" + target.File);
            Files.RequireHash(original, entry.OriginalSha256);
            if (!restore)
                Files.RequireHash(patched, entry.PatchedSha256);

            string destination = Files.Within(root, target.File);
            string current = Files.Hash(destination);
            string desired = restore ? entry.OriginalSha256 : entry.PatchedSha256;
            if (current != entry.OriginalSha256 && current != entry.PatchedSha256)
                throw new InvalidDataException($"Refusing to replace a file outside this bundle: {target.File}");
            if (current != desired)
                replacements.Add(new(destination, restore ? original : patched, current, desired));
        }

        if (replacements.Count == 0)
        {
            Console.WriteLine("All files already match the requested state.");
            return;
        }

        ReplaceFiles(replacements);
        Console.WriteLine($"{(restore ? "Restored" : "Applied")} {replacements.Count} files. Keep the bundle for recovery.");
    }

    private static void Patch(string original, string patched, Target target, byte[] key, byte[] publicKey)
    {
        using var assembly = AssemblyDefinition.ReadAssembly(original);
        if (!assembly.Name.PublicKey.SequenceEqual(publicKey))
            throw new InvalidDataException($"Signing key does not match the original assembly: {target.File}");

        var module = assembly.MainModule;
        var method = Files.Types(module.Types).Single(type => type.FullName == target.Type)
            .Methods.Single(method => method.Name == target.Method);
        var instruction = method.Body.Instructions.Single(instruction =>
            instruction.OpCode == OpCodes.Newobj && instruction.Operand is MethodReference member &&
            member.DeclaringType.FullName == Binding && member.Parameters.Count == 0);
        if (instruction.Offset != target.Offset)
            throw new InvalidDataException($"Unexpected constructor offset: {target.File}");

        var oldConstructor = (MethodReference)instruction.Operand;
        var constructor = new MethodReference(".ctor", module.TypeSystem.Void, oldConstructor.DeclaringType)
        {
            HasThis = true,
            CallingConvention = MethodCallingConvention.Default
        };
        constructor.Parameters.Add(new ParameterDefinition(new TypeReference(
            "System.ServiceModel", "NetNamedPipeSecurityMode", module, oldConstructor.DeclaringType.Scope, true)));
        var none = Instruction.Create(OpCodes.Ldc_I4_0);
        method.Body.GetILProcessor().InsertBefore(instruction, none);
        RedirectTargets(method.Body, instruction, none);
        instruction.Operand = module.ImportReference(constructor);

        var expected = MethodBodies(module);
        assembly.Write(patched, new WriterParameters { StrongNameKeyBlob = key });
        using var written = AssemblyDefinition.ReadAssembly(patched);
        if (written.Name.FullName != assembly.Name.FullName ||
            !written.Name.PublicKey.SequenceEqual(publicKey) ||
            (written.MainModule.Attributes & ModuleAttributes.StrongNameSigned) == 0)
            throw new InvalidDataException($"Assembly identity or signing flag changed: {target.File}");

        var actual = MethodBodies(written.MainModule);
        if (actual.Count != expected.Count || expected.Any(pair =>
            !actual.TryGetValue(pair.Key, out var body) || body != pair.Value))
            throw new InvalidDataException($"Written IL differs from the intended patch: {target.File}");

        var writtenMethod = Files.Types(written.MainModule.Types).Single(type => type.FullName == target.Type)
            .Methods.Single(method => method.Name == target.Method);
        var writtenConstructor = writtenMethod.Body.Instructions.Single(item =>
            item.OpCode == OpCodes.Newobj && item.Operand is MethodReference member &&
            member.DeclaringType.FullName == Binding);
        if (writtenConstructor.Previous?.OpCode != OpCodes.Ldc_I4_0 ||
            ((MethodReference)writtenConstructor.Operand).Parameters.Single().ParameterType.FullName != SecurityMode)
            throw new InvalidDataException($"Expected a None binding: {target.File}");
        Console.WriteLine($"Verified {target.File} at IL_{target.Offset:x4} ({actual.Count} method bodies checked)");
    }

    private static void RedirectTargets(MethodBody body, Instruction from, Instruction to)
    {
        foreach (var instruction in body.Instructions)
        {
            if (ReferenceEquals(instruction.Operand, from))
                instruction.Operand = to;
            if (instruction.Operand is Instruction[] branches)
                for (int index = 0; index < branches.Length; index++)
                    if (branches[index] == from)
                        branches[index] = to;
        }
        foreach (var handler in body.ExceptionHandlers)
        {
            if (handler.TryStart == from) handler.TryStart = to;
            if (handler.TryEnd == from) handler.TryEnd = to;
            if (handler.HandlerStart == from) handler.HandlerStart = to;
            if (handler.HandlerEnd == from) handler.HandlerEnd = to;
            if (handler.FilterStart == from) handler.FilterStart = to;
        }
    }

    private static Dictionary<string, string> MethodBodies(ModuleDefinition module) =>
        Files.Types(module.Types).SelectMany(type => type.Methods).ToDictionary(method => method.FullName, Body);

    private static string Body(MethodDefinition method)
    {
        if (!method.HasBody)
            return "no-body";
        var body = method.Body;
        var instructions = body.Instructions;
        string Operand(object? value) => value switch
        {
            null => "",
            Instruction branch => "@" + instructions.IndexOf(branch),
            Instruction[] branches => string.Join(",", branches.Select(Operand)),
            MemberReference member => member.FullName,
            VariableDefinition variable => "local:" + variable.Index,
            ParameterDefinition parameter => "arg:" + parameter.Index,
            IFormattable formattable => formattable.ToString(null, CultureInfo.InvariantCulture) ?? "",
            _ => value.ToString() ?? ""
        };
        return string.Join("\n", instructions.Select(item => item.OpCode.Name + " " + Operand(item.Operand))) +
            "\nlocals:" + string.Join(",", body.Variables.Select(variable => variable.VariableType.FullName)) +
            "\nhandlers:" + string.Join(";", body.ExceptionHandlers.Select(handler =>
                $"{handler.HandlerType}:{Operand(handler.TryStart)}:{Operand(handler.TryEnd)}:" +
                $"{Operand(handler.HandlerStart)}:{Operand(handler.HandlerEnd)}:{Operand(handler.FilterStart)}:{handler.CatchType?.FullName}"));
    }

    private static byte[] PublicKeyFromSnk(byte[] key)
    {
        if (key.Length < 20 || key[0] != 7 || BitConverter.ToUInt32(key, 8) != 0x32415352)
            throw new InvalidDataException("Expected an RSA strong-name key pair in the installation.");
        int modulusBytes = checked((int)BitConverter.ToUInt32(key, 12) / 8);
        if (modulusBytes <= 0 || modulusBytes > key.Length - 20)
            throw new InvalidDataException("Invalid RSA modulus length.");
        byte[] publicKey = new byte[32 + modulusBytes];
        BitConverter.GetBytes(0x2400u).CopyTo(publicKey, 0);
        BitConverter.GetBytes(0x8004u).CopyTo(publicKey, 4);
        BitConverter.GetBytes((uint)(20 + modulusBytes)).CopyTo(publicKey, 8);
        Array.Copy(key, 0, publicKey, 12, 8);
        publicKey[12] = 6;
        BitConverter.GetBytes(0x31415352u).CopyTo(publicKey, 20);
        Array.Copy(key, 12, publicKey, 24, 8 + modulusBytes);
        return publicKey;
    }

    private static void ReplaceFiles(List<Replacement> replacements)
    {
        string tag = ".bmw-tools-" + Guid.NewGuid().ToString("N");
        var staged = new List<(Replacement File, string Before, string After)>();
        var installed = new List<(Replacement File, string Before, string After)>();
        var keep = new HashSet<string>();
        try
        {
            foreach (var file in replacements)
            {
                string before = file.Destination + tag + ".before";
                string after = file.Destination + tag + ".after";
                staged.Add((file, before, after));
                File.Copy(file.Destination, before);
                Files.RequireHash(before, file.BeforeHash);
                File.Copy(file.Source, after);
                Files.RequireHash(after, file.AfterHash);
                if (!OperatingSystem.IsWindows())
                    File.SetUnixFileMode(after, File.GetUnixFileMode(before));
            }

            foreach (var item in staged)
            {
                Files.RequireHash(item.File.Destination, item.File.BeforeHash);
                File.Move(item.After, item.File.Destination, overwrite: true);
                installed.Add(item);
                Files.RequireHash(item.File.Destination, item.File.AfterHash);
            }
        }
        catch
        {
            foreach (var item in installed.AsEnumerable().Reverse())
            {
                try
                {
                    Files.RequireHash(item.File.Destination, item.File.AfterHash);
                    File.Move(item.Before, item.File.Destination, overwrite: true);
                }
                catch (Exception rollbackError)
                {
                    keep.Add(item.Before);
                    Console.Error.WriteLine($"Rollback failed: {rollbackError.Message}. Pre-change copy: {item.Before}");
                }
            }
            throw;
        }
        finally
        {
            foreach (var path in staged.SelectMany(item => new[] { item.Before, item.After }))
            {
                if (keep.Contains(path))
                    continue;
                try { File.Delete(path); }
                catch (IOException error) { Console.Error.WriteLine($"Could not remove {path}: {error.Message}"); }
                catch (UnauthorizedAccessException error) { Console.Error.WriteLine($"Could not remove {path}: {error.Message}"); }
            }
        }
    }
}
