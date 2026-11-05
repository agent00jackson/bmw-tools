using System.Security.Cryptography;
using Mono.Cecil;

try
{
    switch (args)
    {
        case ["audit", var root]:
            return BindingAudit.Run(Path.GetFullPath(root));
        case ["prepare", var root, var bundle]:
            PatchBundle.Prepare(Path.GetFullPath(root), Path.TrimEndingDirectorySeparator(Path.GetFullPath(bundle)), "all");
            break;
        case ["prepare", var root, var bundle, var group]:
            PatchBundle.Prepare(Path.GetFullPath(root), Path.TrimEndingDirectorySeparator(Path.GetFullPath(bundle)), group);
            break;
        case ["apply" or "restore", var root, var bundle]:
            PatchBundle.Install(Path.GetFullPath(root), Path.TrimEndingDirectorySeparator(Path.GetFullPath(bundle)), args[0] == "restore");
            break;
        default:
            Console.Error.WriteLine("""
                Usage:
                  bmw-tools audit <ista-root>
                  bmw-tools prepare <ista-root> <new-bundle-dir> [all|services|operations|psdz]
                  bmw-tools apply <ista-root> <bundle-dir>
                  bmw-tools restore <ista-root> <bundle-dir>
                """);
            return args is ["--help"] ? 0 : 2;
    }
    return 0;
}
catch (Exception error)
{
    Console.Error.WriteLine(error.Message);
    return 1;
}

static class Files
{
    public static string Hash(string path)
    {
        using var input = File.OpenRead(path);
        return Convert.ToHexString(SHA256.HashData(input)).ToLowerInvariant();
    }

    public static void RequireHash(string path, string expected)
    {
        var actual = Hash(path);
        if (actual != expected)
            throw new InvalidDataException($"Unexpected SHA-256 for {path}. Expected {expected}, got {actual}.");
    }

    // Relative paths are from the built-in target list or a fixed bundle layout.
    public static string Within(string root, string relative)
    {
        var path = root;
        foreach (var part in relative.Split('/'))
        {
            path = Path.Combine(path, part);
            if (new FileInfo(path).LinkTarget is not null)
                throw new IOException($"Refusing to follow a symlink inside {root}: {path}");
        }
        return path;
    }

    public static IEnumerable<TypeDefinition> Types(IEnumerable<TypeDefinition> types)
    {
        foreach (var type in types)
        {
            yield return type;
            foreach (var nested in Types(type.NestedTypes))
                yield return nested;
        }
    }
}
