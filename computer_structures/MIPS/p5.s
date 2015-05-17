# PRAC_5.S
		.data
dato: 	.asciiz "Hola,Muestrame\n"
		.text
		.globl main
main:

		la $t2, dato
		#----Direccionamiento por registro----#
		move $a0,$t2
		li $v0,4
		syscall
		#----valor inmediato----#
		la $a0,0x10010000
		li $v0,4
		syscall		
		#----inmediato + registro----#
		la $a0,5($t2)
		li $v0,4
		syscall	
		#----identificador----#
		la $a0,dato
		li $v0,4
		syscall			
		#----identificador + inmediato----#
		la $a0,dato+5
		li $v0,4
		syscall		
		#----identificador + registro----#
		li $t1, 5
		la $a0,dato($t1)
		li $v0,4
		syscall			
		#----identificador + registro + inmediato----#
		li $t1, 3
		la $a0,dato+2($t1)
		li $v0,4
		syscall		