record Target(string Group, string File, string OriginalSha256, string Type, string Method, int Offset);

static class Targets
{
    private const string Release = "TesterGUI/bin/Release/";
    public const string KeyFile = Release + "RGKeyPair.snk";
    public static readonly Target[] All =
    [
        new("services", Release + "IstaServicesClient.dll",
            "bfd76403ef52afbac7d64e98e48062eaebc8134bbb896b754051c24df6c295f2",
            "BMW.ISPI.IstaServices.Client.IstaServiceClient`1", "CreateChannelFactory", 0),
        new("services", Release + "IstaServicesController.dll",
            "3a68b28bda4fbbe14408fbe65d8b622c10e6637c07ac85c3d986bcc13a7bc863",
            "BMW.ISPI.IstaServices.Controller.IstaServicesMainClient", "CreateChannelFactory", 0),
        new("services", Release + "IstaServicesHost.exe",
            "56aca046ee070c37c6b7f6bd78a9a861e66c4a2591605632c43e61faff3adff5",
            "BMW.ISPI.IstaServices.Host.IstaServicesProcess", "InitializeServices", 48),
        new("operations", Release + "IstaOperationController.dll",
            "0d72cc7a40c0b770831d48c33129dc009569685d1e6caf1e8f3fb9b6cacfeee7",
            "BMW.ISPI.IstaOperation.Controller.IstaOperationServiceClient", "CreateChannelFactory", 0),
        new("operations", Release + "IstaOperation.exe",
            "fec73448689f03a818c034180f10cfc9aa8e570838e866c8079e928c4bdfa69b",
            "BMW.ISPI.IstaOperation.IstaOperationProcess", "InitializeServices", 30),
        new("psdz", Release + "PsdzServiceClient.dll",
            "cf1b3ede4f1fcbbd05c232633c4c942437c481aac1c759422667f1cba492afec",
            "BMW.Rheingold.Psdz.Client.PsdzServiceClient", ".ctor", 17),
        new("psdz", "PSdZ/hostx64/PsdzServiceHost.exe",
            "78622df4c665056a92dd9b0d5fc560c31770e82130026e55e127222745c870e0",
            "BMW.Rheingold.Psdz.Host.Program", "Main", 602)
    ];

    public static Target[] For(string group)
    {
        if (group == "all")
            return All;
        var targets = All.Where(target => target.Group == group).ToArray();
        return targets.Length > 0 ? targets : throw new ArgumentException($"Unknown patch group: {group}");
    }
}
