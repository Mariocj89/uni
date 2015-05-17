; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "press any key...$" 
      
    ;1.
    dato dw 0afedh 
     
    ;2.
    dat1 db 5
    dat2 db 3
    dat3 db 7
    
    ;3
    num db 5
    valores db 3,4,5,6,7,"$"
    
    ;4
    num1 db 2
    veces db 3
    
    ;5
    tabla db 100 DUP ('$')
    
    ;6
    numero db 10
    divisores db 0
   
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

  ;1.
    not dato
    and dato, 0000h
    or dato, 0ffffh
    AND AX,00FFh  
    
  ;2
    xor ax, ax
    mov al, dat1
    add al, dat2
    add al, dat3
    mov bx, 3
    div bx
    
  ;3        
    xor ax, ax 
    xor cx, cx
    mov cl, num
    xor bx, bx   

    
    Bucle:
        add al, valores[bx]
        inc bx
    LOOP Bucle 
    div num  
    
  ;4  
    mov ax, 1
    xor cx, cx
    mov cl, veces
    Bucle1:
        mul num1
    Loop Bucle1 
               
   ;5                 
    xor ax, ax
    xor bx, bx
    xor cx, cx
            
    Buc1:
        inc bl
        cmp bl, 10
        je fin
        mov ch, 1
        Buc2:
            cmp ch, 10
            je Buc1
            mov al, bl
            mul ch
            mov tabla[di], al
            inc di
            inc ch
            jmp Buc2
        jmp Buc1
    fin:
    
   ;6 
    xor ax, ax
    xor bx, bx
    mov bl, numero
    mov di, 0
    Buc3:
        cmp bl, 0
        je fin1
        mov al, numero
        xor ah, ah
        div bl
        cmp ah, 0
        jne eti1
        mov divisores[di], bl
        inc di        
        eti1:
            dec bl
            jmp Buc3     
    fin1:
            
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
