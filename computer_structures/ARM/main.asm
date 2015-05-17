;..........................................................................
; Declaraciones de funciones definidas en otros archivos "*.asm"
;..........................................................................

EXTRN Ini_graf: far
EXTRN Modo_texto: far
EXTRN Escribecar: far
EXTRN Escribecad: far
EXTRN Lee_eco: far
EXTRN Lee:far
EXTRN Lee_no_espera:far
EXTRN hacer_retardo: far
EXTRN PosCursor: far
EXTRN keypressed: far
EXTRN Show_Mouse: far
EXTRN Hide_Mouse: far
EXTRN HayDriver: far
EXTRN BotonDer: far
EXTRN BotonIzq: far
EXTRN GetXY: far
EXTRN Cuadrado:far
EXTRN Circunferencia_Bresenham:far
EXTRN Linea_Bresenham:far
EXTRN retardo:far


include macros.asm
include const.asm



;..........................................................................
; Declaración de la PILA
;..........................................................................


PILA SEGMENT PARA STACK 'stack'
     db 512 dup (?)
PILA ENDS


;----------------------------------------------------------------------------
; Segmento de datos donde se declaran todas las variables del programa
;----------------------------------------------------------------------------
DATOS   SEGMENT PARA PUBLIC 'data'

;----------------------------------------------------------------------------
; Todas son declaradas como publicas
;----------------------------------------------------------------------------
        ;PUBLIC modo,sonido;.......... RESTO DE VARIABLES
		PUBLIC rata

;----------------------------------------------------------------------------                                                                             
; Variables que son cadenas 
;----------------------------------------------------------------------------
        angulo_90 db "90 º$"
		angulo db "       "
		longitud db 7
		findollar db " º$"
		positivo db ?
        
       
		rata	db	8 dup (?)
		;ultima posicion en la que se encontraba el raton
		act_x	dw ?
		act_y	dw ?
				
		;ultima posicion pulsada por el raton		
		act_x_pulsado dw circunf_x
		act_y_pulsado dw circunf_y
		
		aux dw 0

		pendiente dw ?

		;Mapeado de datos		;primer cuadrante(arriba izquierda)					 ;segundo cuadrante(arriba derecha)
		m_angulo dw 		0,	5, 10,	15,	20,	25,	30,	35,	40,	45,	50,	55,	60,	65,	70,	75,	80,	85,	90,		0
		m_pendiente dw		0,	4,	13,	22,	31,	41,	52,	63,	76,	91,	109,130,157,192,241,317,451,759,2290,	32767
		
		cursor_x dw cursor_x_ini
		cursor_y dw cursor_y_ini


DATOS   ENDS



CODIGO SEGMENT
     ASSUME SS:PILA, CS:CODIGO, DS:DATOS

;---------------------------------------------------------------------
; PROCEDIMIENTO PRINCIPAL.
;---------------------------------------------------------------------
PPAL    PROC    FAR
        ASSUME  CS:CODIGO,DS:DATOS,SS:PILA
        push    DS
        xor     AX,AX
        push    AX
        mov     AX,SEG DATOS
        mov     DS,AX

        ;................
        ;................
        ;................
        ;................
		
	Call Ini_graf
	
	Call Show_Mouse
	
	;call lee;esperamos que se pulse una tecla para iniciar el juego
	
	;iniciamos la pantalla
	pintar_cuadrado	
	
	pintar_puntero cursor_x_ini, cursor_y_ini 
	pintar_angulo angulo_90
	
  inicio:  
  
	;hacemos un retardo de 40ms
	mov bx, 40
	mov dx, ciclos_1ms
	call hacer_retardo
	
 ;----------------Actualizacion del cursor--------------------
	;primero borramos el cursor anterior
	borrar_puntero cursor_x,cursor_y
	;obtenemos las coordenadas de la posicion actual del raton.
	Call GetXY
	shr cx,1;GetXY nos da el doble de la cordenada x, asike dividimos x 2
	mov act_x, cx 
	mov act_y, dx
	pasar_a_coordenadas act_x, act_y
	;hallamos la pendiente
	get_pendiente act_x,act_y,pendiente
	 
	 
	 ;ponemos bx en la posicion que "nos toca" segun la pendiente:
	 xor bx,bx;ponemos bx a 0
	 mov ax, pendiente
	 
	 cmp act_y,0;vemos si esta en la parde de arriba o de abajo
	 jl abajo
	 
	 ;arriba:
	 cmp act_x,0;estando arriba vemos si es derecha o izquierda
	 jl izquierda1
	 jmp derecha1
	 
	 abajo:
	 cmp act_x,0;estando abajo vemos si es derecha o izquierda
	 jge derecha2
	 jmp izquierda2	 
	 
