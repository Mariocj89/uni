; multi-segment executable file template.
include "macros.inc"
data segment
    ; add your data here!
    pkey db 10,13,"pulse una tecla...$"
    pnum1 db "Primer sumando(signo+ 2 digitos): $"
    pnum2 db 10,13,"Segundo sumando(signo + 2 digitos): $"
    snum db 10,13,"El resultado es: $"
    
    num db 0
    num1 db 0
    s1 db 0
    num2 db 0 
    s2 db 0
    alfa db 5 dup('$')
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
      escribir pnum1
      pedir 3, alfa
      ascdec alfa+1, num1
      mov al, alfa
      mov s1, al
      escribir pnum2
      pedir 3, alfa
      ascdec alfa+1, num2
      mov al, alfa 
      mov s2, al
      
      mov num, al
      escribir snum
      
      mov al, num1
      mov bl, num2
      
      mov cl, s2
      cmp s1,cl
      je suma 
      resta:
        mov ch, num2
        cmp num1,ch
        jg mayor1 
          ;intercambiamos
          mov cl, bl
          mov bl, al
          mov al, cl        
        sub al, bl
        mov cl, s2
        mov aux, cl
        escribir aux
        jmp fin
        
      suma:
        add al, bl
        mov cl, s1
        mov aux, cl
        escribir aux  
    
    fin: 
    mov num, al
    decasc num, alfa
    escribir alfa
    pedir 1, num1        
    borrar
    cursor 0,0
    jmp inicio 
    
    
    mayor1:
        sub al, bl
        mov cl, s1
        mov aux, cl
        escribir aux
       jmp fin
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends

end start ; set entry point and stop the assembler.
