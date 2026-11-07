/* SPDX-License-Identifier: MIT
 * Compiler support for ARM base PCS, softfp, 32-bit little endian QNX.
 * No SDK startup objects or libgcc archive is incorporated into the output.
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

__attribute__((visibility("hidden"))) void *__dso_handle = &__dso_handle;
extern void __cxa_finalize(void *);
__attribute__((destructor)) static void finalize(void) { __cxa_finalize(__dso_handle); }

/* These base-PCS entry points use r0:r1 for doubles. Integer-to-double
 * conversion is split at 32 bits so it cannot call itself recursively. */
double __aeabi_ul2d(uint64_t n) {
    return (double)(uint32_t)(n >> 32) * 4294967296.0 + (double)(uint32_t)n;
}
double __aeabi_l2d(int64_t n) {
    uint64_t magnitude = n < 0 ? 0 - (uint64_t)n : (uint64_t)n;
    double value = __aeabi_ul2d(magnitude);
    return n < 0 ? -value : value;
}
int64_t __aeabi_d2lz(double value) {
    union { double d; uint64_t u; } bits = { value };
    int exponent = (int)((bits.u >> 52) & 2047) - 1023;
    if (exponent < 0) return 0;
    uint64_t mantissa = (bits.u & UINT64_C(0x000fffffffffffff)) | (UINT64_C(1) << 52);
    uint64_t magnitude;
    if (exponent >= 63) return bits.u >> 63 ? INT64_MIN : INT64_MAX;
    if (exponent >= 52) magnitude = mantissa << (exponent - 52);
    else magnitude = mantissa >> (52 - exponent);
    return (int64_t)(bits.u >> 63 ? 0 - magnitude : magnitude);
}
