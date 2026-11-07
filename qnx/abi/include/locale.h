// SPDX-License-Identifier: MIT
// App-specific QNX 6.5 ARM EABI interface declarations.
#pragma once
#include <bmw_abi.h>
#define LC_COLLATE 1
#define LC_CTYPE 2
#define LC_MONETARY 4
#define LC_NUMERIC 8
#define LC_TIME 16
#define LC_MESSAGES 32
#define LC_ALL 63
struct lconv {
 char *currency_symbol,*int_curr_symbol,*mon_decimal_point,*mon_grouping,*mon_thousands_sep,*negative_sign,*positive_sign;
 char frac_digits,int_frac_digits,n_cs_precedes,n_sep_by_space,n_sign_posn,p_cs_precedes,p_sep_by_space,p_sign_posn;
 char int_n_cs_precedes,int_n_sep_by_space,int_n_sign_posn,int_p_cs_precedes,int_p_sep_by_space,int_p_sign_posn;
 char *decimal_point,*grouping,*thousands_sep,*_Frac_grouping,*_Frac_sep,*_False,*_True,*_No,*_Yes,*_Nostr,*_Yesstr,*_Reserved[8];
};
BMW_BEGIN_DECLS
struct lconv *localeconv(void);
char *setlocale(int,const char *);
BMW_END_DECLS
#ifdef __cplusplus
namespace std { using ::lconv; using ::localeconv; using ::setlocale; }
#endif
