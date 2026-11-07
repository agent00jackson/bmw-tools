/* SPDX-License-Identifier: MIT */
#include <stdlib.h>
#include <errno.h>

typedef void (*init_fn)(void);
extern init_fn __preinit_array_start[], __preinit_array_end[];
extern init_fn __init_array_start[], __init_array_end[];
extern init_fn __fini_array_start[], __fini_array_end[];
extern void _init_libc(int, char **, char **, void *, void (*)(void));
extern int main(int, char **, char **);

static void finish(void) {
    for (init_fn *p = __fini_array_end; p != __fini_array_start;) (*--p)();
}

__attribute__((noreturn))
void bmw_qnx_start(unsigned *stack, void (*loader_finish)(void)) {
    int argc = (int)*stack;
    char **argv = (char **)(stack + 1);
    char **envp = argv + argc + 1;
    char **end = envp;
    while (*end) ++end;
    _init_libc(argc, argv, envp, end + 1, loader_finish);
    for (init_fn *p = __preinit_array_start; p != __preinit_array_end; ++p) (*p)();
    atexit(finish);
    for (init_fn *p = __init_array_start; p != __init_array_end; ++p) (*p)();
    errno = 0;
    exit(main(argc, argv, envp));
}
