;---------------------------------------------------------------------    
; grafica.asm 
; Funciones gráficas y de entrada/salida por teclado
;---------------------------------------------------------------------    

EXTRN 	rata:word

;---------------------------------------------------------------------    
; Declaramos el segmento de CODIGO
;---------------------------------------------------------------------    
CODIGO3 SEGMENT 
	ASSUME CS:CODIGO3

;---------------------------------------------------------------------    
; A continuación declaramos los siguientes procedimientos como PUBLIC para 
; que sean accesibles desde otros módulos que serán montados conjuntamente.
;---------------------------------------------------------------------    

PUBLIC Ini_Graf, Modo_texto, Linea_Vertical, Linea_Horizontal, Put_pixel
PUBLIC Lee, Lee_eco, Lee_no_espera, keypressed, Escribecad, PosCursor, EscribeCar 
PUBLIC Linea_Bresenham,Circunferencia_Bresenham,CircunferenciaPoint

;---------------------------------------------------------------------    
; Procedimiento que borra la pantalla y fija el modo grafico a 320x200 256 col.
;---------------------------------------------------------------------    
Ini_Graf proc far
     mov ah,6       ; Borrado de la pantalla
     mov al,0       ;    
     mov ch,0       ;
     mov cl,0       ;
     mov dh,23      ;
     mov dl,79      ;
     mov bh,7       ;
     int 10h        ; Se ejecuta el borrado
     mov al,13h     ; fijar modo 320x200 256 colores
     mov ah,0       ; Función de la Int 10h 
     int 10h        ; Interrupción BIOS
     ret            ; Devolvemos el control
Ini_graf endp

;---------------------------------------------------------------------    
; Este procedimiento vuelve a poner el modo texto 80x25 color
;---------------------------------------------------------------------    
Modo_Texto proc far
     mov al,3       ; Modo 80x25
     mov ah,0       ; Función de la Int 10h
     int 10h        ; Interrupción BIOS
     ret            ; Devolvemos el control
Modo_Texto endp

;---------------------------------------------------------------------    
; Procedimiento que pinta un pixel en pantalla.
; Parametros de entrada:
;       CX ----> Coordenada X
;       DX ----> Coordenada Y
;       AL ----> Color del pixel
;---------------------------------------------------------------------    
Put_Pixel proc far
     push ax        ; Guardamos el registro AX que vamo a modificar
     mov ah,12      ; Indicamos que queremos pintar un pixel
     int 10h        ; Llamamos a la interrupción BIOS
     pop ax         ; Restauramos el registro AX
     ret            ; Devolvemos el control
Put_Pixel endp
		
;---------------------------------------------------------------------    
; Procedimiento que pinta una linea horizontal 
; Parametros de entrada:
;           CX ----> Coordenada X 
;           DX ----> Coordenada Y 
;           AL ----> Color de la linea 
;           BX ----> Longitud de la linea
;---------------------------------------------------------------------    
Linea_Horizontal proc far
     push cx        ; Guardamos los registros 
     push dx        ;
     push ax        ;
     push bx        ;
sigue_h:
     call put_pixel ; Pintamos el pixel
     dec bx         ; Decrementamos el contador de }longitud
     inc cx         ; Incrementamos la coordenada X
     cmp bx,0       ; Vemos si ya hemos pintado BX pixels
     jne sigue_h    ; Si no los hemos pintado seguimos pintando

     pop bx         ; Restauramos los registros
     pop ax         ;
     pop dx         ;
     pop cx         ;
	ret
Linea_Horizontal endp

;---------------------------------------------------------------------    
; Procedimiento que pinta una linea vertical 
; Parámetros de entrada:
;               CX----> Coordenada X
;               DX----> Coordenada Y
;               AL----> Color de la linea
;               BX----> Longitud de la línea
;---------------------------------------------------------------------    
Linea_Vertical proc far
	push cx        ; Guardamos los registros
	push dx        ;
	push ax        ;
	push bx        ;
sigue_v:
     call put_pixel ; Pintamos el pixel
     dec bx         ; Decrementamos el contador de longitud
     inc dx         ; Incrementamos la coordenada Y
     cmp bx,0       ; Vemos si ya hemos pintado BX pixels
     jne sigue_v    ; Si no los hemos pintado seguimos pintando
     pop bx         ; Restauramos los registros
	pop ax         ;     
	pop dx         ;
	pop cx         ;
	ret
