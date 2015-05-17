; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "press any key...$"
    salto db 13,10,'$'
    num1 db 3 
    factorial dw 0,'$'
    txt db "El factorial del numero almacenado es: $"
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
    inc ax
    xor cx, cx
    ;en ax iremos guardando el resultado
    
    
    bucfac:
        cmp num1, 1
        JNG exit
        mul num1
        dec num1
         
         
        JMP Bucfac 
         
    exit:
    ;Falla aqui, no se como pasar de hex a ascii 
    add ax, 30h
    mov factorial, ax
    

    lea dx, txt
    mov ah, 9
    int 21h      

    lea dx, factorial
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
