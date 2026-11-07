// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <wchar.h>
typedef size_t wctype_t;
typedef size_t wctrans_t;
BMW_BEGIN_DECLS
int iswalnum(wint_t);
int iswalpha(wint_t);
int iswcntrl(wint_t);
int iswdigit(wint_t);
int iswgraph(wint_t);
int iswlower(wint_t);
int iswprint(wint_t);
int iswpunct(wint_t);
int iswspace(wint_t);
int iswupper(wint_t);
int iswxdigit(wint_t);
int iswctype(wint_t,wctype_t);
wctype_t wctype(const char *);
wctrans_t wctrans(const char *);
wint_t towctrans(wint_t,wctrans_t);
wint_t towlower(wint_t);
wint_t towupper(wint_t);
BMW_END_DECLS

#ifdef __cplusplus
namespace std { using ::iswalnum; using ::iswalpha; using ::iswcntrl; using ::iswctype; using ::iswdigit; using ::iswgraph; using ::iswlower; using ::iswprint; using ::iswpunct; using ::iswspace; using ::iswupper; using ::iswxdigit; using ::towctrans; using ::towlower; using ::towupper; using ::wctrans; using ::wctrans_t; using ::wctype; using ::wctype_t; }
#endif
