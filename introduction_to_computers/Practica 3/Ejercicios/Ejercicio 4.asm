; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "press any key...$" 
    num db 0
    raiz db 0, "$"
    mostrar db "La raiz de el numero almacenado es: $"
    nota db "Nota: Si el numero no tiene raiz exacta, se redondeara por exceso.",13,10,'$'
    salto db 13,10,"$"
    txt db "Introduzca una cifra del numero del que desea hallar la raiz: $"
    cuantas db "Introduzca la cantidad de cifras que tendra el numero(1-2): $" 
    numcif db 0
    aux dw 10
    
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
     

    ;Este algoritmo calcula la raiz de un numero de una o 2 cifras como maximo.
    ;Al preguntar el numero de cifras, si introducimos un numero > 2 producira el mismo efecto que con 2
    
    lea dx, cuantas
    mov ah, 9
    int 21h
    
    mov ah, 1
    int 21h
    
    sub al, 30h
    xor cx, cx
    mov cl, al
    mov numcif, al    
    
    lea dx, salto
    mov ah, 9
    int 21h     


    ;si hemos indicado 2 cifras, leera 2 veces
    CMP cl, 1
    JE salt

    lea dx, txt
    mov ah, 9
    int 21h
    

    mov ah, 1
    int 21h 
    sub al, 30h
    xor ah, ah
    mul aux
    add num, al

    lea dx, salto
    mov ah, 9
    int 21h 

    salt:


    
    lea dx, txt
    mov ah, 9
    int 21h

    mov ah, 1
    int 21h 
    sub al, 30h
    add num, al

    lea dx, salto
    mov ah, 9
    int 21h 
    

     
     
    
    
    ;bh almacenara los impares
    mov bh, 1                 
    ;bl almacenara el numero al que se le iran restando los impares
    mov bl, num
    bucle1:
        sub bl, bh
        add bh, 2
        inc raiz
        CMP bl, 0
    JG bucle1
    add raiz, 30h

    lea dx, mostrar
    mov ah, 9
    int 21h  

    lea dx, raiz
    mov ah, 9
    int 21h
    
    lea dx, salto
    mov ah, 9
    int 21h   
    
    lea dx, nota
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
