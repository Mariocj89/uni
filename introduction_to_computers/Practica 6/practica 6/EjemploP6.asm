include 'macrod.inc'
	
	
DSEG SEGMENT 'DATA'

mensaje     DB ' ',10,13
	        DB '  1.Int.datos Vector',10,13
            DB '  2.Ver datos',10,13
            DB '  3.Insertar un elemento',10,13 
            DB '  4.Eliminar un elemento',10,13
            DB '  5.Ordenar una lista de elementos',10,13
            DB '  6.Insertar un elemento en una lista ordenada',10,13
            DB '  7.Buscar un elemento(Busq. binaria si ordenado)',10,13
            DB '  8.Borrar un elemento de una lista ordenada',10,13
            DB '  9.Acabar',10,10,13
            DB '  Opcion....$'
bin         DB  0
alfanu      DB '   ','$'
vector      DB 25 dup (' ')
salida      DB 4 dup (' '),'$'
contador    DB 0
medatos     DB 'Introduce datos:$'
pausa   DB 10,13,'Pulsa una tecla para volver al menu$'
mensaje1    DB 'Introduce el elemento a insertar: $'
mensaje2    DB 'Introduce el elemento a borrar: $'
mensaje3    DB 'Introduce el elemento a buscar: $' 
mencont  db 'Se ha encontrado el elemento en la posicion:$'   
melim  db 'Se ha eliminado el elemento.$'
mnencont db 'No se ha encontrado el elemento.$'  
menoord db 'Atencion, ordene el vector primero.$'
ordenado db 0 
auxiliar dw 0 
dos db 2


DSEG    ENDS

SSEG    SEGMENT STACK   'STACK'
        DW      120h    DUP(?)
SSEG    ENDS

CSEG    SEGMENT 'CODE'
                                                                    
                                                                    
                                                                    
                                                                    
START PROC FAR
    PUSH    DS
    MOV     AX, 0
    PUSH    AX
    MOV     AX, DSEG
    MOV     DS, AX
    MOV     ES, AX
    
entrada0:
        borrar
        cursor 12,2
        escribir mensaje
        cursor  23,13
        CALL	tecla

        CMP     AL,'1'
        JNE     ent1
        CALL    edatos
        JMP     entrada0

ent1:   CMP     AL,'2'
        JNE     ent2
        CALL    vdatos
        JMP     entrada0
                          
ent2:   CMP     AL,'3'
        JNE     ent3
        CALL    inselemento
        JMP     entrada0 
        
ent3:   CMP     AL,'4'
        JNE     ent4
        CALL    elielemento
        JMP     entrada0
        
ent4:   CMP     AL,'5'
        JNE     ent5
        CALL    ordlista
        JMP     entrada0                                         

ent5:   CMP     AL,'6'
        JNE     ent6
        CALL    inslista
        JMP     entrada0

ent6:   CMP     AL,'7'
        JNE     ent7
        CALL    buscar
        JMP     entrada0

ent7:   CMP     AL,'8'
        JNE     ent8
        CALL    borar
        JMP     entrada0
                          
ent8:   CMP     AL,'9'
        JNE     entrada0
        JMP     final
        
        
FINAL: 	RET

START   ENDP




TECLA   PROC NEAR

    MOV AH,01H
    INT 21H

    RET
TECLA ENDP




EDATOS  PROC    NEAR
        LEA     SI,vector;para ver si está sin valores el vector
        MOV     contador,0
        
edatos0:borrar
	    cursor 10,10
	    escribir medatos
	    cursor 10,30
	    pedir  2,alfanu
	    
	    CMP alfanu,'$'
	    JNE edatos1
	    JMP edatos3

edatos1:ascdec  alfanu,bin
        MOV     DL,bin
        MOV     [SI],DL;almaceno en vector
        INC     SI     ;voy a siguiente elemento
        INC     contador
        CMP     contador,25
        JE      edatos3
        JMP	edatos0
edatos3: RET

EDATOS ENDP




VDATOS PROC NEAR
        borrar
        CMP contador,0
        JE  finv
        MOV CX,0
	    MOV CL,contador;tantas vueltas como valores hay
	    cursor 20,1
	    LEA SI,vector

vdatos1: 	
	    decasc [SI],salida
	    MOV salida[3],'$' 
	    escribir salida
	    INC SI		;siguiente valor del vector
	    LOOP vdatos1
	    escribir pausa
	    CALL tecla;pausa para ver los datos
FINV:	RET

VDATOS	ENDP	 
			


;*****************************
INSELEMENTO PROC NEAR
    
    borrar
    cursor 2, 2
    mov bx, offset vector 
    lea dx, mensaje1
    mov ah, 9
    int 21h    
    pedir 2,alfanu
    ascdec alfanu, bin 
    cmp contador, 25
    jge fin
        add bl, contador
        mov dl, bin
        mov [bx], dl   
        inc contador
    fin:
    mov ordenado,0   
                           
RET
INSELEMENTO ENDP
;*****************************


;*****************************
ELIELEMENTO PROC NEAR
  
  lea dx, mensaje2
  mov ah, 9
  int 21h    
  pedir 2,alfanu
  ascdec alfanu, bin
  mov al, bin 
  call busc
  cmp al, [bx+di]
  cursor 0,0
  je encon
  xor dx,dx
  mov dl, contador  
  escribir mnencont 
  escribir pausa
  CALL tecla;pausa para ver los datos 
  finborr:    
