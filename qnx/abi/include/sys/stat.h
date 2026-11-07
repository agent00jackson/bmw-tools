// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <sys/types.h>
struct stat {
#if _FILE_OFFSET_BITS == 64
 ino_t st_ino; off_t st_size;
#else
 ino_t st_ino,st_ino_hi; off_t st_size,st_size_hi;
#endif
 dev_t st_dev,st_rdev; uid_t st_uid; gid_t st_gid;
 time_t st_mtime,st_atime,st_ctime; mode_t st_mode;
 nlink_t st_nlink; blksize_t st_blocksize; int32_t st_nblocks; blksize_t st_blksize;
#if _FILE_OFFSET_BITS == 64
 blkcnt_t st_blocks;
#else
 blkcnt_t st_blocks,st_blocks_hi;
#endif
};
#define S_IFMT 0xf000
#define S_IFIFO 0x1000
#define S_IFCHR 0x2000
#define S_IFDIR 0x4000
#define S_IFBLK 0x6000
#define S_IFREG 0x8000
#define S_IFLNK 0xa000
#define S_IFSOCK 0xc000
#define S_ISDIR(m) (((m)&S_IFMT)==S_IFDIR)
#define S_ISREG(m) (((m)&S_IFMT)==S_IFREG)
#define S_ISCHR(m) (((m)&S_IFMT)==S_IFCHR)
#define S_ISFIFO(m) (((m)&S_IFMT)==S_IFIFO)
#define S_ISLNK(m) (((m)&S_IFMT)==S_IFLNK)
#define S_IRWXU 0700
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXG 0070
#define S_IRGRP 0040
#define S_IWGRP 0020
#define S_IXGRP 0010
#define S_IRWXO 0007
#define S_IROTH 0004
#define S_IWOTH 0002
#define S_IXOTH 0001
BMW_BEGIN_DECLS
int stat(const char *,struct stat *);
int fstat(int,struct stat *);
int lstat(const char *,struct stat *);
int mkdir(const char *,mode_t);
int chmod(const char *,mode_t);
int fchmod(int,mode_t);
mode_t umask(mode_t);
BMW_END_DECLS
