; multi-segment executable file template.

data segment
    ; add your data here!        
    pkey db "press any key...$"
    vector DB 'abcdefghi'
    vector1 DW 11,12,13,14,15,16,17,18,19,20  
    LISTA DB 1,1,0,0,0,0,0,0,0,0,0
    Tam dw 2
    aux db 0
ends

stack segment
    dw   128  dup(0)   
ends

code segment
start:
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax

    mov bx, offset vector
    mov ax,[bx];el primero bite va a al y el segundo a ah
    
;    mov cx,9  
;    xor di,di
;    buc1:  
;    mov al,[bx][di] 
;    inc di
;    loop buc1
                 
;    mov bx, offset vector1
;    mov ax,[bx]                 
                
    ;insertar desordenado            
    mov Bx, offset LISTA
    add bx, Tam
    mov [bx],2;elemnto a insertar
    inc Tam           
      
    ;buscar elemento
;    xor di,di
;    mov bx, offset LISTA
;    mov al, 3
;    otro:
;      cmp al, [bx][di]
;      je fin
;      inc di 
;      cmp di, Tam;comparamos di con el tamanio del vector
;      jg fin 
;      jmp otro
;    fin:
    
    
    ;borrar un elemento
     mov bx, offset LISTA
     mov al, 2;elemento a eliminar
     xor di,di
     otro2:
       CMP al,[bx][di]
       je eliminar
       inc di
       cmp di,Tam 
       jg fin2
       jmp otro2
     eliminar:
       inc di
       mov al, [bx][di]
       mov [bx][di-1],al
       cmp di, Tam
       jnz eliminar 
       dec Tam
     fin2:  
     
    ;algoritmo de la burbuja    
    xor di,di
    mov dx, Tam-1
    buc1: 
    

      buc2:
    
      loop buc2
    loop buc1    
                
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
