; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "press any key...$" 
    cadena db 3,0,0,0,0,'$'
    salto db 13,10,'$'
    num db 0,'$'
    m db 1
    diez db 10
    
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
    
    
    lea dx, cadena
    call PedirCadena 
    call SaltoLinea 

    

    call Asc2Dec 
    
    lea dx, num
    ;call MostrarCadena

    mov ax, 4c00h ; exit to operating system.
    int 21h    
start endp 

PedirCadena Proc near ;ent: dx contiene la direcc de la variable en la que guardar 
    
     push ax
     

     mov ah, 0Ah
     int 21h   
            
        
     pop ax
     ret   
PedirCadena endp ;ent: dx contiene la direcc de la variable a mostrar 
               
                 
MostrarCadena Proc near  
    
     push ax            
     
     
     mov ah, 09h
     int 21h
     
     
     pop ax   
     ret 
     
MostrarCadena endp

SaltoLinea proc near ;declarar " salto db 13,10,'$' "
    
    push ax
    push dx
    
    lea dx, salto  
    mov ah, 09h
    int 21h
    
    pop dx
    pop ax
    ret
    
SaltoLinea endp

Asc2Dec proc near;ent: cadena 
                 ;sal: num 
  
      push ax
      push cx
      push bx
       
      lea bx, cadena
      xor cx, cx
      mov cl,[bx+1]
      add bx, cx
      bucle:
        mov al,[bx+1]
        sub al, 30h
        dec bx
        
        mov dl, m
        mul dl
        
        add num, al
        
        mov al, m
        mul diez
        mov m,al
      
      loop bucle  
        
      pop bx
      pop cx
      pop ax
      ret
      
Asc2Dec endp    



end start ; set entry point and stop the assembler.
