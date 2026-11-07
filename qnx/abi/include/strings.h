/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_STRINGS_H
#define BMW_QNX_STRINGS_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);
void bzero(void *, size_t);
#ifdef __cplusplus
}
#endif
#endif