Linea_Vertical endp

;---------------------------------------------------------------------    
; FUNCION: Lee una letra del teclado y la escribe en pantalla (Con ECO)
; DEVUELVE: En AL, devuelve el carácter ASCII o tecla si codigo extendido.
;---------------------------------------------------------------------    
Lee_eco Proc far
     mov ah, 1      ; Funcion 1 
	int 21h        ; Ejecuta la interrupción 21 
	cmp al,0       ; Comprueba si código extendido 
	jne no_ex      ; Si no extendido AL contiene el cód. ASCII 
	int 21h        ; Ejecuta la interrupción 21, AL contiene la tecla 
no_ex:
     ret            ; retorna el valor  ;
Lee_eco Endp
		
;---------------------------------------------------------------------    
; FUNCION: Lee una letra del teclado sin escribirla en pantalla (Sin ECO) 
; DEVUELVE: En AL, devuelve el carácter ASCII o tecla si código extendido.
;-------------------<--------------------------------------------------    
Lee Proc far
     mov ah,7       ; Función 7
     int 21h        ; Ejecuta la interrupción 21
     cmp al,0       ; Comprueba si código extendido
     jne no_ex1     ; Si no extendido AL contiene el cód. ASCII
     int 21h        ; Ejecuta la interrupción 21, AL contiene la tecla
no_ex1:
     ret            ; Retorna el valor
Lee Endp

;---------------------------------------------------------------------    
; FUNCION: Lee una letra del teclado sin esperar y sin ECO 
; DEVUELVE: En AL, devuelve el carácter ASCII o tecla si codigo extendido.
;---------------------------------------------------------------------    
Lee_no_espera Proc far
     push dx 
     mov dl,0ffh    ; Función para las entradas de teclado 
     mov ah,6       ; Función 6 
     int 21h        ; Ejecuta la interrupción 21 
     cmp al,0       ; Comprueba si código extendido 
     jne no_ex2     ; Si no extendido AL contiene el cód. ASCII 
     int 21h        ; Ejecuta la interrupción 21, AL contiene la tecla 
no_ex2:
     pop dx         ; Recuperamos los registros
     ret            ; Retorna el valor; 
Lee_no_espera Endp 

;---------------------------------------------------------------------    
; Función que comprueba si se ha pulsado un tecla 
; Devuelve: En AL. Si AL = 255, se ha pulsado una tecla
;---------------------------------------------------------------------    
KEYPRESSED proc far 
     mov ah, 11 
     int 21h 
     ret
KEYPRESSED endp

;---------------------------------------------------------------------    
; Este procedimiento escribe una frase en pantalla, la cadena debe estar en la direccion DX (p.e LEA DX,texto)
;---------------------------------------------------------------------
EscribeCad proc far
     push ax        ;guarda los registros afectados
     mov ah, 9
     int 21h
     pop ax
     ret
EscribeCad endp

;---------------------------------------------------------------------    
; Escribe un caracter en pantalla en la posición donde se encuentra el cursor
; AL <- codigo ascii del caracter 
; BH <- color de fondo del caracter
; BL <- color del caracter
;---------------------------------------------------------------------    
EscribeCar proc far
     push ax        ;guarda los registros afectados
     push bx        
     push cx        

     mov ah, 09h
     mov cx,1

     int 10h

     pop cx
     pop bx
     pop ax
     ret
EscribeCar endp

;------------------------------------
; Función que posiciona el cursor en:
; DH <- Fila (y)
; DL <- Columna (x)
;------------------------------------
PosCursor proc far

	push DX
	push BX
	push AX

	mov bh, 0
	mov ah, 2
	int 10h

	pop AX
	pop BX
	pop DX

	ret
PosCursor endp 

;------------------------------------
; Función que pinta una linea siguiendo el algoritmo de bresenham
; DX <- x1
; SI <- y1
; BX <- x2
; CX <- y2
; AL <- Color de la linea
;------------------------------------
Linea_Bresenham proc far

	push DX
	push BX
	push AX
	push CX
	push SI
	push DI

	push ax						;color
	push bx						;x2
	push cx						;y2
	push dx						;x1
	push si						;y1

	;incrementos iniciales
	mov si,1
	mov di,1

	;diferencia y2-y1
	pop ax						;recuperamos y1
	push ax						;almaceno y1
	sub cx,ax
	jge almay					;bifurcar si y2 - y1 es no negativo
	neg di
	neg cx

