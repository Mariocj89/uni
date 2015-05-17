; multi-segment executable file template.
include "macros.inc"
data segment
    ; add your data here!
    pkey db 10,13,"pulse una tecla...$"
    pdato db "Introduzca un numero de dos cifras: $"
    sdato1 db 10,13,"Su menor divisor: $"
    sdato2 db 10,13,"Su mayor divisor: $"
    tprimo db 10,13,"El numero introducido es primo!$"
    
    num db 0
    alfa db ' ','$','$','$','$'
    maxdiv db 0,'$'
    finded db 0
    aux db 0,'$'
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

    inicio:
    borrar
    cursor 0,0
    
    escribir pdato
    pedir 2,alfa
    ascdec alfa, num
    
    mov aux, 1 
    mov finded, 0 
    mov cl, num
    buc1: 
      inc aux  
      cmp aux, cl
      je salida
      xor ax, ax
      mov al, num
      mov bl, aux
      div bl
      cmp ah, 0
      jne buc1
      mov ch, aux
      mov maxdiv, ch
      cmp finded, 0
      jne buc1
      mov finded, 1
      escribir sdato1
      decasc aux, alfa
      escribir alfa
      jmp buc1
      
      
    salida:  
    cmp maxdiv, 0
    je primo
    escribir sdato2
    decasc maxdiv, alfa
    escribir alfa
    fin:
    escribir pkey
    pedir 1, num
    jmp inicio
    
    primo:        
       escribir tprimo
       jmp fin
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
