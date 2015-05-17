


;---------------------------------------------------------------------    
; A continuacion declaramos los siguientes procedimientos que han sido 
; declarados como public en otros modulos, y que utilizamos en este
;---------------------------------------------------------------------    

extrn Linea_Horizontal:far
extrn Linea_Vertical:far
extrn Lee_eco:far


;---------------------------------------------------------------------    
; A continuación declaramos los siguientes procedimientos como PUBLIC para 
; que sean accesibles desde otros módulos que serán montados conjuntamente.
;---------------------------------------------------------------------    

PUBLIC  Cuadrado

;---------------------------------------------------------------------    
; Declaramos el segmento de CODIGO
;---------------------------------------------------------------------    
CODIGO6 SEGMENT 
	ASSUME CS:CODIGO6

;---------------------------------------------------------------------
; PROCEDIMIENTO QUE CREA UN CUADRADO EN LAS POSICION PASADAS POR
; PARAMETROS:
;           CX ----> inicioX 
;           DX ----> inicioY 
;           AX ----> alto
;           BX ----> ancho
;---------------------------------------------------------------------
Cuadrado proc far
	push cx        ; Guardamos los registros
	push dx        ;
	push bx        ;
	push ax        ;
	
	;Pintamos las lineas horizontales
	mov al, 15
	Call Linea_Horizontal
	pop ax	;cogemos el alto
	push ax
	add dx, ax ;incrementamos la posicion x
	mov al, 15
	Call Linea_Horizontal	
	 
	;Pintamos las lineas verticales
	pop ax         ;     
	pop bx         ; Restauramos los registros
	pop dx         ;
	pop cx         ;
	push cx        ; Guardamos los registros
	push dx        ;
	push ax        ;
	push bx        ;
	
	mov bx, ax
	mov al, 15
	Call Linea_Vertical
	pop ax   ;sacamos el largo
	push ax
	add cx,ax
	inc bx
	mov al, 15
	Call Linea_Vertical
	
	pop bx         ; Restauramos los registros
	pop ax         ;     
	pop dx         ;
	pop cx         ;
	ret;
Cuadrado endp 

CODIGO6 ENDS   ; FINAL DEL SEGMENTO DE CODIGO

END 