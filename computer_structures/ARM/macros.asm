
include const.asm

;alarga la linea del cursor y borra la anterior
alargar_cursor macro x,y,pendiente
	local fin, izquierda1,derecha1,derecha2,izquierda2, abajo,cont
    ;borramos la ultima linea
	mov bx, x
	mov cx, y
	mov dx, circunf_x
	mov si, circunf_y
	mov al, 0
  	Call Linea_Bresenham
	
	;comprobamos si la pendiente es igual a 0 (nos dara problemas al dividir por la pendiente)
	cmp pendiente,0
	jne cont
	inc pendiente
	cont:
	
	;obtenemos la posicion del raton
	Call GetXY
	shr cx,1;GetXY nos da el doble de la cordenada x, asike dividimos x 2
	mov x,cx
	mov y, dx

	
	 cmp y,circunf_y;vemos si esta en la parde de arriba o de abajo
	 jnl abajo
	 
	 ;arriba:
	 cmp x,circunf_x;estando arriba vemos si es derecha o izquierda
	 jl izquierda1
	 jmp derecha1
	 
	 abajo:
	 cmp x,circunf_x;estando abajo vemos si es derecha o izquierda
	 jge derecha2
	 jmp izquierda2	 
;-----------------------------------------------
	izquierda1:
	;supongamos que apunta hacia la linea horizontal(superior) y = cuadrado_y
	mov y, cuadrado_y
	pasar_y_a_coordenadas y
	mov ax, y
	mov bx, 100
	mul bx
	mov bx, pendiente
	xor dx,dx
	cmp bx,0
	idiv bx
	mov x, ax
	
	;comprobamos si es un valor valido:
	cmp x, cuadrado_x-circunf_x
	jg fin
	
	;sino, apunta hacia la linea vertical(izquierda) x= cuadrado_x
	mov x, cuadrado_x
	pasar_x_a_coordenadas x

	mov ax, x
	mov bx, pendiente
	mul bx
	
	mov bx, 100;dividmos por 100, ya que la pendiente estaba aumentada 100 veces(para tomar decimales)
	xor dx,dx
	div bx
	
	mov y,ax
	
	jmp fin
;-----------------------------------------------
	derecha1:
	;supongamos que apunta hacia la linea horizontal(superior) y = cuadrado_y
	mov y, cuadrado_y
	pasar_y_a_coordenadas y
	mov ax, y
	mov bx, 100
	mul bx
	mov bx, pendiente
	xor dx,dx
	idiv bx
	mov x, ax
	
	;comprobamos si es un valor valido:
	cmp x, (cuadrado_x+cuadrado_ancho)-circunf_x
	jng fin
	
	;sino, apunta hacia la linea vertical(derecha) x= cuadrado_x+cuadrado_ancho
	mov x, cuadrado_x+cuadrado_ancho
	pasar_x_a_coordenadas x

	mov ax, x
	mov bx, pendiente
	mul bx
	
	mov bx, 100;dividmos por 100, ya que la pendiente estaba aumentada 100 veces(para tomar decimales)
	xor dx,dx
	div bx
	
	mov y,ax
	
	jmp fin
;-----------------------------------------------
	izquierda2:
	;supongamos que apunta hacia la linea horizontal(inferior) y = cuadrado_y+cuadrado_alto
	mov y, cuadrado_y+cuadrado_alto
	pasar_y_a_coordenadas y
	mov ax, y
	NOT ax
	mov bx, 100
	mul bx
	mov bx, pendiente
	xor dx,dx
	idiv bx
	NOT ax
	mov x, ax

	;comprobamos si es un valor valido:
	cmp x, cuadrado_x-circunf_x
	jg fin
	
	;sino, apunta hacia la linea vertical(izquierda) x= cuadrado_x
	mov x, cuadrado_x
	pasar_x_a_coordenadas x

	mov ax, x
	NOT ax
	mov bx, pendiente
	imul bx
	
	mov bx, 100;dividmos por 100, ya que la pendiente estaba aumentada 100 veces(para tomar decimales)
	xor dx,dx
	idiv bx
	NOT ax
	mov y,ax
	jmp fin
;-----------------------------------------------
	derecha2:

	;supongamos que apunta hacia la linea horizontal(inferior) y = cuadrado_y+cuadrado_alto
	mov y, cuadrado_y+cuadrado_alto
	pasar_y_a_coordenadas y
	mov ax, y
	NOT ax
	mov bx, 100
	mul bx
	mov bx, pendiente
	xor dx,dx
	idiv bx
	NOT ax
	mov x, ax

	;comprobamos si es un valor valido:
	cmp x, (cuadrado_x+cuadrado_ancho)-circunf_x
	jng fin
	
	;sino, apunta hacia la linea vertical(derecha) x= cuadrado_x+cuadrado_ancho
	mov x, cuadrado_x+cuadrado_ancho
	pasar_x_a_coordenadas x

	mov ax, x
	mov bx, pendiente
	not bx
	imul bx
	
	mov bx, 100;dividmos por 100, ya que la pendiente estaba aumentada 100 veces(para tomar decimales)
	xor dx,dx
	idiv bx
	not ax
	mov y,ax
	
	jmp fin
;-----------------------------------------------
	;paredes verticales:
	verticales:
	
	fin:

	revertir_coordenadas x,y
	;pintamos la linea
	mov bx, x
	mov cx, y
	mov dx, circunf_x
	mov si, circunf_y
	mov al, 7
	
	Call Linea_Bresenham

endm



