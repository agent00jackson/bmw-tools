// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <bmw_abi.h>
#define RTLD_LAZY 1
#define RTLD_NOW 2
#define RTLD_GLOBAL 0x100
#define RTLD_LOCAL 0x0200
#define RTLD_DEFAULT ((void *)-2)
BMW_BEGIN_DECLS
void *dlopen(const char *,int);
void *dlsym(void *,const char *);
int dlclose(void *);
char *dlerror(void);
BMW_END_DECLS
