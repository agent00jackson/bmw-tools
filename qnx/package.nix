{ stdenvNoCC, lib, cmake, ninja, llvmPackages }:
stdenvNoCC.mkDerivation {
  pname = "qnx650-armv7-sdk";
  version = "0.1.0";
  src = lib.cleanSourceWith {
    src = ./.;
    filter = path: type: !(builtins.elem (baseNameOf path) [ "build" "result" "__pycache__" ]);
  };
  nativeBuildInputs = [ cmake ninja llvmPackages.clang-unwrapped llvmPackages.lld llvmPackages.llvm ];
  dontFixup = true; # Target ELF objects and import libraries must never be host-patched.
  meta = {
    description = "LLVM CMake SDK for the QNX 6.5 ARMv7 compatibility ABI";
    platforms = lib.platforms.unix;
  };
}
