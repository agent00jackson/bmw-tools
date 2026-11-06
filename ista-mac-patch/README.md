# ISTA Mac Patch

This tool applies a local IPC compatibility patch to a supported BMW ISTA installation in CrossOver. It also audits the full ISTA directory for WCF binding sites.

The patch changes selected WCF named-pipe bindings to `NetNamedPipeSecurityMode.None` on both ends of each channel. This avoids the SSPI negotiation failure seen with CrossOver's Wine runtime. It disables authentication, signing, and encryption on those local channels. Apply it only to an installation you control and keep the original-file bundle.

## Requirements

- An existing CrossOver bottle with ISTA and Windows .NET Framework 4.8.
- Nix with flakes enabled on macOS. The flake pins the .NET SDK and runtime, and the package pins the Mono.Cecil download by hash.
- ISTA 4.52.40 with the exact original binary hashes listed in [Targets.cs](src/Targets.cs). The patcher checks the files even when the reported version matches.
- The matching `RGKeyPair.snk` already present in your own ISTA installation under `TesterGUI/bin/Release`. The patcher reads it locally to preserve the assemblies' strong-name identity.

The repository contains source code and build instructions. Keep your BMW binaries, keys, logs, and generated patch bundles private. The only NuGet dependency is [Mono.Cecil 0.11.6](https://www.nuget.org/packages/Mono.Cecil/0.11.6).

## CrossOver bottle software inventory

The following entries were shown in CrossOver's Installed Software details for the reference bottle. Repeated entries across the screenshots are listed once. CrossOver clipped the Visual C++ names; the two entries are the x86 and x64 Microsoft Visual C++ 2015 (14.0) Redistributables.

- Microsoft .NET Framework 2.0
- Microsoft .NET Framework 2.0 Service Pack 2
- Microsoft .NET Framework 4.0
- Microsoft .NET Framework 4.5
- Microsoft .NET Framework 4.5.2
- Microsoft .NET Framework 4.6.2
- Microsoft .NET Framework 4.8
- Microsoft Visual C++ 2015 (14.0) Redistributable (x86)
- Microsoft Visual C++ 2015 (14.0) Redistributable (x64)
- CrossOver HTML engine
- Microsoft Rich Edit 4.1 (`Msftedit.dll`)
- Microsoft Rich Edit 2.0
- `msls31`
- Microsoft Edge WebView2 Runtime
- Microsoft .NET Runtime 9.0.0 (x64)
- E-Sys 3.27.1 (build 44813)
- E-Sys Launcher Premium
- BMW Group ISTA

This is the reference bottle's inventory, not a clean-bottle prerequisite list. The verified ISTA setup uses native Microsoft .NET Framework 4.8; the other entries document what was installed in this bottle and have not each been isolated as requirements.

## Prepare and apply

Run these commands from the repository root. Change `BMW` to the name of your bottle and adjust the installation path if needed.

```sh
ISTA_ROOT="$HOME/Library/Application Support/CrossOver/Bottles/BMW/drive_c/EC-Apps/ISTA"
PATCH_BUNDLE="$HOME/Documents/ista-4.52.40-patch-bundle"

nix run .#ista-mac-patch -- audit "$ISTA_ROOT"
nix run .#ista-mac-patch -- prepare "$ISTA_ROOT" "$PATCH_BUNDLE"
```

`prepare` creates a new bundle containing a manifest, original copies, and patched copies. It verifies the original SHA-256 hashes, constructor locations, signing identity, and written method bodies. Review the manifest before applying the bundle you generated locally.

Quit ISTA and stop its helpers in CrossOver before changing files. Then apply the bundle.

```sh
nix run .#ista-mac-patch -- apply "$ISTA_ROOT" "$PATCH_BUNDLE"
```

Reopen ISTA and test startup, VIN entry, or the feature that hit the SSPI error. The patcher supports `services`, `operations`, and `psdz` as optional final arguments to `prepare` if you want to patch one complete group. The default is `all`.

| Group | Files | Scope |
|---|---|---|
| `services` | `IstaServicesClient.dll`, `IstaServicesController.dll`, `IstaServicesHost.exe` | Main application startup |
| `operations` | `IstaOperationController.dll`, `IstaOperation.exe` | VIN and vehicle operations |
| `psdz` | `PsdzServiceClient.dll`, `PSdZ/hostx64/PsdzServiceHost.exe` | The 64-bit PSdZ helper |

To audit other builds, use `audit` by itself. It recursively inspects managed DLLs and EXEs for direct binding constructors and explicit security mode changes. An audit hit is a candidate for investigation. A client and its matching server must agree on transport security. The 32-bit PSdZ host, FSC validation, IDES, and launcher communication are outside the patch profiles.

## Restore

Quit ISTA and stop its helpers again before restoring the original files.

```sh
nix run .#ista-mac-patch -- restore "$ISTA_ROOT" "$PATCH_BUNDLE"
```

Keep the bundle until you no longer need rollback. Apply and restore check the whole group before replacing binaries. They accept the exact original and patched hashes from that bundle, including a mix after an interrupted operation. If ISTA has been updated, use the hashes to identify what changed before trying to restore an old bundle.

## Separate CrossOver issues

If ISTA responds to clicks but leaves a dismissed dialog painted on screen, try the WPF software rendering setting in that bottle. Set the DWORD `HKCU\Software\Microsoft\Avalon.Graphics\DisableHWAcceleration` to `1` and restart ISTA. Record the previous value before changing it. [Microsoft WPF graphics settings](https://learn.microsoft.com/en-us/dotnet/desktop/wpf/graphics-multimedia/graphics-rendering-registry-settings)

For a direct cable connection, check that ISTA's saved device type is ENET and macOS routes the vehicle IP through the Ethernet adapter. The vehicle IP and interface name depend on your setup. VIN enrichment through BMW online services also depends on backend access.

The original investigation verified startup and VIN operation creation in CrossOver 26.3. The PSdZ pair addresses a confirmed local SSPI error. Full vehicle readout and programming remain unverified.
