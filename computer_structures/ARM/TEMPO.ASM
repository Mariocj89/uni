;---------------------------------------------------------------------    
; Tempo.asm 
; Funciones de control de la temporización y programacion del chip 8253
;---------------------------------------------------------------------    

include const.asm



;---------------------------------------------------------------------    
; A continuacion declaramos los siguientes procedimientos que han sido 
; declarados como public en otros modulos, y que utilizamos en este
;---------------------------------------------------------------------    

extrn lee_no_espera:far


;---------------------------------------------------------------------    
; Declaramos el segmento de CODIGO
;---------------------------------------------------------------------    
CODIGO2 SEGMENT 
	ASSUME CS:CODIGO2

;---------------------------------------------------------------------    
; A continuacion declaramos los siguientes procedimientos como publicos para 
; que sean acesibles desde otros modulos que seran montados conjuntamente.
;---------------------------------------------------------------------    

PUBLIC inicio_sonido,fin_sonido, retardo, delay_sonido, hacer_retardo
;PUBLIC elretardo, inicio_no_sonido, crea_aleatorio, prep_contador
PUBLIC inicio_no_sonido

;---------------------------------------------------------------------    
;Procedimiento que inicializa el chip 8253 para generar un sonido de x seq.
;---------------------------------------------------------------------    
inicio_sonido proc far
     push ax
	in ax,61h           ; Puerto B del 8255, palabra de control
	or al,3             ; activa bits 0 y l, latch y altavoz del canal 2 del 8253
	out 61h,al          ; Envía palabra
     mov al,10110110b    ; Palabra de control del canal 2
                         ; Bit 0   =0 Binario, 1 BCD
                         ; Bits 1-3 =Modo (0-5)
                         ; Bits 4-5 =Operacion
                         ; Bits 6-7 =canal
                         ; Binario,modo 3 (onda cuadrada),leer/esc byteh byte1,canal 2
     out 43h,al
	pop ax
	ret
inicio_sonido endp

;---------------------------------------------------------
;Procedimiento que inicializa el chip 8253 sin generar un sonido de x seq.
;----------------------------------------------------------
inicio_no_sonido proc far
     push ax
	in ax,61h           ; Puerto B del 8255, palabra de control
        or al,1             ; activa bit 0
	out 61h,al          ; Envía palabra
     mov al,10110110b    ; Palabra de control del canal 2
                         ; Bit 0   =0 Binario, 1 BCD
                         ; Bits 1-3 =Modo (0-5)
                         ; Bits 4-5 =Operacion
                         ; Bits 6-7 =canal
                         ; Binario,modo 3 (onda cuadrada),leer/esc byteh byte1,canal 2
     out 43h,al
	pop ax
	ret
inicio_no_sonido endp

;---------------------------------------------------------------------    
; Procedimiento que finaliza el sonido en el chip 8253
;---------------------------------------------------------------------    
fin_sonido proc far
	push ax
     in ax,61h           ; Puerto B del 8255, palabra de control
     and al,11111100b    ; desactiva bits 0 y 1, latch y altavoz del canal 2 del 8253
     out 61h,al          ; Envia palabra
	pop ax
	ret
fin_sonido endp

;---------------------------------------------------------------------    
; Procedimiento que realiza el retardo que se indique en AX en unidades de 1193180 avos de segundo
;---------------------------------------------------------------------    
retardo proc far
     push ax
     push bx
     mov bx,0ffffh
retardando:
     mov al,10000000b
     out 43h,al 
     in al,42h 
     mov ah,al 
     in al,42h 
     xchg ah,al 
     cmp ax,bx 
     mov bx,ax 
     jbe retardando 
     pop bx 
     pop ax 
     ret 
retardo endp

;---------------------------------------------------------------------    
; Delay_sonido produce un retardo de 1 segundo con un sonido de x hertzios
;
; Frecuencia de dearemento del temporizador=1.190.000 hertzios
; Máximo valor del contador 65535(cont. binario 16 bits)
; Frecuencia de reseteo del canal 2 en modo 3:
;    valor del contador- 1.190.000/hertzios.
;    Frecuencia r=2*hertzios
;    Tiempo retardo = 1/Frecuencia_r
;    Tiempo total=Tiempo retado*numero de ejecuciones (CX)
; Ejemplo (Sonido de 400 hertzios durante 1 segundo):
;    Valor de AX (contador) 1190000/400=2975
;    Frecuencia r-2*400=800 hertzios
;    Tiempo retardo-1/800=1,25 msg
;    Número de ejecuciones-Tiempo total/Tiempo retardo=800
;	cx -> numero ejecuciones
;	ax -> valor de cuenta
;---------------------------------------------------------------------    
delay_sonido proc far 
	call inicio_sonido
	;mov cx,800          ; Número de ejecuciones del retardo
    ;mov ax,2975         ; Valor del contador
	cli
	out 42h,al
	mov al,ah
	out 42h,al
	in al,61h
	;xor al,1
	;out 61h,al
	;xor al,1
	;out 61h,al
	sti
retard:
        call retardo
	loop retard
	call fin_sonido
	ret
delay_sonido endp

;----------------------------------------------------------------
;RETARDO SIN SONIDO, 
;bx -> num ejecuciones del retardo
;dx -> valor de cuenta
;----------------------------------------------------------------
hacer_retardo proc far

    push cx


     mov cx, bx          ; Número de ejecuciones del retardo
     mov ax, dx          ; Valor del contador
     call inicio_no_sonido
        cli
	out 42h,al
	mov al,ah
	out 42h,al
	in al,61h
	xor al,1
	out 61h,al
	xor al,1
	out 61h,al
      sti
retard2:
        call retardo
        call lee_no_espera
        cmp al, 0			; Se ha pulsado una tecla
		je notecla
		dec cx
        jmp exit
notecla:
        loop retard2
exit:   call fin_sonido

      pop cx
      
   	  ret
hacer_retardo endp






;---------------------------------------------------------------------    
; Fin del SEGMENTO DE CODIGO
;---------------------------------------------------------------------    
CODIGO2 ENDS 

END
	
