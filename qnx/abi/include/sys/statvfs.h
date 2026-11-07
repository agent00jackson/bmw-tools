/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_STATVFS_H
#define BMW_QNX_STATVFS_H
#include <stdint.h>

#if _FILE_OFFSET_BITS == 64
typedef uint64_t fsblkcnt_t;
typedef uint64_t fsfilcnt_t;
#else
typedef uint32_t fsblkcnt_t;
typedef uint32_t fsfilcnt_t;
#endif

struct statvfs {
    unsigned long f_bsize, f_frsize;
#if _FILE_OFFSET_BITS == 64
    fsblkcnt_t f_blocks, f_bfree, f_bavail;
    fsfilcnt_t f_files, f_ffree, f_favail;
#else
    fsblkcnt_t f_blocks, f_blocks_hi, f_bfree, f_bfree_hi, f_bavail, f_bavail_hi;
    fsfilcnt_t f_files, f_files_hi, f_ffree, f_ffree_hi, f_favail, f_favail_hi;
#endif
    unsigned long f_fsid;
    char f_basetype[16];
    unsigned long f_flag, f_namemax;
    unsigned long bmw_reserved[21];
};

#define ST_RDONLY 1
#define ST_NOEXEC 2
#define ST_NOSUID 4
#define ST_NOCREAT 8
#define ST_OFF32 16
#define ST_NOATIME 32

#ifdef __cplusplus
extern "C" {
#endif
#if _FILE_OFFSET_BITS == 64
int statvfs(const char *, struct statvfs *) __asm__("statvfs64");
int fstatvfs(int, struct statvfs *) __asm__("fstatvfs64");
#else
int statvfs(const char *, struct statvfs *);
int fstatvfs(int, struct statvfs *);
#endif
#ifdef __cplusplus
}
#endif
#endif
