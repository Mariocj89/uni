# PRAC_6.S
		.data
a: 		.word 32,20,27,15,1,62,41
n:		.word 7
		.text
		.globl main
main:
		li $t0,0				#t0 = i
		li $s0,0				#s0 = max
		lw $s1,n				#s1 = n
buc:	bge $t0,$s1,fin 		#si i >= n sale del "bucle"
		mul $t1, $t0, 4			#da a i el valor adeacuado
		lw $t2, a($t1)
		bge $s0, $t2, b2 		#si max >= a[i]
		move $s0, $t2			# max = a[i]
b2:		addi $t0,$t0,1			#incrementamos i en 1		
		b buc 					#vuelve al inicio del bucle
fin:	move $a0, $s0			#mostramos el valor maximo
		li $v0, 1
		syscall