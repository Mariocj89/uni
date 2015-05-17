;---------------------------------------------------------------------    
; MOUSE.asm 
; Funciones uso mouse
;---------------------------------------------------------------------    

include macros.asm
include const.asm

;---------------------------------------------------------------------    
; Declaramos el segmento de CODIGO
;---------------------------------------------------------------------    
CODIGO4 SEGMENT 
	ASSUME CS:CODIGO4

;---------------------------------------------------------------------    
; A continuación declaramos los siguientes procedimientos como PUBLIC para 
; que sean accesibles desde otros módulos que serán montados conjuntamente.
;---------------------------------------------------------------------    

PUBLIC Show_Mouse, Hide_Mouse, HayDriver
PUBLIC BotonIzq,BotonDer,GetXY

;---------------------------------------------------------------------    
; Procedimiento que muestra el puntero del raton
;---------------------------------------------------------------------    
Show_Mouse proc far

     PUSH AX
     MOV AX,01
     INT 33h
     POP AX

     ret            
Show_Mouse endp

;---------------------------------------------------------------------    
; Procedimiento que muestra el puntero del raton
;---------------------------------------------------------------------    
Hide_Mouse proc far

     PUSH AX
     MOV AX,02
     INT 33h
     POP AX

     ret            
Hide_Mouse endp

;---------------------------------------------------------------------    
; Procedimiento que comprueba si hay driver de raton instalado
; AL -> 0 hay driver
; AL -> 1 no hay driver
;---------------------------------------------------------------------    
HayDriver proc far

     MOV AX,0000
     INT 33h
     CMP AX,0000

     JNE hay
     MOV AL,01 ;no hay driver
     JMP fin

hay:
     MOV AL,00 
fin:

     ret            
HayDriver endp


PUBLIC BotonIzq,BotonDer,GetXY

;---------------------------------------------------------------------    
; Procedimiento que comprueba si se ha pulsado el boton izq del raton
; AL -> 1 si
; AL -> 0 no
;---------------------------------------------------------------------    
BotonIzq proc far

     MOV AX, 5
     INT 33h
     CMP AX,1b
     JE pulsado
     MOV AL,0 ;se ha pulsado otro boton
     JMP fin2

pulsado:
     MOV AL,01 
fin2:

     ret            
BotonIzq endp

;---------------------------------------------------------------------    
; Procedimiento que comprueba si se ha pulsado el boton der del raton
; AL -> 1 si
; AL -> 0 no
;---------------------------------------------------------------------    
BotonDer proc far

     MOV AX, 5
     INT 33h
     CMP AX,2
     JE pulsado2
     MOV AL,0 ;se ha pulsado otro boton
     JMP fin3

pulsado2:
     MOV AL,01 
fin3:

     ret            
BotonDer endp

;---------------------------------------------------------------------    
; Procedimiento que devuelve las coordenadas del puntero del raton
; CX -> coordenada X
; DX -> coordenada Y
;---------------------------------------------------------------------    
GetXY proc far

     PUSH AX
     MOV AX, 3
     INT 33h
     POP AX

     ret            
GetXY endp


CODIGO4 ENDS   ; FINAL DEL SEGMENTO DE CODIGO

END

