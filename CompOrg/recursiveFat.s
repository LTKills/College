.text
.globl main

main:

    li $t1, 1
    li $v0, 5 #read int
    syscall

    move $a0, $v0
    li $v0, 1
    jal fat

    move $a0, $v0
    li $v0, 1
    syscall

    li $v0, 10 #halt
    syscall


fat:
    addi $sp, $sp, -8 #allocate
    sw $a0, 4($sp)
    sw $ra, 0($sp)

    beq $a0, $t1, end
    addi $a0, $a0, -1
    jal fat

end:
    lw $a0, 4($sp) #deallocate
    mul $v0, $v0, $a0 #return value

    lw $ra, 0($sp)
    addi $sp, $sp, 8
    jr $ra
