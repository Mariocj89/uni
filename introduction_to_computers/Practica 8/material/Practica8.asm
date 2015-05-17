;programa fichero Practica 8

  include 'macroficher.txt'

data segment

nomfile db "fichep8.txt",0
handle  dw ?
error1 db 10,13,'Ha habido error en la creacion $',10,13
error2 db 10,13,'Ha habido error en la escritura $',10,13
error4 db 10,13, "No se puede abrir el fichero $",10,13
nubytes dw 0
numord    db '0',13
nombreApe db 'Pepe Perez',13
documen   db '10908876k',13
control   db '97',13

mensaje db 10,13,'ELIGE OPCION:',10,13
        db 10,13,'*****CREAR (c)'
        db 10,13,'*****ESCRIBIR (e)'
        db 10,13,'*****SALIR (s)' 
        db       '$'
ends

stack segment
    dw   128  dup(0)
ends

code segment 
    
start PROC FAR
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax

; codigo     
pide:borrar 

    mov dx,offset mensaje
    mov ah,9
    int 21h 
    
    mov ah,1
    int 21h
    cmp al,'c'
    je crea
    cmp al,'e'
    je escribe
    cmp al,'s'
    je fin
       
crea: call crear
    jmp pide
escribe:call escribir
    jmp pide

fin: nop
    
    call cerrar
    mov ax, 4c00h ; exit to operating system.
    int 21h    
start endp    


crear proc near ;CREAR FICHERO Y CERRAR fichero
    
    mov cx,0
    mov dx, offset nomfile
    mov ah,3ch
    int 21h      
    jc err1
    mov handle,ax  
    mov bx,ax
    mov ah,3eh   ;cierra fichero
    int 21h
    jmp fin1
err1:    lea dx, error1
    mov ah, 9
    int 21h
    
fin1:  nop  
      ret            
crear endp   

escribir proc near   ;ESCRIBIR EN EL FICHERO 
 ;en primer lugar se abre el fichero
 
    mov al,1 ; se abre para escritura   
    mov dx,offset nomfile  
    mov ah,3dh
    int 21h
    jc err4     
    

    
; ahora se escribe el fichero
    
    mov bx,handle  ;handle
    mov cx,26 ; numero de bytes a escribir
    mov dx, offset numord
    mov ah,40h
    int 21h
    jc err2

; se posiciona el puntero al final del fichero
   
    mov bx,handle
    mov al,0 ; al final de fichero 
    mov cx,0 
    mov dx,nubytes ;numero de bytes
    mov ah,42
    int 21h
    
    add nubytes,ax ;numero de bytes escritos
    
    jmp fin2 

err4:lea dx,error4  
     mov ah,9
     int 21h
     jmp fin2           
err2:lea dx, error2
    mov ah, 9
    int 21h        
fin2: nop
   
         ret
escribir endp     

cerrar proc near ; cierra fichero
   
   
    mov handle,ax  
    mov bx,ax
    mov ah,3eh   ;cierra fichero
    int 21h       
          
          
       ret
cerrar endp    



gencon proc near ; este procedimiento genera el numero de control
; a partir de las 4 ultimas cifras del DNI
          
          
          
          
       ret
gencon endp    

ends

end start ; set entry point and stop the assembler.

