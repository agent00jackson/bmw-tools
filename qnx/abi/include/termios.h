/* SPDX-License-Identifier: MIT */
#ifndef BMW_QNX_TERMIOS_H
#define BMW_QNX_TERMIOS_H
#include <stdint.h>
typedef unsigned char cc_t;
typedef long speed_t;
typedef unsigned long tcflag_t;
#define NCCS 40
struct termios { tcflag_t c_iflag, c_oflag, c_cflag, c_lflag; cc_t c_cc[NCCS]; uint32_t bmw_reserved[3]; speed_t c_ispeed, c_ospeed; };
#define TCSANOW 1
#define TCSADRAIN 2
#define TCSAFLUSH 4
#define CSIZE 48
#define CS8 48
#define CREAD 128
#define PARENB 256
#define CLOCAL 2048
#define VMIN 16
#define VTIME 17
#ifdef __cplusplus
extern "C" {
#endif
int tcgetattr(int, struct termios *);
int tcsetattr(int, int, const struct termios *);
int cfmakeraw(struct termios *);
speed_t cfgetispeed(const struct termios *);
speed_t cfgetospeed(const struct termios *);
int cfsetispeed(struct termios *, speed_t);
int cfsetospeed(struct termios *, speed_t);
#ifdef __cplusplus
}
#endif
#endif
