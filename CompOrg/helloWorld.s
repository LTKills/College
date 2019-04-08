
.text
.globl main

main:
    li $v0, 5 # le inteiro
    syscall

    move $a0, $v0 # imprime inteiro
    li $v0, 1
    syscall

    li $v0, 10   # halt
    syscall
