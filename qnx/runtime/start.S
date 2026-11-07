/* SPDX-License-Identifier: MIT
 * QNX ARM process entry: initial stack and loader's finalizer become C args.
 */
.syntax unified
.arm
.text
.global _start
.type _start,%function
_start:
    mov r1, r0
    mov r0, sp
    bic sp, sp, #7
    bl bmw_qnx_start
    udf #0
.size _start, .-_start
.section .note.GNU-stack,"",%progbits
