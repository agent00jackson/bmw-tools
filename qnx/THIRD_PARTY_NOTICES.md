# SDK third-party notices

This SDK contains freely licensed source headers and newly authored runtime
support. It does not contain QNX or BMW runtime implementation binaries.

| Component | License | Location |
| --- | --- | --- |
| GNU libstdc++ / GCC 4.4.2 headers | GPL-3.0-or-later with GCC Runtime Library Exception 3.1 | `third_party/libstdc++-4.4.2` |
| OpenSSL 1.0.1l headers | OpenSSL and original SSLeay licenses | `third_party/openssl-1.0.1l` |
| QNX `sys/asound.h` | Apache-2.0, copyright QNX Software Systems 2007 | `third_party/qnx-audio/include/sys/asound.h` |
| ALSA-derived `sys/asoundlib.h` | LGPL-2.0-or-later, copyright Jaroslav Kysela | `third_party/qnx-audio/include/sys/asoundlib.h` |

Original notices are preserved in the headers, and the full licenses are
installed under `share/licenses/qnx-sdk`. `third_party/SHA256SUMS.json`
records the vendored source files. The new SDK code is covered by `LICENSE`.

This product includes software developed by the OpenSSL Project for use in
the OpenSSL Toolkit (https://www.openssl.org/).

This product includes cryptographic software written by Eric Young
(eay@cryptsoft.com).

Applications built with the SDK retain their own licenses and notices.
