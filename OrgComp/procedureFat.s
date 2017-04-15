.text
.globl main

main:
    li $v0, 5 # read integer
    syscall

    move $a0, $v0 #set read number as argument
    jal fat #chama o fatorial e guarda o endereço de retorno em $ra

    move $a0, $v0
    li, $v0, 1
    syscall

    li, $v0, 10
    syscall


fat:
    addi $sp, $sp, -8 # reserva 2 palavras
    sw $a0, 4($sp)
    sw $ra, 0($sp)

    li $v0, 1
    move $t6, $a0

loop:
    beq $t6, $zero, endloop

    mul $v0, $v0, $t6
    addi $t6, $t6, -1

    j loop

endloop:
    lw $a0, 4($sp)
    lw $ra, 0($sp)
    addi $sp, $sp, 8 # libera 2 palavras
    jr $ra
