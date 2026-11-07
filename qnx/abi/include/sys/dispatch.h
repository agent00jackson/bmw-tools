/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_DISPATCH_H
#define BMW_QNX_DISPATCH_H
#include <time.h>
#include <sys/resmgr.h>
typedef struct bmw_qnx_dispatch dispatch_t;
typedef union _dispatch_context dispatch_context_t;
typedef struct {
    unsigned flags, nparts_max, msg_max_size;
    int (*other_func)(resmgr_context_t *, void *);
    unsigned reserved[4];
} resmgr_attr_t;
#ifdef __cplusplus
extern "C" {
#endif
int name_open(const char *, int);
int name_close(int);
dispatch_t *dispatch_create(void);
int dispatch_destroy(dispatch_t *);
dispatch_context_t *dispatch_context_alloc(dispatch_t *);
void dispatch_context_free(dispatch_context_t *);
dispatch_context_t *dispatch_block(dispatch_context_t *);
int dispatch_handler(dispatch_context_t *);
int dispatch_timeout(dispatch_t *, struct timespec *);
int resmgr_attach(dispatch_t *, resmgr_attr_t *, const char *, int, unsigned,
                  const resmgr_connect_funcs_t *, const resmgr_io_funcs_t *, RESMGR_HANDLE_T *);
int resmgr_detach(dispatch_t *, int, unsigned);
#ifdef __cplusplus
}
#endif
#endif
