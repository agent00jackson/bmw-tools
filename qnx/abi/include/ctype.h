// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <bmw_abi.h>
#define _XA 512
#define _XS 256
#define _BB 128
#define _CN 64
#define _DI 32
#define _LO 16
#define _PU 8
#define _SP 4
#define _UP 2
#define _XD 1
BMW_BEGIN_DECLS
int isalnum(int);
int isalpha(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int isblank(int);
int tolower(int);
int toupper(int);
BMW_END_DECLS
#ifdef __cplusplus
namespace std { using ::isalnum; using ::isalpha; using ::iscntrl; using ::isdigit; using ::isgraph; using ::islower; using ::isprint; using ::ispunct; using ::isspace; using ::isupper; using ::isxdigit; using ::isblank; using ::tolower; using ::toupper; }
#endif
