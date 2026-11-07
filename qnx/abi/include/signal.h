// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <sys/types.h>
typedef int sig_atomic_t;
typedef struct { long __bits[2]; } sigset_t;
typedef struct { void *ss_sp; size_t ss_size; int ss_flags; } stack_t;
union sigval { int sival_int; void *sival_ptr; };
typedef struct { int si_signo,si_code,si_errno; union { int padding[7]; struct { pid_t pid; union { struct { uid_t uid; union sigval value; } kill; struct { clock_t utime; int status; clock_t stime; } child; } data; } process; struct { int fltno; void *fltip; void *addr; int bdslot; } fault; } data; } siginfo_t;
#define si_pid data.process.pid
#define si_uid data.process.data.kill.uid
#define si_value data.process.data.kill.value
#define si_addr data.fault.addr
#define si_status data.process.data.child.status
struct sigaction { union { void (*handler)(int); void (*action)(int,siginfo_t *,void *); } callbacks; int sa_flags; sigset_t sa_mask; };
#define sa_handler callbacks.handler
#define sa_sigaction callbacks.action
#define SIG_DFL ((void (*)(int))0)
#define SIG_IGN ((void (*)(int))1)
#define SIG_ERR ((void (*)(int))-1)
#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGTRAP 5
#define SIGABRT 6
#define SIGFPE 8
#define SIGKILL 9
#define SIGBUS 10
#define SIGSEGV 11
#define SIGSYS 12
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15
#define SIGUSR1 16
#define SIGUSR2 17
#define SIGCHLD 18
#define SIG_BLOCK 0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2
#define SA_NOCLDSTOP 1
#define SA_SIGINFO 2
#define SA_RESETHAND 4
#define SA_NODEFER 16
#define SA_NOCLDWAIT 32
#define SS_DISABLE 2
#define SIGSTKSZ 8192
BMW_BEGIN_DECLS
int sigaction(int,const struct sigaction *,struct sigaction *);
void (*signal(int,void (*)(int)))(int);
int raise(int);
int kill(pid_t,int);
int sigemptyset(sigset_t *);
int sigfillset(sigset_t *);
int sigaddset(sigset_t *,int);
int sigdelset(sigset_t *,int);
int sigismember(const sigset_t *,int);
int sigprocmask(int,const sigset_t *,sigset_t *);
int pthread_kill(pthread_t,int);
int pthread_sigmask(int,const sigset_t *,sigset_t *);
int sigaltstack(const stack_t *,stack_t *);
BMW_END_DECLS
#ifdef __cplusplus
namespace std { using ::sig_atomic_t; using ::raise; using ::signal; }
#endif
