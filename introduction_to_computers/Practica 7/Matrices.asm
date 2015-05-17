include "macros.inc"

; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "Press any key...$"    
    matriz db 100 dup(1)     
    inicio db "Elige el tamanio de la matriz: $"
    mtar db "Creando triangulo...$"            
    mrellenar db "Inicializando matriz...$"
    mtraspuesta db "Matriz traspuesta$"
    mpause db "Pulse una tecla para continuar...$"
    menu db "Menu:",10,13,
         db "1. Rellenar matriz",10,13, 
         db "2. Obtener traspuesta",10,13,
         db "3. Ordenar elementos",10,13,
         db "4. Ver simetria",10,13,
         db "5. Buscar minimo",10,13,   
         db "6. Mostrar matriz",10,13, 
         db "7. Mostrar triangulo de tartaglia",10,13, 
         db "8. Salir" ,10,10,
         db "Opcion: $"     
   
  
    eleccion db 0   
    i db 0
    j db 0
    n db 5
    num db 0
    linea db 0 ; 
    salida db 4 dup(' '),'$' 
    intro db 10,13,'$'      
  
   
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

ent0:  ;***********  MENU    ************
     borrar    
     cursor 5,2
     escribir menu  
     pedir 1,eleccion
     
     
     cmp eleccion,'1'
     jne ent2
     call rellenar
     jmp ent0  
     
ent2:
     cmp eleccion,'2'
     jne ent3
     call traspuesta
     jmp ent0    
ent3:
     cmp eleccion,'3'
     jne ent4
     call ordenar
     jmp ent0  
ent4:
     cmp eleccion,'4'
     jne ent5
     call simetria
     jmp ent0    
ent5:
     cmp eleccion,'5'
     jne ent6
     call buscar
     jmp ent0 
ent6:
     cmp eleccion,'6'
     jne ent7
     call mostrar
     jmp ent0 
ent7:
     cmp eleccion,'7'
     jne ent8
     call triangulo
     jmp ent0    
          
ent8:
     cmp eleccion,'8'
     jne ent0
     jmp salir
fin:  ret   
;********************************************************
                                                     
                                                     
rellenar proc near ;***********  RELLENAR    ************
    borrar
    cursor 9,9
    escribir mrellenar     
    lea bx, matriz  
    mov i,1 
      xor ax,ax
      mov al,i 
      mul n    
      
      xor cx,cx
      xor ax,ax
      mov al,i  
      mul n
      mul n    ;almacena en al la longitud del vector
      mov cl,al 
 
        
       
rellenar1:
    mov [bx],cl  
    inc bx
    loop rellenar1 
                             
    ret
rellenar endp
;********************************************************

traspuesta proc near;*********  TRASPUESTA    **********
    borrar
    cursor 0,0

    lea bx, matriz 
    mov i,0
tras1:
    mov j,0
tras2:
    lea bx, matriz 
      
      xor ax,ax
      mov al,j 
      mul n      ;al almacena la posicion del elemento
      add al,i 
      
      add bl,al  ;bx apunta al elemento
    decasc [bx], salida 
    escribir salida
    inc j
    mov dl,j
    mov cl,n
    cmp dl,cl
  jl tras2 
    inc i
    cursor i,0      
    mov dl,i
    cmp dl,cl
  jl tras1:
    tecla     
        
    ret
traspuesta endp
;********************************************************
                    
ordenar proc near;*********  ORDENAR    **********
    
    ret
ordenar endp
;********************************************************

simetria proc near ;*********  SIMETRIA    **********
    
    ret
simetria endp
;********************************************************

buscar proc near ;*********  BUSCAR    **********
    
    ret
buscar endp
;********************************************************

mostrar proc near;*********  MOSTRAR    **********   
  borrar
  cursor 5,0  
  lea bx, matriz  
  
  mov i,1
mostrar1:
  mov j,1
mostrar2:

  decasc [bx], salida
  escribir salida     ;Escribe el dato apuntado
      
  inc bx 
  inc j   
  
  mov dl,j
  mov cl,n
  cmp dl,cl
  jle mostrar2 ;salta al llegar al final de la linea      
            
  lea dx, intro
  mov ah,9       
  int 21h      ; salto de linea
  
  inc i 
  mov dl, i 
  mov cl,n 
  cmp dl,cl
  jle mostrar1 ;salta si no es la ultima linea 
    
      tecla           
  ret
mostrar endp
;********************************************************
                    
triangulo proc near;*********  TRIANGULO    **********
    borrar
    cursor 9,9
    escribir mtar
    mov i,2
    lea bx, matriz
    dec bx

buci:
    mov j,2
  bucj:
      xor ax,ax
      mov al,i 
      mul n
      add al,j
      mov si,bx 
      add si,ax ;si almacena la posicion del elemento
      xor dx,dx
      


      xor cx,cx
      mov cl,n    ; si = 2 elemento
      sub si,cx  
      
      mov al,[si] ; al = contador
      
      dec si      ; si = 1 elemento
      
      add al, [si]
      
      xor cx,cx
      mov cl,n    ; si = 2 elemento
      add si,cx    
      inc si      ; si= posicion del elemento principal
      
      mov [si],al

  finbucj: 
    inc j
    mov dl,j
    mov cl,i    
    cmp dl, cl
    jle bucj       
    
finbuci:
  inc i 
  mov dl, i 
  mov cl,n 
  dec cl
  cmp dl,cl

  jle buci
  
  call mostrarT

  ret
    
triangulo endp     
;********************************************************

mostrarT proc near;*********  MOSTRAR T    **********
  borrar 
  cursor 0,0
  lea bx, matriz
  mov i,1
mt1:
  mov j,1 
  mt2:
    decasc [bx], salida
    escribir salida
    inc bx 
    inc j
    mov dl,j
    mov cl,i
    cmp dl,cl
  jle mt2       
  
  cursor i,0     
  
  xor dx,dx
  mov dl,n
  sub dl,j
  inc dl
  
  add bx,dx
  
  inc i 
  mov dl, i 
  mov cl,n 
  cmp dl,cl
jle mt1
  cursor 3,30
  escribir mpause  
  tecla        
ret                   
mostrarT endp  
;********************************************************

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

end start ; set entry point and stop the assembler.
