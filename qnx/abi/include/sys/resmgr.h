/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_RESMGR_H
#define BMW_QNX_RESMGR_H
#include <stdint.h>
typedef struct _resmgr_context resmgr_context_t;
typedef struct bmw_qnx_open_message io_open_t;
typedef struct _iofunc_attr { uint64_t bmw_private_storage[11]; } iofunc_attr_t;
#define RESMGR_HANDLE_T struct _iofunc_attr

typedef int (*bmw_qnx_unused_connect_fn)(void);
typedef struct {
    unsigned nfuncs;
    int (*open)(resmgr_context_t *, io_open_t *, RESMGR_HANDLE_T *, void *);
    bmw_qnx_unused_connect_fn unlink, rename, mknod, readlink, link, unblock, mount;
} resmgr_connect_funcs_t;
typedef struct {
    unsigned nfuncs;
    void (*bmw_private_slots[26])(void);
} resmgr_io_funcs_t;
#define _RESMGR_CONNECT_NFUNCS 8
#define _RESMGR_IO_NFUNCS 26
#define _RESMGR_FLAG_SELF 0x0200
#define _RESMGR_DETACH_ALL 0
#define _FTYPE_ANY 0
#endif
