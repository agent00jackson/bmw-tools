/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_DIRENT_H
#define BMW_QNX_DIRENT_H
#include <stdint.h>
struct _dir;
typedef struct _dir DIR;
struct dirent { uint32_t d_ino, d_ino_hi; int32_t d_offset, d_offset_hi; int16_t d_reclen, d_namelen; char d_name[1]; };
#ifdef __cplusplus
extern "C" {
#endif
DIR *opendir(const char *);
struct dirent *readdir(DIR *);
int closedir(DIR *);
void rewinddir(DIR *);
#ifdef __cplusplus
}
#endif
#endif
