/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_NET_IF_H
#define BMW_QNX_NET_IF_H
#include <sys/socket.h>
#define IF_NAMESIZE 16
#define IFNAMSIZ 16
struct ifreq {
    char ifr_name[16];
    union { struct sockaddr address; struct sockaddr_storage storage; int flags; int metric; int mtu; void *data; } bmw_value;
};
#define ifr_addr bmw_value.address
#define ifr_flags bmw_value.flags
#define ifr_mtu bmw_value.mtu
#define ifr_data bmw_value.data
#endif
