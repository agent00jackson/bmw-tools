{
  description = "QNX 6.5 ARMv7 LLVM SDK";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-26.05-darwin";
  outputs = { nixpkgs, ... }: let
    eachSystem = nixpkgs.lib.genAttrs [ "aarch64-darwin" "x86_64-darwin" "aarch64-linux" "x86_64-linux" ];
  in {
    packages = eachSystem (system: let pkgs = nixpkgs.legacyPackages.${system}; in rec {
      qnx-sdk = pkgs.callPackage ./package.nix { };
      default = qnx-sdk;
    });
    devShells = eachSystem (system: let pkgs = nixpkgs.legacyPackages.${system}; in {
      default = pkgs.mkShellNoCC {
        packages = [ pkgs.cmake pkgs.ninja pkgs.llvmPackages.clang-unwrapped pkgs.llvmPackages.lld pkgs.llvmPackages.llvm ];
      };
    });
    checks = eachSystem (system: let
      pkgs = nixpkgs.legacyPackages.${system};
      sdk = pkgs.callPackage ./package.nix { };
    in {
      cmake-consumer = pkgs.stdenvNoCC.mkDerivation {
        name = "qnx-sdk-cmake-consumer-check";
        src = ./examples/hello;
        nativeBuildInputs = [ pkgs.cmake pkgs.ninja pkgs.llvmPackages.llvm ];
        cmakeFlags = [ "-DCMAKE_TOOLCHAIN_FILE=${sdk}/share/cmake/QnxSdk/toolchain.cmake" ];
        dontFixup = true;
        installPhase = ''
          llvm-readelf -h -l hello | tee elf.txt
          grep -q 'EXEC (Executable file)' elf.txt
          grep -q '/usr/lib/ldqnx.so.2' elf.txt
          llvm-readelf -h libexample.so | grep -q 'DYN (Shared object file)'
          mkdir -p "$out"
          cp hello libexample.so elf.txt "$out/"
        '';
      };
    });
  };
}
