/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_SYS_SOCKET_H
#define BMW_QNX_SYS_SOCKET_H
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#ifndef BMW_QNX_SOCKET_TYPES
#define BMW_QNX_SOCKET_TYPES
typedef uint8_t sa_family_t;
typedef uint32_t socklen_t;
#endif
struct sockaddr { uint8_t sa_len; sa_family_t sa_family; char sa_data[14]; };
struct sockaddr_storage { uint8_t ss_len; sa_family_t ss_family; char bmw_padding[6]; int64_t bmw_alignment; char bmw_storage[112]; };
struct linger { int l_onoff, l_linger; };
#define AF_UNSPEC 0
#define AF_UNIX 1
#define AF_LOCAL 1
#define AF_INET 2
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define SOL_SOCKET 65535
#define SO_REUSEADDR 4
#define SO_KEEPALIVE 8
#define SO_REUSEPORT 512
#define SO_SNDBUF 0x1001
#define SO_RCVBUF 0x1002
#define SO_SNDTIMEO 0x1005
#define SO_RCVTIMEO 0x1006
#define SO_ERROR 0x1007
#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2
#ifdef __cplusplus
extern "C" {
#endif
int socket(int, int, int);
int socketpair(int, int, int, int *);
int bind(int, const struct sockaddr *, socklen_t);
int listen(int, int);
int connect(int, const struct sockaddr *, socklen_t);
int accept(int, struct sockaddr *, socklen_t *);
int getpeername(int, struct sockaddr *, socklen_t *);
int getsockname(int, struct sockaddr *, socklen_t *);
int getsockopt(int, int, int, void *, socklen_t *);
int setsockopt(int, int, int, const void *, socklen_t);
int shutdown(int, int);
ssize_t recv(int, void *, size_t, int);
ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *, socklen_t *);
ssize_t send(int, const void *, size_t, int);
ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
#ifdef __cplusplus
}
#endif
#endif
