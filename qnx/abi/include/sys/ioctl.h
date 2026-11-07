/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_SYS_IOCTL_H
#define BMW_QNX_SYS_IOCTL_H
#include <sys/sockio.h>
#ifdef __cplusplus
extern "C" {
#endif
int ioctl(int, int, ...);
#ifdef __cplusplus
}
#endif
#endif
