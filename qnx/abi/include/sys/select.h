// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <sys/time.h>
#define FD_SETSIZE 256
typedef struct { int fds_bits[8]; } fd_set;
#define FD_SET(n,s) ((s)->fds_bits[(unsigned)(n)/32] |= 1u<<((n)%32))
#define FD_CLR(n,s) ((s)->fds_bits[(unsigned)(n)/32] &= ~(1u<<((n)%32)))
#define FD_ISSET(n,s) (((s)->fds_bits[(unsigned)(n)/32] >> ((n)%32)) & 1u)
#define FD_ZERO(s) __builtin_memset((s),0,sizeof(*(s)))
BMW_BEGIN_DECLS
int select(int,fd_set *,fd_set *,fd_set *,struct timeval *);
BMW_END_DECLS
