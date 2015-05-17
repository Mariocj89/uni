; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "press any key...$" 
    fibona db 0,1,8 DUP('$')  
    num db 0, '$'
    txt db "Cuantos numeros de la serie de fibonacci que desea generar?( >2 ): $"
    salto db 13,10,'$'
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

    

    lea si, fibona
    

            
    lea dx, txt
    mov ah, 9
    int 21h       
                     
    
    mov ah, 1
    int 21h
    mov num, al
    sub num,30h 
    
    
    lea dx, salto
    mov ah, 9
    int 21h
    
        
    ;si nos piden que hallemos menos de 3 numeros, ya biene echo de base. 
    cmp num, 2
    JNG FIN 
    
    dec num
    dec num 
    xor cx,cx
    mov cl, num
    xor si,si
     
    bucle1:
        mov al, fibona[si]
        add al, fibona[si+1]
        mov fibona[si+2], al
        inc si
    
    LOOP bucle1
    
    FIN:
            
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
