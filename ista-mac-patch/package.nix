{ lib, buildDotnetModule, dotnetCorePackages }:

buildDotnetModule {
  pname = "ista-mac-patch";
  version = "0.1.0";

  src = lib.fileset.toSource {
    root = ./src;
    fileset = lib.fileset.unions [
      ./src/BindingAudit.cs
      ./src/BmwTools.csproj
      ./src/PatchBundle.cs
      ./src/Program.cs
      ./src/Targets.cs
    ];
  };

  projectFile = "BmwTools.csproj";
  nugetDeps = ./deps.json;
  dotnet-sdk = dotnetCorePackages.sdk_9_0-bin;
  executables = [ "ista-mac-patch" ];

  meta = {
    description = "Local named-pipe compatibility patcher for BMW ISTA under CrossOver";
    mainProgram = "ista-mac-patch";
    platforms = lib.platforms.darwin;
  };
}
