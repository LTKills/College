.data
.align 0

strask:
    .asciiz "Digite um numero: "

strans:
    .asciiz "Hello World "

.text
.globl main

main:
    li $v0, 4 #print string
    la $a0, strask
    syscall

    li $v0, 5 # read int
    syscall
    move $t0, $v0

    li $v0, 4 # print ans
    la $a0, strans
    syscall

    move $a0, $t0 #print int
    li $v0, 1
    syscall

    li $v0, 10
    syscall
