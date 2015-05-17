#Trabajo Practico estructuras de Computadores
		.data
endl:	.ascii		"\n"
esp:	.ascii		" "
tam:	.word		201 	#tamaño maximo de la cadena
output:	.asciiz		"Introduzca un texto (máximo: 200 caracteres)\n============================================\n"
res:	.asciiz		"\nResultados:(no incluyen retorno de carro)\n============================================"
tcar:	.asciiz		"\nCaracteres:							"
tpal:	.asciiz		"\nPalabras:							"
tesp:	.asciiz		"\nEspacios en blanco:					"
tvoc:	.asciiz		"\nVocales:							"
tcon:	.asciiz		"\nConsonantes:						"
tnum:	.asciiz		"\nNúmeros (digitos):					"
tsig:	.asciiz		"\nSignos de puntuacion y otros:				"
cons:	.ascii		"QWRTYPSDFGHJKLZXCVBNMqwrtypsdfghjklzxcvbnm" 	#42 caracteres
ncons:	.word		42
voc:	.ascii		"aeiouAEIOUáéíóú"								#15 caracteres
nvoc:	.word		15
dig:	.ascii		"1234567890"									#10 caracteres
ndig:	.word		10
input:	.asciiz		"12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890" #200 esto hay ke kambiarlo

		.text
		.globl main
main:
		#escribimos el mensaje de inicio
		la $a0,output
		li $v0,4
		syscall
		#leemos la cadena a tratar
		li $v0,8
		la $a0,input
		lw $a1, tam
		syscall
		
		#inicializamos los contadores
		li $t0, 0		#caracteres
		li $t1, 1		#palabras (empieza en uno puesto que es el numero de espacios en blanco + 1)
		li $t2, 0		#espacios en blanco 
		li $t3, 0		#vocales
		li $t4, 0		#consonantes
		li $t5, 0		#digitos
		li $t6, 0		#signos de puntuacion y otros
		
		#recorremos toda la cadena, utilizamos $s0 como indice
		li $s0, 0		#indice
		lb $s1, endl	#'\n'
		lb $s2, esp		#' '
buc:	
		lb $s3, input($s0) 	#cargamos en $s3 un caracter.
		beq $s3, $s1, salir  #cuando encuentre el retorno de carro se sale
		
		addi $t0, $t0, 1		#sumamos uno a los caracteres
		
		bne $s3, $s2, fb0 		#comparamos con el espacio
		addi $t1, $t1, 1
		addi $t2, $t2, 1
		b finb
	fb0:
	
		li $t7, 0 #usamos un indice para comparar por las vocales
		lw $s5, nvoc #usamos un registro donde almacenar el maximo de vocales
	b1:	lb $s4, voc($t7)
		bne $s4, $s3, fb1 #es esta vocal?
		addi $t3, $t3, 1
		b finb
		
	fb1:addi $t7, $t7, 1
		ble $t7, $s5, b1 #fin de vocales?
	
		li $t7, 0 #usamos un indice para comparar por las consonantes
		lw $s5, ncons #usamos un registro donde almacenar el maximo de consonantes
	b2:	lb $s4, cons($t7)
		bne $s4, $s3, fb2 #es esta consonante?
		addi $t4, $t4, 1
		b finb
		
	fb2:addi $t7, $t7, 1
		ble $t7, $s5, b2 #fin de consonantes?
		
		li $t7, 0 #usamos un indice para comparar por los digitos
		lw $s5, ndig #usamos un registro donde almacenar el maximo de digitos
	b3:	lb $s4, dig($t7)
		bne $s4, $s3, fb3 #es este digito?
		addi $t5, $t5, 1
		b finb
		
	fb3:addi $t7, $t7, 1
		ble $t7, $s5, b3 #fin de consonantes?	
	
		#si no es ni vocal ni consonante ni digito es "otro"
		addi $t6, $t6, 1
		
		
		
finb:	addi $s0, $s0, 1			#incrementamos en una posicion el indice (4 bytes)
		b buc
salir:	#mostramos todos los valores obtenidos.
		la $a0,res
		li $v0,4
		syscall
		la $a0,tcar
		li $v0,4
		syscall
		move $a0,$t0
		li $v0,1
		syscall		
		la $a0,tpal
		li $v0,4
		syscall
		move $a0,$t1
		li $v0,1
		syscall		
		la $a0,tesp
		li $v0,4
		syscall
		move $a0,$t2
		li $v0,1
		syscall	
		la $a0,tvoc
		li $v0,4
		syscall
		move $a0,$t3
		li $v0,1
		syscall	
		la $a0,tcon
		li $v0,4
		syscall
		move $a0,$t4
		li $v0,1
		syscall	
		la $a0,tnum
		li $v0,4
		syscall
		move $a0,$t5
		li $v0,1
		syscall	
		la $a0,tsig
		li $v0,4
		syscall
		move $a0,$t6
		li $v0,1
		syscall	