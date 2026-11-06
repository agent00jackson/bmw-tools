# BMW tools for macOS

[ISTA Mac Patch](ista-mac-patch/README.md) audits and patches supported BMW ISTA installations in CrossOver. It keeps a bundle of original files for rollback.

With Nix flakes enabled, run this from the repository root:

```sh
nix run .#ista-mac-patch
```

Nix supplies the .NET build and runtime dependencies. You'll need your own ISTA installation and CrossOver bottle. See the [ISTA patch guide](ista-mac-patch/README.md) for supported builds, the local security tradeoff, and the apply and restore commands.
