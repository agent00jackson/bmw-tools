/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_STDDEF_H
#define BMW_QNX_STDDEF_H
typedef __SIZE_TYPE__ size_t;
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#ifndef __cplusplus
typedef __WCHAR_TYPE__ wchar_t;
#define NULL ((void *)0)
#else
#define NULL __null
namespace std { using ::size_t; using ::ptrdiff_t; }
#endif
#define offsetof(type, member) __builtin_offsetof(type, member)
#ifndef __SRCVERSION
#define __SRCVERSION(text)
#endif
#endif
