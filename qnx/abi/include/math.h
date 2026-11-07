/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_MATH_H
#define BMW_QNX_MATH_H
#define HUGE_VAL __builtin_huge_val()
#define HUGE_VALF __builtin_huge_valf()
#define HUGE_VALL __builtin_huge_vall()
#define INFINITY __builtin_inff()
#define NAN __builtin_nanf("")
#define M_PI 3.14159265358979323846
#ifdef __cplusplus
extern "C" {
#endif
double acos(double);
float acosf(float);
long double acosl(long double);
double asin(double);
float asinf(float);
long double asinl(long double);
double atan(double);
float atanf(float);
long double atanl(long double);
double cos(double);
float cosf(float);
long double cosl(long double);
double sin(double);
float sinf(float);
long double sinl(long double);
double tan(double);
float tanf(float);
long double tanl(long double);
double cosh(double);
float coshf(float);
long double coshl(long double);
double sinh(double);
float sinhf(float);
long double sinhl(long double);
double tanh(double);
float tanhf(float);
long double tanhl(long double);
double exp(double);
float expf(float);
long double expl(long double);
double log(double);
float logf(float);
long double logl(long double);
double log10(double);
float log10f(float);
long double log10l(long double);
double sqrt(double);
float sqrtf(float);
long double sqrtl(long double);
double ceil(double);
float ceilf(float);
long double ceill(long double);
double fabs(double);
float fabsf(float);
long double fabsl(long double);
double floor(double);
float floorf(float);
long double floorl(long double);
double exp2(double);
float exp2f(float);
long double exp2l(long double);
double log2(double);
float log2f(float);
long double log2l(long double);
double trunc(double);
float truncf(float);
long double truncl(long double);
double round(double);
float roundf(float);
long double roundl(long double);
double nearbyint(double);
float nearbyintf(float);
long double nearbyintl(long double);
double rint(double);
float rintf(float);
long double rintl(long double);
double cbrt(double);
float cbrtf(float);
long double cbrtl(long double);
double atan2(double, double);
float atan2f(float, float);
long double atan2l(long double, long double);
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
double pow(double, double);
float powf(float, float);
long double powl(long double, long double);
double copysign(double, double);
float copysignf(float, float);
long double copysignl(long double, long double);
double hypot(double, double);
float hypotf(float, float);
long double hypotl(long double, long double);
double frexp(double, int *);
double ldexp(double, int);
double modf(double, double *);
long lrint(double);
long lround(double);
long long llrint(double);
long long llround(double);
float frexpf(float, int *);
float ldexpf(float, int);
float modff(float, float *);
long lrintf(float);
long lroundf(float);
long long llrintf(float);
long long llroundf(float);
long double frexpl(long double, int *);
long double ldexpl(long double, int);
long double modfl(long double, long double *);
long lrintl(long double);
long lroundl(long double);
long long llrintl(long double);
long long llroundl(long double);
#ifdef __cplusplus
}
namespace std {
using ::acos;
using ::acosf;
using ::acosl;
using ::asin;
using ::asinf;
using ::asinl;
using ::atan;
using ::atanf;
using ::atanl;
using ::cos;
using ::cosf;
using ::cosl;
using ::sin;
using ::sinf;
using ::sinl;
using ::tan;
using ::tanf;
using ::tanl;
using ::cosh;
using ::coshf;
using ::coshl;
using ::sinh;
using ::sinhf;
using ::sinhl;
using ::tanh;
using ::tanhf;
using ::tanhl;
using ::exp;
using ::expf;
using ::expl;
using ::log;
using ::logf;
using ::logl;
using ::log10;
using ::log10f;
using ::log10l;
using ::sqrt;
using ::sqrtf;
using ::sqrtl;
using ::ceil;
using ::ceilf;
using ::ceill;
using ::fabs;
using ::fabsf;
using ::fabsl;
using ::floor;
using ::floorf;
using ::floorl;
using ::exp2;
using ::exp2f;
using ::exp2l;
using ::log2;
using ::log2f;
using ::log2l;
using ::trunc;
using ::truncf;
using ::truncl;
using ::round;
using ::roundf;
using ::roundl;
using ::nearbyint;
using ::nearbyintf;
using ::nearbyintl;
using ::rint;
using ::rintf;
using ::rintl;
using ::cbrt;
using ::cbrtf;
using ::cbrtl;
using ::atan2;
using ::atan2f;
using ::atan2l;
using ::fmod;
using ::fmodf;
using ::fmodl;
using ::pow;
using ::powf;
using ::powl;
using ::copysign;
using ::copysignf;
using ::copysignl;
using ::hypot;
using ::hypotf;
using ::hypotl;
using ::frexp;
using ::frexpf;
using ::frexpl;
using ::ldexp;
using ::ldexpf;
using ::ldexpl;
using ::modf;
using ::modff;
using ::modfl;
using ::lrint;
using ::lrintf;
using ::lrintl;
using ::lround;
using ::lroundf;
using ::lroundl;
using ::llrint;
using ::llrintf;
using ::llrintl;
using ::llround;
using ::llroundf;
using ::llroundl;
inline double abs(double x) { return __builtin_fabs(x); }
inline float abs(float x) { return __builtin_fabsf(x); }
inline long double abs(long double x) { return __builtin_fabsl(x); }
template<class T> inline T __cmath_power(T x, unsigned n) {
    T result = 1;
    while (n) { if (n & 1) result *= x; x *= x; n >>= 1; }
    return result;
}
}
#endif
#define isfinite(x) __builtin_isfinite(x)
#define isnan(x) __builtin_isnan(x)
#define isinf(x) __builtin_isinf(x)
#define signbit(x) __builtin_signbit(x)
#endif
