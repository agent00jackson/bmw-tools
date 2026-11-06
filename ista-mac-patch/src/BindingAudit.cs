using Mono.Cecil;
using Mono.Cecil.Cil;

static class BindingAudit
{
    private static readonly HashSet<string> BindingTypes = new()
    {
        "System.ServiceModel.NetNamedPipeBinding",
        "System.ServiceModel.NetTcpBinding",
        "System.ServiceModel.Channels.WindowsStreamSecurityBindingElement",
        "System.ServiceModel.Channels.SslStreamSecurityBindingElement"
    };

    public static int Run(string root)
    {
        int candidates = 0, managed = 0, sites = 0, errors = 0;
        var options = new EnumerationOptions
        {
            RecurseSubdirectories = true,
            AttributesToSkip = FileAttributes.ReparsePoint,
            IgnoreInaccessible = false
        };
        foreach (var path in Directory.EnumerateFiles(root, "*", options).Order(StringComparer.Ordinal))
        {
            if (Path.GetExtension(path).ToLowerInvariant() is not (".dll" or ".exe"))
                continue;
            candidates++;
            try
            {
                using var assembly = AssemblyDefinition.ReadAssembly(path);
                managed++;
                foreach (var method in Files.Types(assembly.MainModule.Types).SelectMany(type => type.Methods))
                {
                    if (!method.HasBody)
                        continue;
                    foreach (var instruction in method.Body.Instructions)
                    {
                        if (instruction.Operand is not MethodReference member)
                            continue;
                        bool constructor = instruction.OpCode == OpCodes.Newobj &&
                            BindingTypes.Contains(member.DeclaringType.FullName);
                        bool securityMode = member.Name == "set_Mode" &&
                            member.DeclaringType.Namespace.StartsWith("System.ServiceModel", StringComparison.Ordinal) &&
                            member.DeclaringType.Name.Contains("Security", StringComparison.Ordinal);
                        if (!constructor && !securityMode)
                            continue;
                        sites++;
                        string mode = instruction.Previous?.OpCode == OpCodes.Ldc_I4_0 &&
                            member.Parameters.Count == 1 &&
                            member.Parameters[0].ParameterType.FullName == "System.ServiceModel.NetNamedPipeSecurityMode"
                            ? " [None]" : "";
                        Console.WriteLine($"{Path.GetRelativePath(root, path)} | {method.FullName} IL_{instruction.Offset:x4} | {member.FullName}{mode}");
                    }
                }
            }
            catch (BadImageFormatException)
            {
                // Native DLLs and EXEs do not have readable CLR assembly metadata.
            }
            catch (Exception error) when (error is not OutOfMemoryException)
            {
                errors++;
                Console.Error.WriteLine($"{Path.GetRelativePath(root, path)}: {error.Message}");
            }
        }
        Console.WriteLine($"Scanned {candidates} DLL/EXE files, read {managed} managed assemblies, found {sites} binding/security sites, {errors} scan errors.");
        return errors == 0 ? 0 : 1;
    }
}
