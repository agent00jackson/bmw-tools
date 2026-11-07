// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <sched.h>
typedef struct { int __count; unsigned __owner; } pthread_mutex_t;
typedef pthread_mutex_t pthread_cond_t;
typedef struct { int __protocol,__flags,__prioceiling,__clockid,__reserved[4]; } pthread_mutexattr_t;
typedef pthread_mutexattr_t pthread_condattr_t;
typedef int pthread_key_t;
typedef struct { int __flags; size_t __stacksize; void *__stackaddr; void (*__exitfunc)(void *); int __policy; struct sched_param __param; unsigned __guardsize,__prealloc; int __spare[2]; } pthread_attr_t;
typedef struct { int __once; pthread_mutex_t __mutex; } pthread_once_t;
#define PTHREAD_MUTEX_INITIALIZER { (int)0x80000000u,0xffffffffu }
#define PTHREAD_COND_INITIALIZER { -5,0xffffffffu }
#define PTHREAD_ONCE_INIT { 0,PTHREAD_MUTEX_INITIALIZER }
#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1
#define PTHREAD_MUTEX_DEFAULT 0
#define PTHREAD_MUTEX_RECURSIVE 2
#define PTHREAD_MUTEX_NORMAL 3
#define PTHREAD_MUTEX_ERRORCHECK 1
BMW_BEGIN_DECLS
int pthread_create(pthread_t *,const pthread_attr_t *,void *(*)(void *),void *);
int pthread_join(pthread_t,void **);
int pthread_detach(pthread_t);
pthread_t pthread_self(void);
int pthread_equal(pthread_t,pthread_t);
void pthread_exit(void *) __attribute__((noreturn));
int pthread_cancel(pthread_t);
int pthread_attr_init(pthread_attr_t *);
int pthread_attr_destroy(pthread_attr_t *);
int pthread_attr_setdetachstate(pthread_attr_t *,int);
int pthread_attr_setstacksize(pthread_attr_t *,size_t);
int pthread_attr_setschedparam(pthread_attr_t *,const struct sched_param *);
int pthread_attr_setschedpolicy(pthread_attr_t *,int);
int pthread_setschedparam(pthread_t,int,const struct sched_param *);
int pthread_getschedparam(pthread_t,int *,struct sched_param *);
int pthread_mutex_init(pthread_mutex_t *,const pthread_mutexattr_t *);
int pthread_mutex_destroy(pthread_mutex_t *);
int pthread_mutex_lock(pthread_mutex_t *);
int pthread_mutex_trylock(pthread_mutex_t *);
int pthread_mutex_unlock(pthread_mutex_t *);
int pthread_mutexattr_init(pthread_mutexattr_t *);
int pthread_mutexattr_destroy(pthread_mutexattr_t *);
int pthread_mutexattr_settype(pthread_mutexattr_t *,int);
int pthread_cond_init(pthread_cond_t *,const pthread_condattr_t *);
int pthread_cond_destroy(pthread_cond_t *);
int pthread_cond_signal(pthread_cond_t *);
int pthread_cond_broadcast(pthread_cond_t *);
int pthread_cond_wait(pthread_cond_t *,pthread_mutex_t *);
int pthread_cond_timedwait(pthread_cond_t *,pthread_mutex_t *,const struct timespec *);
int pthread_key_create(pthread_key_t *,void (*)(void *));
int pthread_key_delete(pthread_key_t);
void *pthread_getspecific(pthread_key_t);
int pthread_setspecific(pthread_key_t,const void *);
int pthread_once(pthread_once_t *,void (*)(void));
BMW_END_DECLS
