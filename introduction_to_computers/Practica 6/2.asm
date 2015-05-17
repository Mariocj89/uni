; multi-segment executable file template.

include "c:\mismacros.inc"

data segment
    ; add your data here!
    pkey db 10,13,"Saliendo del programa..$" 
    menu2 db "  Menu Principal: ",10,13,"$"
    cad1 db "1.Introducir datos.",10,13,"$"
    cad2 db "2.Mostrar datos.",10,13,"$"
    cad3 db "3.Salir.",10,13,"$" 
    elegir db "Elija una opcion: $"  
    pdatos db "Inserte un valor: $" 
    salto db 10,13,'$'
    num db 0  
    num2 db 0
    vector DB 25 dup (' ') 
    contador db 0  
    salida db "000000$" 
    diez db 10
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

    menu:
    MostrarCadena salto 
    MostrarCadena menu2;mostramos menu2   
    MostrarCadena cad1;mostramos cad1
    MostrarCadena cad2;mostramos cad2
    MostrarCadena cad3;mostramos cad3 
    MostrarCadena elegir;mostramos elegir
    
    PedirCaracter num;Pedimos un numero 

    
    cmp num,'1'
    je op1
    cmp num,'2'
    je op2
    cmp num,'3'
    je salir
     
     
     
    op1:
    call edatos 
    ; wait for any key....    
    mov ah, 1
    int 21h    
    jmp menu ;regresamos al menu
    
    
        
    op2:
    call vdatos
    ; wait for any key....    
    mov ah, 1
    int 21h    
    jmp menu ;regresamos al menu
            
            
            
    salir:  
             
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends 

edatos proc near 
    lea si, vector
    mov contador, 0
edatos0:   
    MostrarCadena salto 
    MostrarCadena pdatos;
    PedirCaracter num
    cmp num, '$'
    jne edatos1 
    jmp edatos3
edatos1: ASCDEC num[-2],num2
         mov dl,num2
         mov [si],dl
         inc si ;si el vector fuera tipo word esto se incrementa 2 veces
         inc contador
         cmp contador, 25
         je edatos3
         jmp edatos0
edatos3: ret
edatos endp 
vdatos proc near
        cmp contador, 0
        je finv
        mov cx, 0
        mov cl, contador 
        lea di,vector
vdatos1:
    DECASC [di], salida[-2]
    mov salida[1], '$' 
    MostrarCadena salida
    inc di
    LOOP vdatos1
finV:
vdatos endp
    
    

end start ;set entry point and stop the assembler.
