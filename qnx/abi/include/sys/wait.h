/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_SYS_WAIT_H
#define BMW_QNX_SYS_WAIT_H
#include <sys/types.h>
#define WNOHANG 64
#define WUNTRACED 4
#define WIFEXITED(s) (((s) & 255) == 0)
#define WEXITSTATUS(s) (((s) >> 8) & 255)
#define WIFSIGNALED(s) (((s) & 255) != 0 && ((s) & 65280) == 0)
#define WTERMSIG(s) ((s) & 127)
#define WIFSTOPPED(s) (((s) & 255) == 127 && ((s) & 65280) != 0)
#ifdef __cplusplus
extern "C" {
#endif
pid_t wait(int *);
pid_t waitpid(pid_t, int *, int);
#ifdef __cplusplus
}
#endif
#endif
