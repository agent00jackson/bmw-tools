/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_POLL_H
#define BMW_QNX_POLL_H
typedef unsigned int nfds_t;
struct pollfd { int fd; short events, revents; };
#define POLLRDNORM 1
#define POLLOUT 2
#define POLLWRNORM POLLOUT
#define POLLRDBAND 4
#define POLLIN 5
#define POLLPRI 8
#define POLLWRBAND 16
#define POLLERR 32
#define POLLHUP 64
#define POLLNVAL 4096
#ifdef __cplusplus
extern "C" {
#endif
int poll(struct pollfd *, nfds_t, int);
#ifdef __cplusplus
}
#endif
#endif
