// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <stdio.h>
#include <time.h>
typedef int wint_t;
typedef struct { unsigned _Wchar; char _State; char _Reserved[3]; } mbstate_t;
#define WEOF ((wint_t)-1)
BMW_BEGIN_DECLS
size_t wcslen(const wchar_t *);
wchar_t *wcscpy(wchar_t *,const wchar_t *);
wchar_t *wcsncpy(wchar_t *,const wchar_t *,size_t);
wchar_t *wcscat(wchar_t *,const wchar_t *);
wchar_t *wcsncat(wchar_t *,const wchar_t *,size_t);
int wcscmp(const wchar_t *,const wchar_t *);
int wcsncmp(const wchar_t *,const wchar_t *,size_t);
int wcscoll(const wchar_t *,const wchar_t *);
size_t wcsxfrm(wchar_t *,const wchar_t *,size_t);
wchar_t *wcschr(const wchar_t *,wchar_t);
wchar_t *wcsrchr(const wchar_t *,wchar_t);
wchar_t *wcspbrk(const wchar_t *,const wchar_t *);
wchar_t *wcsstr(const wchar_t *,const wchar_t *);
size_t wcsspn(const wchar_t *,const wchar_t *);
size_t wcscspn(const wchar_t *,const wchar_t *);
wchar_t *wcstok(wchar_t *,const wchar_t *,wchar_t **);
int wmemcmp(const wchar_t *,const wchar_t *,size_t);
wchar_t *wmemcpy(wchar_t *,const wchar_t *,size_t);
wchar_t *wmemmove(wchar_t *,const wchar_t *,size_t);
wchar_t *wmemset(wchar_t *,wchar_t,size_t);
wchar_t *wmemchr(const wchar_t *,wchar_t,size_t);
size_t wcsftime(wchar_t *,size_t,const wchar_t *,const struct tm *);
int mbsinit(const mbstate_t *);
size_t mbrlen(const char *,size_t,mbstate_t *);
size_t mbrtowc(wchar_t *,const char *,size_t,mbstate_t *);
size_t wcrtomb(char *,wchar_t,mbstate_t *);
size_t mbsrtowcs(wchar_t *,const char **,size_t,mbstate_t *);
size_t wcsrtombs(char *,const wchar_t **,size_t,mbstate_t *);
wint_t btowc(int);
int wctob(wint_t);
double wcstod(const wchar_t *,wchar_t **);
float wcstof(const wchar_t *,wchar_t **);
long double wcstold(const wchar_t *,wchar_t **);
long wcstol(const wchar_t *,wchar_t **,int);
unsigned long wcstoul(const wchar_t *,wchar_t **,int);
long long wcstoll(const wchar_t *,wchar_t **,int);
unsigned long long wcstoull(const wchar_t *,wchar_t **,int);
wint_t fgetwc(FILE *);
wchar_t *fgetws(wchar_t *,int,FILE *);
wint_t fputwc(wchar_t,FILE *);
int fputws(const wchar_t *,FILE *);
int fwide(FILE *,int);
int fwprintf(FILE *,const wchar_t *,...);
int fwscanf(FILE *,const wchar_t *,...);
int wprintf(const wchar_t *,...);
int wscanf(const wchar_t *,...);
int swprintf(wchar_t *,size_t,const wchar_t *,...);
int swscanf(const wchar_t *,const wchar_t *,...);
int vfwprintf(FILE *,const wchar_t *,__builtin_va_list);
int vswprintf(wchar_t *,size_t,const wchar_t *,__builtin_va_list);
int vwprintf(const wchar_t *,__builtin_va_list);
wint_t getwc(FILE *);
wint_t getwchar(void);
wint_t putwc(wchar_t,FILE *);
wint_t putwchar(wchar_t);
wint_t ungetwc(wint_t,FILE *);
BMW_END_DECLS

#ifdef __cplusplus
namespace std { using ::btowc; using ::fgetwc; using ::fgetws; using ::fputwc; using ::fputws; using ::fwide; using ::fwprintf; using ::fwscanf; using ::getwc; using ::getwchar; using ::mbrlen; using ::mbrtowc; using ::mbsinit; using ::mbsrtowcs; using ::mbstate_t; using ::putwc; using ::putwchar; using ::swprintf; using ::swscanf; using ::ungetwc; using ::vfwprintf; using ::vswprintf; using ::vwprintf; using ::wcrtomb; using ::wcscat; using ::wcschr; using ::wcscmp; using ::wcscoll; using ::wcscpy; using ::wcscspn; using ::wcsftime; using ::wcslen; using ::wcsncat; using ::wcsncmp; using ::wcsncpy; using ::wcspbrk; using ::wcsrchr; using ::wcsrtombs; using ::wcsspn; using ::wcsstr; using ::wcstod; using ::wcstof; using ::wcstok; using ::wcstol; using ::wcstold; using ::wcstoll; using ::wcstoul; using ::wcstoull; using ::wcsxfrm; using ::wctob; using ::wint_t; using ::wmemchr; using ::wmemcmp; using ::wmemcpy; using ::wmemmove; using ::wmemset; using ::wprintf; using ::wscanf; }
#endif
