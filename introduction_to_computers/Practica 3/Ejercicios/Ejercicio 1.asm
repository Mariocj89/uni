; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "press any key...$"
    salto db 13,10,'$'
    veces db 10,'$'
    num db 1,2,3,4,8,6,7,8,3,6  
    mayor db 0, '$'
    txt db "El mayor de todos los numeros guardados es: $"
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
    
    xor ax, ax
    lea si, num 
    xor cx, cx
    mov cl, veces
    bucle1: 
        cmp al, [si]
        JG paso1
        mov al, [si]
        paso1:     
        inc si
    LOOP bucle1    
    
    add al, 30h
    mov mayor, al 
     
    lea dx, txt
    mov ah, 9
    int 21h   
    
    lea dx, mayor
    mov ah, 9
    int 21h  
    
    lea dx, salto
    mov ah, 9
    int 21h        

            
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