;hallar la pendiente(Vamos a trabajar con la pendiente * 100, para "coger" decimales)
get_pendiente macro act_x,act_y,pendiente
	local salir,dividendoneg,dividir,dividir1
	push si
	push ax
	push dx
	
	cmp act_y,0
	jl dividendoneg
	
	;-------------------Dividendo positivo
	 mov ax, act_y
	 mov si, 100
	 mul si
	 mov si, act_x
	 cmp si,0
	 jne dividir
	 inc si;si el divisor vale 0, lo incrementamos en 1, ya que si no, nos dara error
	 dividir:
	 xor dx,dx;ponemos dx a 0
	 idiv si
	 mov pendiente, ax
	 jmp salir
	 ;-------------------Dividendo negativo(pasamos el dividendo a positivo y cambio el signo del divisor)
	 dividendoneg:
	 mov ax, act_y
	 NOT ax
	 mov si, 100
	 mul si
	 mov si, act_x
	 NOT si
	 cmp si, 0
	 jne dividir1
	 inc si
	 dividir1:
	 xor dx,dx;ponemos dx a 0
	 idiv si
	 mov pendiente, ax
	 jmp salir
	 ;-------------------------
	 
	 
	 salir:
	 
	pop dx
	pop ax
	pop si


endm


;pasa los valores a cordenadas de nuestro juego
pasar_a_coordenadas macro x, y
	pasar_x_a_coordenadas x
	pasar_y_a_coordenadas y
endm

;pasa la x a coordenada de nuestro juego
pasar_x_a_coordenadas macro x
	mov ax, x
	sub ax, circunf_x
	mov x, ax
endm

;pasa la x a coordenada de nuestro juego	
pasar_y_a_coordenadas macro y
	mov ax,y
	sub ax,circunf_y
	NOT ax
	mov y, ax

endm

;revierte los valores de las cordenadas de nuestro juego
revertir_coordenadas macro x, y
	mov ax, x
	add ax, circunf_x
	mov x, ax
	
	mov ax,y
	NOT ax
	add ax,circunf_y
	mov y, ax

endm


;escribe el angulo pasado por parametro
pintar_angulo macro angulo

	mov dh, angulo_y
	mov dl, angulo_x
	Call PosCursor
	
	lea dx, angulo
	Call EscribeCad

endm

;Dibuja un cuadrado con los parametros
pintar_cuadrado macro

	mov cx, cuadrado_x
	mov dx, cuadrado_y
	mov ax, cuadrado_alto
	mov bx, cuadrado_ancho
	
	Call Cuadrado
	
endm

pintar_puntero macro x,y

	;dibujamos la circunferencia
	mov cx, circunf_x
	mov dx, circunf_y
	mov al, circunf_color
	mov bx, circunf_radio
	
	Call Circunferencia_Bresenham
	
	mov dx, circunf_x
	mov si, circunf_y
	mov bx, x
	mov cx, y
	mov al, cursor_color
	
	Call Linea_Bresenham
	
endm

borrar_puntero macro x,y

	mov dx, circunf_x
	mov si, circunf_y
	mov bx, x
	mov cx, y
	mov al, 0
	
	Call Linea_Bresenham
	
endm


itoa	macro numero,cadena,lon, positivo
	local relleno,bucle,jpositivo,fin11

	push ax
	push bx
	push cx
	push dx
	push si
	
	mov ax,numero
	mov positivo,1
	
	;comprobamos si es negativo
	cmp ax, 0
	jnl jpositivo
	NOT ax
	mov positivo, 0
	
	jpositivo:
	;rellenar cadena de salida con blancos (5 caracteres)
	mov cx,5
	mov bx,0
	
relleno:
	mov byte ptr cadena[bx], ' '		
	inc bx
	loop relleno
	
	mov si,10
	
	;obtenemos los numeros en decimal
bucle:
	xor dx,dx						;borrar mitad superior del dividendo (dividendo: dx, ax)

	div si							;dividir entre 10
									;ax = cociente, dx = resto

	add dl,'0'						;convertimos el resto a ASCII
	dec bx							; Indice cadena bx = bx - 1

	mov byte ptr cadena[bx],dl		;almacena el caracter en la cadena (de der. a izq.)
	
	inc cx							;incremento el numero de caracteres convertidos
	or ax,ax						;si ax = 0, zf = 1
	
	jnz bucle
	
	cmp positivo,0
	jne fin11
	dec bx
	mov cadena, '-'
	fin11:
	
	
	mov lon,cl						;mover cl = logintud de la cadena
	
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
endm

gastarciclos	macro random
	local retardo,retardo2

	push ax
	push bx
	push cx
	push dx
	push si

	Mov cx,random
retardo:
	push cx
	
	;bloque 1
	Mov ax,112
	Mov dx,421
	Mov si,11320
	Mov cx,65000

retardo2:
	push cx
	
	Mul dx
	Div si
	Mul ax
	Mul dx
	Mul ax
	Mul dx
	Div si
	
	pop cx
	loop retardo2
	
	Mul dx
	Div si
	Mul ax
	Div si
	Mul ax
	Mul dx
	Div si
	
	pop cx
	loop retardo	

	pop si
	pop dx
	pop cx
	pop bx
	pop ax
endm

borrar macro
         
        push ax
        push bx
        push cx
        push dx
        push di
        push si   
            
            mov cx,0
            mov dx,2479h
            mov al,0
            mov bh,0  ;color cursor
            mov ah,6  ;interrupcion
            int 10h  ;interrupcion
          
          pop si
          pop di
          pop dx
          pop cx
          pop bx
          pop ax 
            
         endm 
