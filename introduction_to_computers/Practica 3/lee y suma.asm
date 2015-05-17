; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db 13,10,178,178,178,178,178,"press any key",178,178,178,178,178,'$'
    mostrar db 13,10,"La suma de ambos es:$"
    pedir db 13,10,"Introduzca un numero:$"
    var1 db "h$"
    var2 db "r$"
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

    lea dx, pedir         
    mov ah, 9   
    int 21h

    mov ah, 1
    int 21h
    mov var1, al 
    
    lea dx, pedir         
    mov ah, 9   
    int 21h 
    
    mov ah, 1
    int 21h
    mov var2, al     

    lea dx, mostrar  ;or mov dx, offset mostrar       
    mov ah, 9   
    int 21h
    
    mov bh, var1 
    mov bl, var2
    sub bl, 30h
    add bl,bh 
    mov var1, bl
    
             
    lea dx, var1         
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
