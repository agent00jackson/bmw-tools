/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_NETINET_IN_H
#define BMW_QNX_NETINET_IN_H
#include <stdint.h>
#include <sys/socket.h>
typedef uint32_t in_addr_t;
typedef uint16_t in_port_t;
struct in_addr { in_addr_t s_addr; } __attribute__((packed));
struct sockaddr_in { uint8_t sin_len; sa_family_t sin_family; in_port_t sin_port; struct in_addr sin_addr; int8_t sin_zero[8]; };
#define INADDR_ANY 0u
#define INADDR_LOOPBACK 0x7f000001u
#define INADDR_NONE 0xffffffffu
#define INET_ADDRSTRLEN 16
#define IPPROTO_IP 0
#define IPPROTO_TCP 6
#define IPPROTO_UDP 17
static __inline__ uint16_t htons(uint16_t x) { return __builtin_bswap16(x); }
static __inline__ uint16_t ntohs(uint16_t x) { return __builtin_bswap16(x); }
static __inline__ uint32_t htonl(uint32_t x) { return __builtin_bswap32(x); }
static __inline__ uint32_t ntohl(uint32_t x) { return __builtin_bswap32(x); }
#endif
