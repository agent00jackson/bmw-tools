// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <bmw_abi.h>
BMW_BEGIN_DECLS
void *memcpy(void *,const void *,size_t);
void *memmove(void *,const void *,size_t);
void *memset(void *,int,size_t);
int memcmp(const void *,const void *,size_t);
void *memchr(const void *,int,size_t);
size_t strlen(const char *);
size_t strnlen(const char *,size_t);
char *strcpy(char *,const char *);
char *strncpy(char *,const char *,size_t);
char *strcat(char *,const char *);
char *strncat(char *,const char *,size_t);
int strcmp(const char *,const char *);
int strncmp(const char *,const char *,size_t);
int strcoll(const char *,const char *);
size_t strxfrm(char *,const char *,size_t);
char *strchr(const char *,int);
char *strrchr(const char *,int);
char *strstr(const char *,const char *);
char *strpbrk(const char *,const char *);
size_t strspn(const char *,const char *);
size_t strcspn(const char *,const char *);
char *strtok(char *,const char *);
char *strtok_r(char *,const char *,char **);
char *strdup(const char *);
char *strerror(int);
int strcasecmp(const char *,const char *);
int strncasecmp(const char *,const char *,size_t);
BMW_END_DECLS

#ifdef __cplusplus
namespace std { using ::memchr; using ::memcmp; using ::memcpy; using ::memmove; using ::memset; using ::strcasecmp; using ::strcat; using ::strchr; using ::strcmp; using ::strcoll; using ::strcpy; using ::strcspn; using ::strdup; using ::strerror; using ::strlen; using ::strncasecmp; using ::strncat; using ::strncmp; using ::strncpy; using ::strnlen; using ::strpbrk; using ::strrchr; using ::strspn; using ::strstr; using ::strtok; using ::strtok_r; using ::strxfrm; }
#endif
