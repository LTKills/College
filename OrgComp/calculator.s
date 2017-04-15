.data
.align 0

strask:
    .asciiz "Digite a operacao: "

strans:
    .asciiz "Resultado: "

.text
.globl main

main:

    # read operands
    li $v0, 5
    syscall
    move $t1, $v0

    li $v0, 5
    syscall
    move $t2, $v0

    li $v0, 4 # pede operacao
    la $a0, strask
    syscall

    # read character
    li $v0, 12
    syscall
    move $t3, $v0

    #choose operation
    li $t4, 43
    li $t5, 45
    li $t6, 42
    li $t7, 47
    beq $t3, $t4, sim # +
    beq $t3, $t5, sib # -
    beq $t3, $t6, muli # *
    beq $t3, $t7, dio # /

# operations
sim:
    add $t0, $t1, $t2
    j end
sib:
    sub $t0, $t1, $t2
    j end
dio:
    div $t0, $t2, $t1
    j end
muli:
    mul $t0, $t2, $t1
    j end

end:
    li $v0, 4 # Resultado:
    la $a0, strans
    syscall

    # imprime resultado
    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 10
    syscall
