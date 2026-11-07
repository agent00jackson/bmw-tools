/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_PROCFS_H
#define BMW_QNX_PROCFS_H
#include <stdint.h>
#include <devctl.h>
typedef struct { uint64_t vaddr; char path[1]; } procfs_debuginfo;
#define DCMD_PROC_MAPDEBUG_BASE 0x40100803u
#endif
