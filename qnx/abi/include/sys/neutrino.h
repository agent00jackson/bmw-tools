/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_NEUTRINO_H
#define BMW_QNX_NEUTRINO_H
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>

#ifndef BMW_QNX_IOVEC_DEFINED
#define BMW_QNX_IOVEC_DEFINED
typedef struct iovec { void *iov_base; size_t iov_len; } iov_t;
#endif
#ifndef SETIOV
#define SETIOV(iov, base, length) \
    ((iov)->iov_base = (void *)(base), (iov)->iov_len = (length))
#endif
#define _NTO_TIMEOUT_SEND 16
#define _NTO_TIMEOUT_REPLY 64
struct sigevent;
#ifdef __cplusplus
extern "C" {
#endif
int MsgSendvs_r(int, const struct iovec *, int, void *, int);
int TimerTimeout(clockid_t, int, const struct sigevent *, const uint64_t *, uint64_t *);
#ifdef __cplusplus
}
#endif
#endif
