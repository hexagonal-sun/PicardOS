.globl _start
_start:
    b setup
    b _exit
    b __syscall
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit
    b _exit

setup:
    ldr sp,=0x00027C00
    bl main
    b _exit
