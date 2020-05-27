.syntax unified
.cpu cortex-m4
//.fpu softvfp
.thumb
#define A #2 //a
#define B #2 //b
#define C #2 //c
// Global memory locations.
.global vtable_kernel
.global __kernel_reset__
.type vtable_kernel, %object
.type __kernel_reset__, %function
.section .interrupt_vector
vtable_kernel:
.word __stack_start
.word __kernel_reset__+1
.size vtable_kernel, .-vtable_kernel
.section .rodata
data: .asciz "kernel started!\n"
final: .asciz "Value in register #3: "
.section .text
__kernel_reset__:
// (a&b) >> + c!
mov r0, A
mov r1, B
mov r2, C
and r0, r1
lsr r4, r0, #1 
mov r3, #1
factorial:
cmp r2, #1
beq sum
mul r3, r2
sub r2, #1
b factorial
sum:
add r4, r3
ldr r0, =data
bl dbgput_line
mov r0, r4
bl dbgput_num
end:
b end
