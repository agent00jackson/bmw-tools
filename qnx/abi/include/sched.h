// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <time.h>
struct sched_param { int sched_priority,sched_curpriority; int __spare[8]; };
#define SCHED_NOCHANGE 0
#define SCHED_FIFO 1
#define SCHED_RR 2
#define SCHED_OTHER 3
#define SCHED_SPORADIC 4
BMW_BEGIN_DECLS
int sched_yield(void);
int sched_get_priority_min(int);
int sched_get_priority_max(int);
int sched_getparam(pid_t,struct sched_param *);
int sched_setparam(pid_t,const struct sched_param *);
BMW_END_DECLS
