/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_SLOG_H
#define BMW_QNX_SLOG_H
#include <stdarg.h>
#define _SLOG_INFO 5
#define _SLOG_TEXTBIT 8
#define _SLOG_SETCODE(major, minor) ((major) | ((minor) << 20))
#ifdef __cplusplus
extern "C" {
#endif
int vslogf(int, int, const char *, va_list) __attribute__((format(printf, 3, 0)));
int slogf(int, int, const char *, ...) __attribute__((format(printf, 3, 4)));
#ifdef __cplusplus
}
#endif
#endif
