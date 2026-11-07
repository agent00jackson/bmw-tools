# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.24)
project(qnx650_armv7_sdk LANGUAGES NONE)
find_program(QNX_CLANG NAMES clang REQUIRED)
find_program(QNX_LLD NAMES ld.lld REQUIRED)
find_program(QNX_AR NAMES llvm-ar REQUIRED)
find_program(QNX_RANLIB NAMES llvm-ranlib REQUIRED)
find_program(QNX_STRIP NAMES llvm-strip REQUIRED)
set(flags --target=armv7-none-eabi -march=armv7-a -marm -mfpu=vfpv3 -mfloat-abi=softfp
  -mno-unaligned-access -fno-short-enums -fno-short-wchar -nostdlibinc -O2 -fPIC
  -fno-stack-protector -fno-builtin -D__QNXNTO__=1 -D__QNX__=1 -D__ARM__=1
  -D__LITTLEENDIAN__=1 -D_QNX_SOURCE -isystem "${CMAKE_CURRENT_SOURCE_DIR}/abi/include")
set(support_objects)
foreach(source support.c memory.S popen.c slog.c start.c start.S)
  set(object "${CMAKE_CURRENT_BINARY_DIR}/runtime/${source}.o")
  add_custom_command(OUTPUT "${object}"
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/runtime"
    COMMAND "${QNX_CLANG}" ${flags} -c "${CMAKE_CURRENT_SOURCE_DIR}/runtime/${source}" -o "${object}"
    DEPENDS "runtime/${source}" VERBATIM)
  if(NOT source MATCHES "^start\\.")
    list(APPEND support_objects "${object}")
  endif()
endforeach()
set(support "${CMAKE_CURRENT_BINARY_DIR}/libqnx-support.a")
set(start "${CMAKE_CURRENT_BINARY_DIR}/crt1.o")
add_custom_command(OUTPUT "${support}"
  COMMAND "${QNX_AR}" rcs "${support}" ${support_objects} DEPENDS ${support_objects} VERBATIM)
add_custom_command(OUTPUT "${start}"
  COMMAND "${QNX_LLD}" -m armelf -r -o "${start}" runtime/start.c.o runtime/start.S.o
  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/runtime/start.c.o" "${CMAKE_CURRENT_BINARY_DIR}/runtime/start.S.o"
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" VERBATIM)
include(cmake/QnxImport.cmake)
qnx_import_manifest("${CMAKE_CURRENT_SOURCE_DIR}/abi/imports/qnx650.json"
  "${CMAKE_CURRENT_BINARY_DIR}/imports" QNX sdk_libraries)
add_custom_target(sdk ALL DEPENDS "${support}" "${start}")
foreach(target IN LISTS sdk_libraries)
  add_dependencies(sdk "${target}")
endforeach()
install(FILES "${support}" "${start}" DESTINATION usr/lib)
install(DIRECTORY abi/include/ third_party/openssl-1.0.1l/include/ third_party/qnx-audio/include/ DESTINATION usr/include)
install(DIRECTORY third_party/libstdc++-4.4.2/include/ DESTINATION usr/include/c++/4.4.2)
file(READ abi/imports/qnx650.json metadata)
string(JSON count LENGTH "${metadata}" libraries)
math(EXPR last "${count} - 1")
foreach(index RANGE 0 ${last})
  string(JSON soname GET "${metadata}" libraries ${index} soname)
  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/imports/${soname}" DESTINATION usr/lib)
endforeach()
configure_file(cmake/toolchain.cmake.in toolchain.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/toolchain.cmake" cmake/QnxRules.cmake
  cmake/QnxSdkConfig.cmake cmake/QnxImport.cmake DESTINATION share/cmake/QnxSdk)
install(FILES LICENSE THIRD_PARTY_NOTICES.md DESTINATION share/licenses/qnx-sdk)
install(FILES third_party/libstdc++-4.4.2/COPYING3 third_party/libstdc++-4.4.2/COPYING.RUNTIME DESTINATION share/licenses/qnx-sdk/libstdc++)
install(FILES third_party/openssl-1.0.1l/LICENSE DESTINATION share/licenses/qnx-sdk/openssl)
install(FILES third_party/qnx-audio/COPYING.LIB third_party/qnx-audio/LICENSE-APACHE-2.0 DESTINATION share/licenses/qnx-sdk/audio)
install(FILES abi/imports/qnx650.json DESTINATION share/qnx-sdk)
