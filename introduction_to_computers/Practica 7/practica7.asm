; multi-segment executable file template.
include "macros.inc"

data segment
    ; add your data here!
    pkey db "press any key...$"
    matriz db 100 dup(1), '$'  
    i db 0
    j db 0
    ;matriz db 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,'$'
    cadena db 30 dup('$') ;variable utilizada para leer 
    num db 3 dup('$') 
    
    introduce db "Introduzca el tamaño de la martriz(2<n<10): $" 
    fueraderango db "Numero fuera del rango. "
    salto db 10,13,'$'
    aux db 0
    tam db 0
ends

stack segment
    dw   128  dup(0) 
ends

code segment
    start proc far
; set segment registers:
    mov ax, data
    mov ds, ax
    mov es, ax  
    
        
    inicio:
    
    escribir introduce
    pedir 1,cadena 
    escribir salto    
    ascdec cadena, num
    mov al, num
    mov tam, al
    cmp num, 2
    jle fuera 
    call tartaglia
    jmp mostrar
    continuar:

    
    

    ; add your code here
            
    lea dx, pkey
    mov ah, 9
    int 21h        ; output string at ds:dx
    
    ; wait for any key....    
    mov ah, 1
    int 21h
    
    mov ax, 4c00h ; exit to operating system.
    int 21h 
    
    fuera:
      escribir fueraderango
      jmp inicio   
      
    mostrar:
      ;push i
      ;push j
      
      mov aux,1
      lea di, matriz
      mov i,0
      mov j,0 
      
      xor cx,cx
      mov cl,tam
      buc1:
      
        push cx
        xor cx,cx 
        mov cl, tam
        buc2:          
            mov al, [di]
            mov num, al
            decasc num, cadena
            escribir cadena
            inc di
            LOOP buc2
        ;inc aux        
        pop cx
      escribir salto    
      LOOP buc1
      
      
    jmp continuar  
      ;pop j
      ;pop i
       
endp    

Tartaglia proc near
    mov i,2   
    mov aux, 5
    lea bx, matriz
    dec bx

  buct1:
    mov j,2
  buct2:
      xor ax,ax
      mov al,i 
      mul aux
      add al,j
      mov si,bx 
      add si,ax 
      xor dx,dx
      


      xor cx,cx
      mov cl,aux  
      sub si,cx  
      
      mov al,[si]
      
      dec si
      
      add al, [si]
      
      xor cx,cx
      mov cl,aux
      add si,cx    
      inc si 
      
      mov [si],al

  finbuct2: 
    inc j
    mov dl,j
    mov cl,i    
    cmp dl, cl
    jle buct2       
    
  finbuct1:
    inc i 
    mov dl, i 
    mov cl,aux 
    dec cl
    cmp dl,cl

  jle buct1
  
  ;call mostrar

  ret
    
Tartaglia endp 

end start ; set entry point and stop the assembler.
