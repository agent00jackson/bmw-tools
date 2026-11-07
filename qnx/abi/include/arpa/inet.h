/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_ARPA_INET_H
#define BMW_QNX_ARPA_INET_H
#include <netinet/in.h>
#ifdef __cplusplus
extern "C" {
#endif
in_addr_t inet_addr(const char *);
int inet_aton(const char *, struct in_addr *);
char *inet_ntoa(struct in_addr);
const char *inet_ntop(int, const void *, char *, socklen_t);
int inet_pton(int, const char *, void *);
#ifdef __cplusplus
}
#endif
#endif
