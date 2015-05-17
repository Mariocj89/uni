; multi-segment executable file template.

include "C:/mimacro.inc"

data segment
    ; add your data here!
    pkey db "press any key...$" 
    n1 dw 3000
    n2 dw -3000
    v1 dw 0
    v2 dw 0
    s1 db 0
    s2 db 0
    nr dw 0,0,"$"
    sr db 0
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

    signo n1,s1
    signo n2,s2
    signores s1,s2, sr
  
    mov ax, n1
    mul n2
    
    mov nr, dx
    mov nr[2], ax
    
    
            
    lea dx, nr
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h    
ends
          
end start ; set entry point and stop the assembler.

