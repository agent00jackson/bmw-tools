/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_SPAWN_H
#define BMW_QNX_SPAWN_H
#include <stdint.h>
#include <sys/types.h>
#include <signal.h>
#include <sched.h>
typedef uintptr_t posix_spawnattr_t;
typedef uintptr_t posix_spawn_file_actions_t;
struct inheritance { unsigned long flags; pid_t pgroup; sigset_t sigmask, sigdefault, sigignore; unsigned long stack_max; int policy; uint32_t nd, runmask; struct sched_param param; };
typedef struct inheritance spawn_inheritance_type;
#define SPAWN_SETGROUP 1
#define SPAWN_SETSIGMASK 2
#define SPAWN_SETSIGDEF 4
#define SPAWN_SETSID 512
#define SPAWN_EXPLICIT_SCHED 1024
#define SPAWN_NOZOMBIE 8192
#define SPAWN_FDCLOSED (-1)
#define SPAWN_NEWPGROUP 0
#ifdef __cplusplus
extern "C" {
#endif
int posix_spawn_file_actions_init(posix_spawn_file_actions_t *);
int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *);
int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *, int);
int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *, int, int);
int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *, int, const char *, int, mode_t);
int posix_spawnattr_init(posix_spawnattr_t *);
int posix_spawnattr_destroy(posix_spawnattr_t *);
int posix_spawn(pid_t *, const char *, const posix_spawn_file_actions_t *, const posix_spawnattr_t *, char *const[], char *const[]);
int posix_spawnp(pid_t *, const char *, const posix_spawn_file_actions_t *, const posix_spawnattr_t *, char *const[], char *const[]);
pid_t spawn(const char *, int, const int[], const struct inheritance *, char *const[], char *const[]);
pid_t spawnp(const char *, int, const int[], const struct inheritance *, char *const[], char *const[]);
#ifdef __cplusplus
}
#endif
#endif
