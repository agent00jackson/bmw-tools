/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_IOFUNC_H
#define BMW_QNX_IOFUNC_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resmgr.h>
struct _client_info;
#ifdef __cplusplus
extern "C" {
#endif
void iofunc_func_init(unsigned, resmgr_connect_funcs_t *, unsigned, resmgr_io_funcs_t *);
void iofunc_attr_init(iofunc_attr_t *, mode_t, iofunc_attr_t *, struct _client_info *);
#ifdef __cplusplus
}
#endif
#endif
