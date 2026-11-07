// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <bmw_abi.h>
typedef int32_t ssize_t;
typedef int32_t pid_t;
typedef int32_t uid_t;
typedef int32_t gid_t;
typedef unsigned mode_t;
typedef unsigned dev_t;
typedef unsigned nlink_t;
typedef unsigned blksize_t;
typedef unsigned time_t;
typedef unsigned clock_t;
typedef int clockid_t;
typedef int timer_t;
typedef unsigned useconds_t;
typedef int suseconds_t;
typedef int32_t pthread_t;
typedef unsigned socklen_t;
typedef unsigned char sa_family_t;
#if _FILE_OFFSET_BITS == 64
typedef int64_t off_t;
typedef uint64_t ino_t;
typedef uint64_t blkcnt_t;
#else
typedef int32_t off_t;
typedef uint32_t ino_t;
typedef uint32_t blkcnt_t;
#endif
typedef int64_t off64_t;
typedef uint64_t ino64_t;
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef char *caddr_t;