almay:
	push di						;deldy
	
	;diferencia x2-x1
	sub bx,dx
	jge almax
	neg si
	neg bx

almax:
	push si						;deldx
	
	;clasificar y2-y1 y x2-x1
	cmp bx,cx					;compara delr con delp
	jge mover 					;bifurcar si recta en direccion x
	mov si,0 					;si linea vertical incremento de x=0
	xchg bx,cx
	jmp alma

mover:
	mov di,0					;si linea horizontal, incremento de y = 0

	;almacenar delr,delp,delrx y delry
alma:
	push bx						;delr
	push cx						;delp
	push si						;delrx
	push di						;delry

	;calcular valor inicial e incrementos para la funcion de error
	mov ax,cx					;ax <- delp
	mov cx,bx					;cx <- delr
	sal ax,1
	push ax						;delre

	sub ax,cx					;2*delp - delr
	mov bx,ax

	sub ax,cx					;2*delp - 2*delr (cambio si movimiento diagonal)
	push ax						;delde

	;ajustar contador
	inc cx

	;recupero valores iniciales x1 e y1
	mov bp,sp
	mov dx,ss:[bp+16]			;dx <- y1
	
	;bucle principal
bucle:
	push cx
		
	mov cx,ss:[bp+18]			;cx <- x
	mov al,byte ptr ss:[bp+24]	;al <- color

	Call put_pixel
	
	cmp bx,0
	jge diagonal
	
recta:
	add cx,ss:[bp+6]	;delrx
	mov ss:[bp+18],cx	;x
	add dx,ss:[bp+4]	;y + delry
	add bx,ss:[bp+2]	;delre
	pop cx
	loop bucle
	jmp fin

diagonal:
	;linea diagonal
	add cx,ss:[bp+12]	;deldx
	mov ss:[bp+18],cx	;x
	add dx,ss:[bp+14]	;deldy
	add bx,ss:[bp]		;delde	
	pop cx
	loop bucle

fin:
	pop ax				;delde
	pop ax				;delre
	
	pop di				;delry
	pop si				;delrx
	pop cx				;delp
	pop bx				;delr
	
	pop si				;deldx
	pop di				;deldy

	pop ax				;y1
	pop dx				;x1
	pop cx				;y2
	pop bx				;x2
	pop ax				;color

	pop DI
	pop SI
	pop CX
	pop AX
	pop BX
	pop DX

	ret
Linea_Bresenham endp

; -------------------------------------------------------
; Circunferencia_Bresenham: Rutina para desplegar una circunferencia en modo 13h.
;          Implementacion del algoritmo de Bresenham
;	      para dibujar circunferencias
; Parametros: 
;           CX ----> CentroX 
;           DX ----> CentroY 
;           AL ----> Color de la linea 
;           BX ----> Radio
; -------------------------------------------------------
;	rata = 1.0
;	delta = 3-2*radio
;	x=0
;	y=radio
;	while (x<y) {
;		CircunferenciaPoint(x,y,CentroX,CentroY,color)
;		if(delta<0) {
;			delta+=(4*x)+6
;			x++
;		} else {
;			delta+=(4*(x-y)+10)
;			y--
;			x++
;		}
;	}
;	x=y
;	if(y=0) CircunferenciaPoint(x,y,CentroX,CentroY,color)
; -------------------------------------------------------
Circunferencia_Bresenham	proc	far

	push	si
	push	di
	push	bx

	push	ax							; color
	push	bx							; radio
	push	dx							; centroY
	push	cx							; centroX
	
	push	bp
	mov	bp,sp
	sub	sp,2
	
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;	Estado de la pila
;			-----------------------------
;			|			delta			| <- sp
;			-----------------------------
;			|			bp				| <- bp
;			-----------------------------
;			|			centroX			| +2
;			-----------------------------
;			|			centroY			| +4
;			-----------------------------
;			|			radio			| +6
;			-----------------------------
;			|			color			| +8
;			-----------------------------
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

; - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;	int x, y, delta;
;		rate=1.0;
; Uses the math copprocesor to set 0 in "delta" variable
; - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	fld1	
	fstp	qword ptr rata
; - - - - - - - - - - - - - - - - 
;		y=radio;
; - - - - - - - - - - - - - - - - 
	mov	di,word ptr ss:[bp+6]			; radio
; - - - - - - - - - - - - - - - - 
;		delta=3-2*radio;
; - - - - - - - - - - - - - - - - 
	mov	ax,word ptr ss:[bp+6]			; radio
	shl	ax,1							; radio*2
	mov	dx,3
	sub	dx,ax							; 3 - (radio*2)
	mov	word ptr ss:[bp-2],dx			; delta=[bp-2], (var. local)
; - - - - - - - - - - - - - - - - 
;		for(x=0; x<y; ) {
; - - - - - - - - - - - - - - - - 
	xor	si,si							; SI = x = 0
	jmp	FOR1END
FOR1INIT:
; - - - - - - - - - - - - - - - - - - - -  
;	CircunferenciaPoint(x, y, orX, orY, color);
; - - - - - - - - - - - - - - - - - - - -  
	; Dibujar un punto del circulo	
	push dx
	push si
	push bx
	push cx
	push ax
	
	mov ax,word ptr ss:[bp+8]			; color 
	mov dx,word ptr ss:[bp+2]			; orX: coordenada x del centro
	mov bx,si							; x
	mov si,word ptr ss:[bp+4]			; orY: coordenada y del centro
	mov cx,di							; y <=> radio
	call CircunferenciaPoint
	
 	pop ax
	pop cx
	pop bx
	pop si
	pop dx
		
; - - - - - - - - - - - - - - - - - - 
;	if (delta < 0)
; - - - - - - - - - - - - - - - - - - 
	cmp	word ptr ss:[bp-2],0			; delta tiene un valor negartivo?
	jge	 ELSE1

; -------------------------------
; Si d>0, sólo se incrementará x:
;	x:=x+1		d:= d+4x+6
; -------------------------------

; - - - - - - - - - - 
;	delta += 4*x+6;
; - - - - - - - - - - 
	mov	ax,si
	shl	ax,1							; x*2
	shl	ax,1							; x*2
	add	ax,6							; x+6
	add	word ptr ss:[bp-2],ax			; delta:=delta+(4*x+6)
	jmp	 ENDIF1
ELSE1:
; -------------------------------------------------------
; si d<=0, entonces, se incrementan x e y se disminuirá:
;	x:= x+1		y:= y-1		d:= d+4(x-y)+10
; -------------------------------------------------------

; - - - - - - - - - - - - - - - - - 
;	else {
;		delta += 4*(x-y)+10;
; - - - - - - - - - - - - - - - - - 
	mov	ax,si
	sub	ax,di							; x-y
	shl	ax,1							; (x-y)*2
	shl	ax,1							; (x-y)*2
	add	ax,10							; (x-y)*2 + 10
	add	word ptr ss:[bp-2],ax			; delta:=(x-y)*2 + 10
; - - - - - - - - - - - - - - - - - 
; 	y--;
; - - - - - - - - - - - - - - - - - 
	dec	di								; disminuir y
ENDIF1:
; - - - - - - - - - - - - - - - - - 
;	x++;
; - - - - - - - - - - - - - - - - - 
	inc	si								; incrementar x
FOR1END:
	cmp	si,di
	jl	 FOR1INIT
; - - - - - - - - - - - - - - - - - 
;	x=y;
; - - - - - - - - - - - - - - - - - 
	mov	si,di							; x:=y
; - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;		if(y) CircunferenciaPoint(x, y, orX, orY, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	or	di,di							; y es cero?
	je	 ENDIF2

	push dx
	push si
	push bx
	push cx
	push ax
	
	mov ax,word ptr ss:[bp+8]			; color 
	mov dx,word ptr ss:[bp+2]			; orX: coordenada x del centro
	mov bx,si							; x
	mov si,word ptr ss:[bp+4]			; orY: coordenada y del centro
	mov cx,di							; y <=> radio
	call CircunferenciaPoint
	
 	pop ax
	pop cx
	pop bx
	pop si
	pop dx

ENDIF2:
	mov	sp,bp
	pop	bp
	
	pop	cx							; centroX
	pop	dx							; centroY
	pop	bx							; radio
	pop	ax							; color	
	
	pop	bx
	pop	di
	pop	si
	
	ret 
Circunferencia_Bresenham	endp

; -------------------------------------------------------
;	void CircunferenciaPoint(int x, int y, int orX, int orY, int color) {
; DX <- centroX
; SI <- centroY
; BX <- X
; CX <- Y <=> Radio
; AL <- Color
; -------------------------------------------------------
;	put_pixel(centroX + X , centroY + Y, color)
;	put_pixel(centroX + X , centroY - Y, color)
;	put_pixel(centroX - X , centroY + Y, color)
;	put_pixel(centroX - X , centroY - Y, color)

;	put_pixel(centroX + Y , centroY + X, color)
;	put_pixel(centroX + Y , centroY - X, color)
;	put_pixel(centroX - Y , centroY + X, color)
;	put_pixel(centroX - Y , centroY - X, color)
; -------------------------------------------------------
CircunferenciaPoint	proc	far

	push	si
	push	di
	push	bx

	push	ax							; color
	push	si							; centroY
	push	dx							; centroX
	push	cx							; Y
	push	bx							; X

	push	bp
	mov	bp,sp
	sub	sp,14
	
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
;	Estado de la pila
;			-----------------------------
;			|							| <-sp
;			-----------------------------
;			|			y1				| -12
;			-----------------------------
;			|			end_y			| -10
;			-----------------------------
;			|			begin_y			| -8
;			-----------------------------
;			|			x1				| -6
;			-----------------------------
;			|			end_x			| -4
;			-----------------------------
;			|			begin_x			| -2
;			-----------------------------
;			|			bp				| <- bp
;			-----------------------------
;			|			X				| +2
;			-----------------------------
;			|			Y				| +4
;			-----------------------------
;			|			centroX			| +6
;			-----------------------------
;			|			centroY			| +8
;			-----------------------------
;			|			color			| +10
;			-----------------------------
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - 


	mov	si,word ptr ss:[bp+2]			; x
	mov	di,word ptr ss:[bp+4]			; radio
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;		int begin_x, end_x, x1, begin_y, end_y, y1;
;		begin_y = y*rata;
; This multiplies a int (x) by a real number (rata) 
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	mov	ax,word ptr ss:[bp+4]
	mov	word ptr ss:[bp-14],ax
	fild	word ptr ss:[bp-14]			; 
	fmul	qword ptr rata				; y*rata

	Call nftol							; (y*rata) float point to long integer
	mov	word ptr ss:[bp-8],ax			; int begin_y
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;		end_y = (y+1)*rata;
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	mov	ax,word ptr ss:[bp+4]
	inc	ax								; y+1
	mov	word ptr ss:[bp-14],ax
	fild	word ptr [bp-14]			;
	fmul	qword ptr rata				; (y+1) * rata
	Call nftol							; Float Point To Long Integer
	mov	word ptr ss:[bp-10],ax			; int end_y
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;		begin_x = x*rata;
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	mov	ax,word ptr ss:[bp+2]
	mov	word ptr ss:[bp-14],ax			; x
	fild	word ptr ss:[bp-14]			;
	fmul	qword ptr rata				; x*rata
	Call nftol							; Float Point To Long Integer
	mov	word ptr ss:[bp-2],ax			; int begin_x
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;		end_x = (x+1)*rata;
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	mov	ax,word ptr ss:[bp+2]
	inc	ax								; x+1
	mov	word ptr ss:[bp-14],ax			;
	fild	word ptr ss:[bp-14]	; 
	fmul	qword ptr rata				; (x+1) * rata
	Call nftol							; Float Point To Long Integer
	mov	word ptr ss:[bp-4],ax			; int end_x
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;		for (x1=begin_x; x1<end_x; ++x1) {
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	mov	ax,word ptr ss:[bp-2]			; int begin_x
	mov	word ptr ss:[bp-6],ax
	jmp	ENDFOR2

BEGINFOR2:
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(x1+orX, y+orY, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	mov ax, word ptr ss:[bp+10]			; <- color
	mov	dx,word ptr ss:[bp+8]			; y+orY
	add dx,di
	mov	cx,word ptr ss:[bp+6]			;x1+orX
	add cx,word ptr ss:[bp-6]

	Call Put_Pixel
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(x1+orX, orY-y, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	;mov ax, word ptr ss:[bp+10]		;<- color
	mov	dx,word ptr ss:[bp+8]			;orY-y
	sub dx,di
	;mov	cx,word ptr ss:[bp+6]		;x1+orX
	;add cx,word ptr ss:[bp-6]

	Call Put_Pixel		
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(orX-x1, orY-y, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	;mov ax, word ptr ss:[bp+10]		;<- color
	;mov	dx,word ptr ss:[bp+8]		;orY-y
	;sub dx,di
	mov	cx,word ptr ss:[bp+6]			;x1+orX
	sub cx,word ptr ss:[bp-6]

	Call Put_Pixel
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(orX-x1, y+orY, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	;mov ax, word ptr ss:[bp+10]		;<- color
	mov	dx,word ptr ss:[bp+8]			; y+orY
	add dx,di
	;mov	cx,word ptr ss:[bp+6]		;x1+orX
	;sub cx,word ptr ss:[bp-6]

	Call Put_Pixel	
	
	inc	word ptr ss:[bp-6]
ENDFOR2:
	mov	ax,word ptr ss:[bp-6]
	cmp	ax,word ptr ss:[bp-4]
	jl BEGINFOR2

; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;		for (y1=begin_y; y1<end_y; ++y1) {
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	mov	ax,word ptr ss:[bp-8]
	mov	word ptr ss:[bp-12],ax
	jmp	ENDFOR3
BEGINFOR3:
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(y1+orX, x+orY, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	mov ax, word ptr ss:[bp+10]			;<- color
	mov	dx,word ptr ss:[bp+8]			; x+orY
	add dx,si
	mov	cx,word ptr ss:[bp+6]			;y1+orX
	add cx,word ptr ss:[bp-12]

	Call Put_Pixel	
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(y1+orX, orY-x, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	;mov ax, word ptr ss:[bp+10]		;<- color
	mov	dx,word ptr ss:[bp+8]			; orY-x
	sub dx,si
	;mov	cx,word ptr ss:[bp+6]		;y1+orX
	;add cx,word ptr ss:[bp-12]
	
	Call Put_Pixel	
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(orX-y1, orY-x, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	;mov ax, word ptr ss:[bp+10]		;<- color
	;mov	dx,word ptr ss:[bp+8]		; orY-x
	;sub dx,si
	mov	cx,word ptr ss:[bp+6]			;orX-y1
	sub cx,word ptr ss:[bp-12]

	Call Put_Pixel	
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;			PutPix(orX-y1, x+orY, color);
; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	
	;mov ax, word ptr ss:[bp+10]		;<- color
	mov	dx,word ptr ss:[bp+8]			; x+orY
	add dx,si
	;mov	cx,word ptr ss:[bp+6]		;orX-y1
	;sub cx,word ptr ss:[bp-12]

	Call Put_Pixel	

	inc	word ptr ss:[bp-12]
ENDFOR3:
	mov	ax,word ptr ss:[bp-12]
	cmp	ax,word ptr ss:[bp-10]
	jl	BEGINFOR3

	mov	sp,bp
	pop	bp
	
	pop	bx							; X
	pop	cx							; Y
	pop	dx							; centroX
	pop	si							; centroY
	pop	ax							; color
			
	pop	bx
	pop	di
	pop	si
	
	ret 	
CircunferenciaPoint	endp

; -------------------------------------------------------
; nftol: Float Point To Long Integer
; Proposito: Convierte valor real en entero
; -------------------------------------------------------
nftol		proc
	push	bp
	
	mov	bp,sp
	sub	sp,10

	fstcw	word ptr ss:[bp-2]
	mov	al, ss:[bp-1]
	or	byte ptr ss:[bp-1], 0Ch
	fldcw word ptr ss:[bp-2]
	fistp qword ptr ss:[bp-10]
	mov	ss:[bp-1], al
	fldcw word ptr ss:[bp-2]
	mov	ax, ss:[bp-10]
	mov	dx, ss:[bp-8]
	
	mov	sp, bp

	pop	bp
	
	ret
nftol		endp


CODIGO3 ENDS   ; FINAL DEL SEGMENTO DE CODIGO

END

