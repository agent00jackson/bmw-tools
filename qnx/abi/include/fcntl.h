// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <sys/types.h>
#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_ACCMODE 3
#define O_APPEND 8
#define O_NONBLOCK 128
#define O_CREAT 256
#define O_TRUNC 512
#define O_EXCL 1024
#define O_NOCTTY 2048
#define O_CLOEXEC 8192
#define O_SYNC 32
#define F_DUPFD 0
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4
#define F_GETLK 14
#define F_SETLK 6
#define F_SETLKW 7
#define FD_CLOEXEC 1
#define F_RDLCK 1
#define F_WRLCK 2
#define F_UNLCK 3
BMW_BEGIN_DECLS
int open(const char *,int,...);
int creat(const char *,mode_t);
int fcntl(int,int,...);
BMW_END_DECLS
