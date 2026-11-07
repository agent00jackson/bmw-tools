// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <time.h>
struct timeval { time_t tv_sec; suseconds_t tv_usec; };
struct timezone { int tz_minuteswest,tz_dsttime; };
struct itimerval { struct timeval it_interval,it_value; };
BMW_BEGIN_DECLS
int gettimeofday(struct timeval *,void *);
int settimeofday(const struct timeval *,const struct timezone *);
BMW_END_DECLS
