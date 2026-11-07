/* SPDX-License-Identifier: MIT
 * QNX libc exports fdopen/spawn/waitpid, but supplies popen only in its static
 * archive. Implement the POSIX interface here to avoid that proprietary code.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <spawn.h>
#include <sys/wait.h>

extern char **environ;
struct child { FILE *stream; pid_t pid; int fd; struct child *next; };
static struct child *children;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

FILE *popen(const char *command, const char *mode) {
    if (!command || !mode || (mode[0] != 'r' && mode[0] != 'w') ||
        (mode[1] && (mode[1] != 'e' || mode[2]))) { errno = EINVAL; return NULL; }
    struct child *entry = malloc(sizeof(*entry));
    if (!entry) return NULL;
    /* Every pipe must be registered or closed before another popen spawns. */
    pthread_mutex_lock(&lock);
    int fds[2];
    if (pipe(fds) < 0) { pthread_mutex_unlock(&lock); free(entry); return NULL; }
    int parent = fds[mode[0] == 'r' ? 0 : 1];
    int child = fds[mode[0] == 'r' ? 1 : 0];
    int dest = mode[0] == 'r' ? STDOUT_FILENO : STDIN_FILENO;
    FILE *stream = fdopen(parent, mode[0] == 'r' ? "r" : "w");
    if (!stream) {
        int e = errno; close(parent); close(child); pthread_mutex_unlock(&lock);
        free(entry); errno = e; return NULL;
    }
    if (mode[1] && fcntl(parent, F_SETFD, FD_CLOEXEC) < 0) {
        int e = errno; fclose(stream); close(child); pthread_mutex_unlock(&lock);
        free(entry); errno = e; return NULL;
    }
    posix_spawn_file_actions_t actions;
    int rc = posix_spawn_file_actions_init(&actions);
    int initialized = rc == 0;
    if (!rc) rc = posix_spawn_file_actions_addclose(&actions, parent);
    if (!rc) rc = posix_spawn_file_actions_adddup2(&actions, child, dest);
    if (!rc && child != dest) rc = posix_spawn_file_actions_addclose(&actions, child);
    for (struct child *p = children; !rc && p; p = p->next)
        if (p->fd != dest && p->fd != child && p->fd != parent)
            rc = posix_spawn_file_actions_addclose(&actions, p->fd);
    char *argv[] = { "sh", "-c", (char *)command, NULL };
    if (!rc) rc = posix_spawn(&entry->pid, "/bin/sh", &actions, NULL, argv, environ);
    if (initialized) posix_spawn_file_actions_destroy(&actions);
    if (!rc) { entry->stream = stream; entry->fd = parent; entry->next = children; children = entry; }
    close(child);
    if (rc) fclose(stream);
    pthread_mutex_unlock(&lock);
    if (rc) { free(entry); errno = rc; return NULL; }
    return stream;
}

int pclose(FILE *stream) {
    pthread_mutex_lock(&lock);
    struct child **link = &children;
    while (*link && (*link)->stream != stream) link = &(*link)->next;
    struct child *entry = *link;
    int close_rc = 0, close_errno = 0;
    if (entry) {
        close_rc = fclose(stream); close_errno = errno;
        *link = entry->next;
    }
    pthread_mutex_unlock(&lock);
    if (!entry) { errno = EINVAL; return -1; }
    int status; pid_t rc;
    do { rc = waitpid(entry->pid, &status, 0); } while (rc < 0 && errno == EINTR);
    free(entry);
    if (rc < 0) return -1;
    if (close_rc) { errno = close_errno; return -1; }
    return status;
}
