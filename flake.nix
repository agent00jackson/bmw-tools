{
  description = "BMW tools for macOS";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-26.05-darwin";

  outputs = { nixpkgs, ... }: {
    packages = nixpkgs.lib.genAttrs [ "aarch64-darwin" "x86_64-darwin" ] (system: {
      ista-mac-patch = nixpkgs.legacyPackages.${system}.callPackage ./ista-mac-patch/package.nix { };
    });
  };
}
