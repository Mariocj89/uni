; multi-segment executable file template.
include "macros.inc"
data segment
    ; add your data here!
    pkey db "press any key...$"   
    tmenu db "Menu: ",10,13
     db "1 - Factorial.",10,13
     db "2 - Minimo Comun Multiplo.",10,13
     db "3 - EsPrimo?",10,13
     db "4 - Mostrar 10 numeros mayores de 20 y divisibles entre 3.",10,13
     db "5 - Fibonacci.",10,13  
     db "6 - Salir.",10,13
     db "Elija una opcion(1-5): $"
    pnumero1 db "Introduzca el numero(n<5): $"
    pnumero db "Introduzca el numero(2 digitos): $"
    tres db "Resultado: $" 
    nprimo db "El numero no es primo.$",10,13
    sprimo db "El numero si es primo.$", 10, 13 
    contador db 0
    salto db 10,13,'$' 
    espacio db " $"  
     
     
    num db 0    
    num2 db 0
    alfa db ' ','$','$','$','$'
    aux db 0,'$' 
    vfibonacci db 1,1,0,0,0,0,0,0,0,0,0                                       
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

    call menu
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends
      
menu proc near
    
    inicio:
    
    escribir tmenu 
    pedir 1, alfa
    borrar
    cursor 0,0
    
    cmp alfa,'1'
    jne ent2
    call factorial
    jmp otra
        
    ent2:
    cmp alfa,'2'
    jne ent3
    call mcm
    jmp otra
    
    ent3:
    cmp alfa,'3'
    jne ent4 
    call primo
    jmp otra
    
    ent4:
    cmp alfa,'4'
    jne ent5 
    call mayoresdivisibles
    jmp otra
    
    ent5:
    cmp alfa,'5'
    jne salir
    call fibonacci
    jmp otra
    
    
    salir:
    pedir 1, num
    borrar
    cursor 0,0
    ret
    
    otra:
    pedir 1, num
    borrar
    cursor 0,0    
    jmp inicio
    
menu endp

factorial proc near
    xor ax, ax
    inc ax
    
    escribir pnumero1
    pedir 1, num
    sub num, 30h 
    escribir salto
    
    iniciofac:
    cmp num, 1
    je finfac 
    mul num
    dec num    
    jmp iniciofac
    
    finfac:
    mov aux,al
    escribir tres
    decasc aux, alfa
    escribir alfa
    ret
factorial endp   


primo proc near  
    
    
   escribir pnumero
    pedir 2, alfa
    ascdec alfa, num  

    
    cmp num, 4
    jl primosi     
    xor ax,ax
    xor bx,bx
    ;empezamos a probar a partir de n/2
    mov al, num 
    mov bx, 2
    div bl
    mov aux, al
    
    
    inicioprim:
      xor ax,ax
      mov al, num
      div aux
      cmp ah, 0
      je primono 
      dec aux
      cmp aux, 1
      jg inicioprim   
    primosi:
       escribir salto  
       escribir sprimo

                           
    finprimo:
    ret
    primono: 
      escribir salto
      escribir nprimo
       
    jmp finprimo
primo endp    

mcm proc near
    escribir pnumero
    pedir 2, alfa
    ascdec alfa, num 
    escribir salto

    escribir pnumero
    pedir 2, alfa
    ascdec alfa, num2
    escribir salto
    
    escribir tres
    xor ax,ax    
    mov al, num
    mov aux, al
    dec aux
    mcminicio:
      inc aux 
      xor ax,ax
      mov al, aux
      div num2
      cmp ah, 0
      jne mcminicio
      xor ax, ax
      mov al, aux
      div num
      cmp ah, 0
      jne mcminicio 
       
    decasc aux,alfa
    escribir alfa 
    ret    
mcm endp
mayoresdivisibles proc near
    escribir tres
    mov contador,0
    mov num, 20  
    mov bl,3
    
    
    minicio:
      inc num
      xor ax, ax
      mov al, num
      div bl
      cmp ah,0
      je mmostrar
    
      cmp contador, 10
      jne minicio
    
    ret
    
    mmostrar:
      decasc num, alfa
      escribir alfa 
      escribir espacio
      inc contador
      jmp minicio
mayoresdivisibles endp

fibonacci proc near  
    
    escribir tres
    mov aux, '1'
    escribir aux
    escribir espacio  
    escribir espacio
    escribir aux
    mov contador, 2 
    lea bx, vfibonacci
    
    finicio:
    xor ax,ax
    mov al,[bx]
    mov ah,[bx+1]
    add al, ah
    inc bx
    mov [bx+1], al
    mov num, al
    decasc num, alfa
    escribir alfa
   
    
    inc contador
    cmp contador, 10
    jl finicio
    ret
fibonacci endp
end start ; set entry point and stop the assembler.
