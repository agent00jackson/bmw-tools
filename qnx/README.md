# LLVM SDK for QNX 6.5 ARMv7

This directory supplies a CMake-compatible SDK: headers, startup objects,
compiler runtime support, link interfaces and a toolchain file. It requires
no Momentics installation, QNX license file, vendor runtime binaries, Docker,
or Python application builder.

From the `bmw-tools` root:

```sh
nix build path:./qnx#qnx-sdk --out-link result-qnx-sdk
cmake -S /path/to/application -B /path/to/build -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$PWD/result-qnx-sdk/share/cmake/QnxSdk/toolchain.cmake" \
  -DCMAKE_BUILD_TYPE=Release
cmake --build /path/to/build
```

The published standalone flake is available as
`github:agent00jackson/bmw-tools?dir=qnx`. A Nix consumer can import that URL
and select `packages.<system>.qnx-sdk`; this does not require changes to the
repository's root flake.

A normal consumer project can use:

```cmake
cmake_minimum_required(VERSION 3.24)
project(example C CXX)
find_package(QnxSdk CONFIG REQUIRED)
add_executable(example main.cpp)
target_compile_features(example PRIVATE cxx_std_11)
target_link_libraries(example PRIVATE QNX::socket)
```

There is a complete example in `examples/hello`. Run the SDK's independent
C/C++ executable and shared-library checks with:

```sh
nix flake check path:./qnx
```

The SDK itself builds and installs with CMake. Nix supplies host LLVM/LLD,
CMake and Ninja, then packages that CMake installation. The installed
`share/cmake/QnxSdk/toolchain.cmake` points at those host tools. To inspect
or build the SDK directly, enter `nix develop path:./qnx`, then use ordinary
`cmake -S qnx -B /tmp/qnx-sdk-build -G Ninja` from the repository root.

## Scope and target ABI

The current compatibility interfaces cover the QNX 6.5 ARMv7 little-endian
ABI used by NBT Evo: VFPv3 softfp/base PCS, strict alignment, 32-bit enums,
4-byte wchar, old GNU libstdc++ ABI and `/usr/lib/ldqnx.so.2`. They are a
validated subset, not the complete official QNX SDK. An application using
other APIs may require additional independently authored declarations and
link metadata.

CMake lists application sources explicitly. The SDK does not parse QNX
project files, Makefiles, or application source trees. BMW-specific framework
interfaces belong to the consuming application. `QnxImport.cmake` provides
`qnx_import_manifest` for applications that need additional symbol metadata.
The Android Auto checkout uses it for A2I and the BMW app frameworks.

The SDK's `usr/lib/*.so*` files are **link-only interfaces**, not runtime
libraries. Never copy them onto a car or into an application runtime bundle.
They contain traps rather than vendor implementations. Programs use the
real libraries already installed on QNX. The SDK's `crt1.o` and
`libqnx-support.a` contain newly authored startup/runtime code and are linked
into application products.

## Licenses and validation

New SDK code is MIT licensed. Freely licensed GNU C++ headers, OpenSSL
headers and the two audio headers retain their own licenses; see
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md). GNU `vector` was compared
byte-for-byte with the GCC 4.4.2 public release. The QNX audio headers
explicitly carry Apache 2.0 and LGPL 2-or-later notices. Restricted core SDK
headers are replaced by independently written interface declarations.

Reference audits, the 606 ABI fact comparisons, host runtime tests, firmware
import inspection, historical project files and old builds have moved to
`../bmw-tools-private/qnx` (a sibling of the public `bmw-tools` repository).
They are not inputs to this SDK or to consumer builds. The reconstruction
was not a segregated clean-room process.

The independent logging formatter writes the documented QNX 6.5 slog record
format and avoids linking a proprietary static libc implementation:
[QNX slogger interface](https://qnx.com/developers/docs/6.5.0SP1.update/com.qnx.doc.neutrino_utilities/s/slogger.html).
CMake checks validate building/linking; execution on the intended QNX system
is a separate qualification step.
