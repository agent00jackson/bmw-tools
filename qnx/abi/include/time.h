// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <sys/types.h>
struct timespec { time_t tv_sec; long tv_nsec; };
struct tm { int tm_sec,tm_min,tm_hour,tm_mday,tm_mon,tm_year,tm_wday,tm_yday,tm_isdst; long tm_gmtoff; const char *tm_zone; };
#define CLOCK_REALTIME 0
#define CLOCK_SOFTTIME 1
#define CLOCK_MONOTONIC 2
#define CLOCKS_PER_SEC 1000000
#define TIMER_ABSTIME 0x80000000
BMW_BEGIN_DECLS
time_t time(time_t *);
clock_t clock(void);
double difftime(time_t,time_t);
time_t mktime(struct tm *);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
struct tm *gmtime_r(const time_t *,struct tm *);
struct tm *localtime_r(const time_t *,struct tm *);
char *asctime(const struct tm *);
char *ctime(const time_t *);
char *ctime_r(const time_t *,char *);
size_t strftime(char *,size_t,const char *,const struct tm *);
int clock_gettime(clockid_t,struct timespec *);
int clock_settime(clockid_t,const struct timespec *);
int clock_getres(clockid_t,struct timespec *);
int nanosleep(const struct timespec *,struct timespec *);
void tzset(void);
BMW_END_DECLS

#ifdef __cplusplus
namespace std { using ::asctime; using ::clock; using ::clock_getres; using ::clock_gettime; using ::clock_settime; using ::clock_t; using ::ctime; using ::ctime_r; using ::difftime; using ::gmtime; using ::gmtime_r; using ::localtime; using ::localtime_r; using ::mktime; using ::nanosleep; using ::strftime; using ::time; using ::time_t; using ::tm; using ::tzset; }
#endif
