/* SPDX-License-Identifier: MIT
 * EABI memory entry points, adapting memset's argument order. The QNX libc
 * implementations are integer-only; these veneers do not touch VFP registers.
 */
.syntax unified
.arm
.text
.macro copy name, target
.global \name
.type \name,%function
\name:
    b \target
.size \name, .-\name
.endm
copy __aeabi_memcpy, memcpy
copy __aeabi_memcpy4, memcpy
copy __aeabi_memcpy8, memcpy
copy __aeabi_memmove, memmove
copy __aeabi_memmove4, memmove
copy __aeabi_memmove8, memmove
.macro clear name
.global \name
.type \name,%function
\name:
    mov r2, r1
    mov r1, #0
    b memset
.size \name, .-\name
.endm
clear __aeabi_memclr
clear __aeabi_memclr4
clear __aeabi_memclr8
.macro set name
.global \name
.type \name,%function
\name:
    mov r3, r1
    mov r1, r2
    mov r2, r3
    b memset
.size \name, .-\name
.endm
set __aeabi_memset
set __aeabi_memset4
set __aeabi_memset8
.section .note.GNU-stack,"",%progbits
