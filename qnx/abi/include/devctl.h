/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_DEVCTL_H
#define BMW_QNX_DEVCTL_H
#include <stddef.h>
#ifndef EOK
#define EOK 0
#endif
#ifdef __cplusplus
extern "C" {
#endif
int devctl(int, int, void *, size_t, int *);
#ifdef __cplusplus
}
#endif
#endif