;-------------------------------------------
	 izquierda2:
	 ;bx empieza en 0
	 bucle4:
		cmp ax, m_pendiente[bx+2]
		jl saliri2
		inc bx
		inc bx
		jmp bucle4
	
	saliri2:	;calculamos los nuevos x,y del cursor y el angulo
		mov cursor_x,circunf_x-circunf_radio
		mov cursor_y,circunf_y

		mov ax, bx
		shr ax,1
		shr ax,1
		
		add cursor_x,ax
		add cursor_y,ax
		
		mov ax, 360
		sub ax, m_angulo[bx]
		mov aux, ax
		
		itoa aux,angulo,longitud,positivo

		jmp apintar
	 
	 
;-------------------------------------------	 
	 derecha2:
	 ;bx empieza en 0
	 NOT ax
	 bucle3:
		cmp ax, m_pendiente[bx+2]
		jl salird2
		inc bx
		inc bx
		jmp bucle3
	
	salird2:	;calculamos los nuevos x,y del cursor y el angulo
		mov cursor_x,circunf_x+circunf_radio
		mov cursor_y,circunf_y

		mov ax, bx
		shr ax,1
		shr ax,1
		
		sub cursor_x,ax
		add cursor_y,ax

		mov ax, 180
		add ax, m_angulo[bx]
		mov aux, ax
		
		itoa aux,angulo,longitud,positivo
		
		jmp apintar
;-------------------------------------------	 
	 derecha1:
	 ;bx empieza en 0
	 bucle1:
		cmp ax, m_pendiente[bx+2]
		jl salird1
		inc bx
		inc bx
		jmp bucle1
	
	salird1:	;calculamos los nuevos x,y del cursor y el angulo
		mov cursor_x,circunf_x+circunf_radio
		mov cursor_y,circunf_y

		mov ax, bx
		shr ax,1
		shr ax,1
		
		sub cursor_x,ax
		sub cursor_y,ax

		mov ax, 180
		sub ax, m_angulo[bx]
		mov aux, ax
		itoa aux,angulo,longitud,positivo
		
		jmp apintar
;-------------------------------------------	 
	 
	 izquierda1:
	 ;bx empieza en 0
	 NOT ax; pasamos la pendiente a positiva
	 bucle:
		cmp ax, m_pendiente[bx+2]
		jl saliri1
		inc bx
		inc bx
		jmp bucle
	
	saliri1:	;calculamos los nuevos x,y del cursor y el angulo
		mov cursor_x,circunf_x-circunf_radio
		mov cursor_y,circunf_y

		mov ax, bx
		shr ax,1
		shr ax,1
		
		add cursor_x,ax
		sub cursor_y,ax
		itoa m_angulo[bx],angulo,longitud,positivo

		 jmp apintar
;-------------------------------------------
	
	apintar:
	
	
	
	
  	;actualizamos el cursor
     pintar_cuadrado	
	 pintar_puntero cursor_x,cursor_y
	 pintar_angulo angulo
 ;------------------------------------------------------------
  	;Si se pulsa escape salimos
	xor al,al
	Call Lee_no_espera
	CMP al, ESCAPE
	JE salir
	
	
	;Compropacion del boton derecho del raton
	Call BotonDer
	CMP al, 1
	JE pulsado
	;no se ha pulsado el boton derecho
	
	;Compropacion del boton izquierdo del raton
	Call BotonIzq
	CMP al, 1
	JE pulsadoIzq
	;no se ha pulsado el boton derecho
	
	
	jmp inicio
;-------------------------------------------------------;
	;se ha pulsado el boton derecho del raton	
  pulsado:
	alargar_cursor act_x_pulsado,act_y_pulsado, pendiente
	jmp inicio
;-------------------------------------------------------;	

;-------------------------------------------------------;
	;se ha pulsado el boton izquierdo del raton	
  pulsadoIzq:
	borrar;borra la pantalla
	pintar_cuadrado	
	jmp inicio
;-------------------------------------------------------;	


salir:	
	Call Hide_Mouse
	
	Call Modo_texto
	
    ret
PPAL    ENDP

;----------------------------------------------------------------------------
; Fin del segmento de codigo
;----------------------------------------------------------------------------
CODIGO ENDS
END     PPAL
