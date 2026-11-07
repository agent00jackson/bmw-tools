// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <bmw_abi.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RAND_MAX 32767
#define MB_CUR_MAX _Mbcurmax
BMW_BEGIN_DECLS
extern char _Mbcurmax;
typedef struct { int quot,rem; } div_t;
typedef struct { long quot,rem; } ldiv_t;
typedef struct { long long quot,rem; } lldiv_t;
void *malloc(size_t);
void *calloc(size_t,size_t);
void *realloc(void *,size_t);
void free(void *);
void abort(void) __attribute__((noreturn));
void exit(int) __attribute__((noreturn));
void _Exit(int) __attribute__((noreturn));
int atexit(void (*)(void));
char *getenv(const char *);
int setenv(const char *,const char *,int);
int unsetenv(const char *);
int putenv(char *);
int system(const char *);
int atoi(const char *);
long atol(const char *);
long long atoll(const char *);
double atof(const char *);
long strtol(const char *,char **,int);
unsigned long strtoul(const char *,char **,int);
long long strtoll(const char *,char **,int);
unsigned long long strtoull(const char *,char **,int);
double strtod(const char *,char **);
float strtof(const char *,char **);
long double strtold(const char *,char **);
int abs(int);
long labs(long);
long long llabs(long long);
div_t div(int,int);
ldiv_t ldiv(long,long);
lldiv_t lldiv(long long,long long);
int rand(void);
void srand(unsigned);
void qsort(void *,size_t,size_t,int (*)(const void *,const void *));
void *bsearch(const void *,const void *,size_t,size_t,int (*)(const void *,const void *));
int mblen(const char *,size_t);
int mbtowc(wchar_t *,const char *,size_t);
int wctomb(char *,wchar_t);
size_t mbstowcs(wchar_t *,const char *,size_t);
size_t wcstombs(char *,const wchar_t *,size_t);
char *realpath(const char *,char *);
BMW_END_DECLS

#ifdef __cplusplus
namespace std { using ::_Exit; using ::abort; using ::abs; using ::atexit; using ::atof; using ::atoi; using ::atol; using ::atoll; using ::bsearch; using ::calloc; using ::div; using ::div_t; using ::exit; using ::free; using ::getenv; using ::labs; using ::ldiv; using ::ldiv_t; using ::llabs; using ::lldiv; using ::lldiv_t; using ::malloc; using ::mblen; using ::mbstowcs; using ::mbtowc; using ::putenv; using ::qsort; using ::rand; using ::realloc; using ::realpath; using ::setenv; using ::srand; using ::strtod; using ::strtof; using ::strtol; using ::strtold; using ::strtoll; using ::strtoul; using ::strtoull; using ::system; using ::unsetenv; using ::wcstombs; using ::wctomb; }
#endif
