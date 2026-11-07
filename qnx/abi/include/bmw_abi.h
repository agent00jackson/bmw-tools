// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
#define BMW_BEGIN_DECLS extern "C" {
#define BMW_END_DECLS }
#else
#define BMW_BEGIN_DECLS
#define BMW_END_DECLS
#endif
#define __SRCVERSION(x)
#define __BEGIN_DECLS BMW_BEGIN_DECLS
#define __END_DECLS BMW_END_DECLS
#define _CSTD
#define _STD_BEGIN namespace std {
#define _STD_END }
#define _C_STD_BEGIN
#define _C_STD_END
#define _Restrict __restrict
#define _Int8t int8_t
#define _Uint8t uint8_t
#define _Int16t int16_t
#define _Uint16t uint16_t
#define _Int32t int32_t
#define _Uint32t uint32_t
#define _Int64t int64_t
#define _Uint64t uint64_t
#define _Intptrt intptr_t
#define _Uintptrt uintptr_t
