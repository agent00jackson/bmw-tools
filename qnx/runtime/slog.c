/* SPDX-License-Identifier: MIT
 * QNX 6.5 /dev/slog record format: severity/text/msec/count, opcode, seconds,
 * then 32-bit-padded data. See the public slogger/sloginfo interface docs.
 * This replaces the SDK's static-only formatter without borrowing its code.
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/slog.h>

__attribute__((visibility("hidden")))
int vslogf(int code, int severity, const char *format, va_list args) {
    uint32_t record[257] = {0};
    char *text = (char *)(record + 3);
    size_t capacity = sizeof(record) - 3 * sizeof(uint32_t);
    if (!format) { errno = EINVAL; return -1; }
    int length = vsnprintf(text, capacity, format, args);
    if (length < 0) return -1;
    size_t bytes = (size_t)length < capacity ? (size_t)length + 1 : capacity;
    size_t words = (bytes + 3) / 4;
    struct timeval now;
    if (gettimeofday(&now, NULL)) return -1;
    record[0] = (uint32_t)(words << 16) | (uint32_t)((now.tv_usec / 1000) << 4)
                | 8u | ((unsigned)severity & 7u);
    record[1] = (uint32_t)code;
    record[2] = (uint32_t)now.tv_sec;
    if (severity & 8) fputs(text, stderr);
    int fd = open("/dev/slog", O_WRONLY);
    if (fd < 0) return -1;
    size_t total = (words + 3) * sizeof(uint32_t);
    ssize_t sent;
    do { sent = write(fd, record, total); } while (sent < 0 && errno == EINTR);
    int saved = errno;
    close(fd);
    if (sent >= 0 && (size_t)sent != total) { errno = EIO; return -1; }
    errno = saved;
    return (int)sent;
}

__attribute__((visibility("hidden")))
int slogf(int code, int severity, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = vslogf(code, severity, format, args);
    va_end(args);
    return result;
}
