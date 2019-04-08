.data
.align 0

strask:
    .asciiz "Digite um inteiro: "

strans:
    .asciiz "Fatorial de "

streh:
    .asciiz " eh "

.text
.globl main

#variables

# t0 -> ans
# t1 -> input
# t2 -> aux

main:
    li $v0, 4 #print string
    la $a0, strask
    syscall

    li $v0, 5 # read int
    syscall
    move $t0, $v0

    li $v0, 4 #print string
    la $a0, strans
    syscall

    li $v0, 1 #print int
    move $a0, $t0
    syscall

    li $v0, 4 #print string
    la $a0, streh
    syscall

    #calcula fatorial de $t0#
    move $t2, $t0
    li $t1, 1

loop:
    beq $t2, 0, endloop
    mul $t1, $t1, $t2
    addi $t2, $t2, -1
    j loop

endloop:

    li $v0, 1 #print int
    move $a0, $t1
    syscall

    li $v0, 10 #halt
    syscall

