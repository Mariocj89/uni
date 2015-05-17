# PRAC_4B.S
		.text
		.globl main
main:
		li $s0, 5 		# Selecciono el color
		bne $s0, 0, c1
		la $a0, negro
		b cx
c1: 	bne $s0, 1, c2
		la $a0, azul
		b cx
c2: 	bne $s0, 2, c3
		la $a0, amarillo
		b cx
c3: 	bne $s0, 3, c4
		la $a0, verde
		b cx
c4: 	bne $s0, 4, c5
		la $a0, rojo
		b cx
c5: 	bne $s0, 5, c6
		la $a0, gris
		b cx
c6: 	bne $s0, 6, c7
		la $a0, naranja
		b cx
c7: 	bne $s0, 7, c8
		la $a0, blanco
		b cx
c8: 	la $a0, otros
cx: 	li $v0, 4 		# Imprime el color
		syscall
		li $v0, 10
		syscall
		.data
negro: 	.asciiz "negro\n"
azul: 	.asciiz "azul\n"
amarillo: .asciiz "amarillo\n"
verde: 	.asciiz "verde\n"
rojo: 	.asciiz "rojo\n"
gris: 	.asciiz "gris\n"
naranja: .asciiz "naranja\n"
blanco: .asciiz "blanco\n"
otros: 	.asciiz "otros\n"
