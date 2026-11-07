// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <sys/types.h>
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define F_OK 0
#define X_OK 1
#define W_OK 2
#define R_OK 4
#define _SC_CLK_TCK 3
#define _SC_PAGESIZE 11
#define _SC_NPROCESSORS_CONF 90
#define _SC_NPROCESSORS_ONLN 91
BMW_BEGIN_DECLS
extern char **environ;
int close(int);
int isatty(int);
ssize_t read(int,void *,size_t);
ssize_t write(int,const void *,size_t);
off_t lseek(int,off_t,int);
int pipe(int [2]);
int dup(int);
int dup2(int,int);
int access(const char *,int);
int unlink(const char *);
int rmdir(const char *);
int chdir(const char *);
char *getcwd(char *,size_t);
int usleep(useconds_t);
unsigned sleep(unsigned);
unsigned alarm(unsigned);
int fsync(int);
int ftruncate(int,off_t);
pid_t getpid(void);
pid_t getppid(void);
pid_t fork(void);
pid_t vfork(void);
pid_t setsid(void);
uid_t getuid(void);
uid_t geteuid(void);
gid_t getgid(void);
gid_t getegid(void);
int execv(const char *,char *const []);
int execve(const char *,char *const [],char *const []);
int execvp(const char *,char *const []);
int execl(const char *,const char *,...);
void _exit(int) __attribute__((noreturn));
long sysconf(int);
int gethostname(char *,size_t);
ssize_t readlink(const char *,char *,size_t);
BMW_END_DECLS