RET

  encon:
  mov al, [bx+di+1]    
  mov [bx+di],al
  inc di
  cmp dx,di  
  jne encon
  dec contador
  escribir melim
  escribir pausa
  CALL tecla;pausa para ver los datos
  jmp finborr 
    
ELIELEMENTO ENDP
;*****************************


;*****************************
ORDLISTA PROC NEAR
    
    burbuja contador, vector
    mov ordenado,1  
    
RET    
ORDLISTA ENDP
;*****************************


;*****************************
INSLISTA PROC NEAR
    
    cmp ordenado, 0
    je error
    borrar
    cursor 2, 2  
    xor cx, cx 
    mov cl, contador
    mov di, cx 
    mov bx, offset vector 
    lea dx, mensaje1
    mov ah, 9
    int 21h    
    pedir 2,alfanu
    ascdec alfanu, bin 
    xor dx,dx
    mov dl, bin
    cmp contador, 25
    jge fin1 
    
    
  buci:
  dec di 
  cmp di, -1 
  je finbuci
  mov al, [bx+di]   
  mov [bx+di+1] ,al
  cmp dl,[bx+di]  
  jng buci
  finbuci:
    
    mov [bx+di+1], dl   
    inc contador    
    
    
        
    fin1:       
        
RET 

     error: 
    cursor 0,0
    escribir menoord 
    escribir pausa
    CALL tecla;pausa para ver los datos
    jmp fin1
   
INSLISTA ENDP
;*****************************


;*****************************
BUSCAR PROC NEAR   
  lea dx, mensaje3
  mov ah, 9
  int 21h    
  pedir 2,alfanu
  ascdec alfanu, bin
  mov al, bin
  cmp ordenado,1
  je ord 
  call busc
  fb:  
  mov bx, offset vector
  cmp al, [bx+di]
  cursor 0,0
  je enc
  escribir mnencont  
  escribir pausa     
  CALL tecla;pausa para ver los datos 
  finb:    
RET

  enc:
  xor dx,dx 
  mov dx, di
  mov bin, dl
  decasc bin, alfanu   
  escribir mencont
  escribir alfanu
  escribir pausa
  CALL tecla;pausa para ver los datos
  jmp finb  
  
  
  ;si el vector esta ordenado:
  ord:
  call buscbin
  jmp fb
    
BUSCAR ENDP
;*****************************


;*****************************
BUSC PROC NEAR;tenemos en al el numero que buscamos
  MOV BX, OFFSET VECTOR
  xor di,di 
  xor dx,dx
  mov dl, contador
  otro: cmp al, [bx+di]
      je finbusc
      inc di
      cmp dx, di
      jne otro 
      finbusc:
    
RET
BUSC ENDP
;*****************************


;*****************************
BUSCBIN PROC NEAR;tenemos en al el numero que buscamos
   xor di,di 
   xor dx,dx
   xor bx,bx
   mov di, offset vector
   mov bl, contador
   add bx, di
   dec bl
   again: 

       call aux  
       mov cx, di       
       mov di, auxiliar
       cmp bx, di
       je finbuscbin        
       cmp al, [di] 
       je finbuscbin
       mov di, cx       
       jg mayor
       jmp menor  

       finbuscbin:      
       sub di, offset vector
         
RET 
    menor:
       cmp di, bx
       je finbuscbin    
       mov bx, auxiliar
       jmp again
    
    mayor:
       cmp di, bx  
       je finbuscbin
       inc auxiliar      
       mov di, auxiliar             
       jmp again           
    
BUSCBIN ENDP
;*****************************

;*****************************
BORAR PROC NEAR
    cmp ordenado, 0
    je err 
    
  lea dx, mensaje2
  mov ah, 9
  int 21h    
  pedir 2,alfanu
  ascdec alfanu, bin
  mov al, bin 
  call buscbin 
  mov bx, offset vector

  cursor 0,0
  xor dx,dx
  mov dl, contador 
  cmp al, [bx+di]
;  mov di, dx
  je encont  
  escribir mnencont 
  escribir pausa
  CALL tecla;pausa para ver los datos 
  finborar:    
RET
  
  encont:
  mov al, [bx+di+1]    
  mov [bx+di],al
  inc di
  cmp dx,di  
  jne encont
  dec contador
  escribir melim
  escribir pausa
  CALL tecla;pausa para ver los datos
  jmp finborar     

    err: 
    cursor 0,0
    escribir menoord 
    escribir pausa
    CALL tecla;pausa para ver los datos
    jmp finborar
    
     


BORAR ENDP   
;***************************** 

;*****************************
aux PROC NEAR;devuelve en auxiliar  (bx+di)/2
   push ax
   push cx
   xor cx,cx 
   mov ax, bx
   add ax, di
   sub ax, offset vector
   sub ax, offset vector   
   div dos
   xor ah,ah
   mov auxiliar, ax
   add auxiliar, offset vector 
   
   pop cx 
   pop ax        
RET
aux ENDP
;*****************************  


CSEG    ENDS 

        END    START  