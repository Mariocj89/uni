# PRAC_4A.S
		.text
		.globl main
main:
		la $a0,x 		# $a0 = dirección base del array x
		la $a1,y 		# $a1 = dirección base del array y
		lw $a2,size 	# $a2 = tamaño del array = n
		jal ip 			# Invoca rutina ip, guarda en $ra la dir. de vuelta
		move $a0,$v0 	# Imprime el número entero que hay en $a0, y que
		li $v0,1 		# es el resultado que ip dejó en $v0
		syscall
		li $v0,10 		# Termina la ejecución del programa
		syscall
ip: 	li $v0,0 		# Inicializa sum a 0. Usamos $v0 para guardar el
						# resultado que devuelve la rutina.
		li $t3,0 		# Pone i en $t3. Usamos $t3 como índice de
						# elementos de los arrays.
ipl:	bge $t3,$a2,ipx # Sale cuando i >= n (n está en $a2)
		lw $t0,0($a0) 	# Captura a0[i]
		lw $t1,0($a1) 	# Captura a1[i]
		mul $t2,$t0,$t1
		add $v0,$v0,$t2 # Suma a0[i]*a1[i] a sum
		addi $a0,$a0,4 	# Incrementa los punteros
		addi $a1,$a1,4
		addi $t3,$t3,1 	# i++
		b ipl 			# Contin·a. Va a ipl incondicionalmente.
ipx: 	jr $ra 			# Retorna al invocador
		.data
size: 	.word 5
x: 		.word 2,4,3,5,1
y: 		.word 3,3,2,5,4
