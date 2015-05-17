; multi-segment executable file template.
include "macros.inc"
data segment
    ; add your data here!
    pkey db "press any key...$" 
    contador db 0
    nombre db 100 dup('$')
    dni db 10 dup('$')
    control db 0,'$' 
    
    alfa db 50 dup('$')
    num db 0    
    ultdigitos dw 0
    
    t1 db "Introduzca los datos para la persona numero $"
    y1 db "Datos de la persona numero: $" 
    y2 db "Numero de control: $"
    t2 db "Nombre y Apellido: $" 
    t3 db "DNI con letra: $"
    salto db 10,13,'$' 
    menu db "Menu: ",10,13
       db "T - Tomar datos.",10,13
       db "E - Escribir en fichero.",10,13
       db "S - Salir.",10,13
       db "Elija una opcion(T/E/S): $"
    error db "Opcion desconocida, pulse una tecla pra continuar.$"
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

    call pmenu
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends


;*****************************************************************
pmenu proc near
    inicio:
    borrar
    escribir menu
    pedir 1, alfa
    
    cmp alfa, 'T'
    jne op2
    borrar
    cursor 0,0
    call obtenerdatos 
    call MostrarDato
    inc contador    
    jmp inicio
    
    op2:
    cmp alfa, 'E'
    jne op3
    
    
    op3:
    cmp alfa, 'S'
    jne fallo
    escribir salto
    
    ret      
    
    
    fallo:
      escribir error
      pedir 1,num
      jmp inicio  
pmenu endp    

;*****************************************************************

obtenerdatos proc near
    push ax
    push bx
    push cx
    
    escribir t1
    decasc contador, alfa
    escribir alfa 
    escribir salto
    escribir t2
    pedir 20, nombre     
    escribir salto   
    escribir t3
    pedir 9, dni
    escribir salto
    
    
    call HallarDigitoControl
    
    
    
    pop cx
    pop bx
    pop ax    
    ret
obtenerdatos endp

;*****************************************************************                 
                 
HallarDigitoControl proc near 
   lea bx, dni
   add bx,4 
   mov al, [bx]
   mov alfa, al   
   inc bx
   mov al,[bx]
   mov alfa[1], al
   ASCDEC alfa, num
   xor ax,ax
   mov al, num 
   mov cl, 100
   mul cl   
   mov ultdigitos, ax

   inc bx
   mov al,[bx]
   mov alfa, al
   inc bx
   mov al,[bx]
   mov alfa[1], al
   ASCDEC alfa, num
   xor ax,ax
   mov al, num
   add ultdigitos, ax    
   
   
   call GenerarDigitoControl
    
   ret 
HallarDigitoControl endp

;*****************************************************************

GenerarDigitoControl proc near
    
    
    
     ret
GenerarDigitoControl endp

;*****************************************************************
MostrarDato proc near
    borrar
    cursor 0,0
    escribir y1
    decasc contador, alfa
    escribir alfa 
    escribir salto
    escribir t2
    escribir nombre     
    escribir salto   
    escribir t3
    escribir dni
    escribir salto
    escribir y2  
    decasc control, alfa 
    escribir alfa
    escribir salto
    
    escribir pkey
    pedir 1,num
    ret
MostrarDato endp    
                     
end start ; set entry point and stop the assembler.
