;Muestra la cadena introducida por parametros
MostrarCadena MACRO sdat

    push ax      
    push dx      

    lea dx,sdat
    mov ah,9
    int 21h

    pop dx      
    pop AX  
   
endm         


PedirCaracter MACRO caracter

    push ax      
    mov ah,1
    int 21h
    mov caracter, al 
    pop ax  
       
endm     

decasc macro valordec, valasci 
        
    mov bx, offset valasci
    add bx,5
    
   
    mov ax,valordec
    ;vemos si es de una sola cifra
    xor dx,dx
    cmp ax,9
    
    jbe unacifra
    ;pasamos a ascii
     
    div diez
     
sigue:
    cmp al,9
    jle doscif
    
    ;guardo en valasc el primer digito
    add ah,30h
    mov [bx],ah
    dec  bx
     
    xor ah,ah
   
    div diez
    jmp sigue

 unacifra:
    add ax,30h 
    mov [bx],al 
 
 doscif: 
    add ah,30h
    add al,30h
    mov [bx],ah
    dec bx
    mov [bx],al 
 
endm    

ASCDEC  MACRO ASC,BINV
                        LOCAL ASC1,ASC2,ASC11
                        push  ax
                        PUSH  BX
                        PUSH  CX
                        PUSH  DX
                        PUSH  SI
                        PUSH  DI
                        
                        LEA   SI,ASC[2]
                        MOV   CX,3
                        MOV   BX,1
                        MOV   BINV,0
                  ASC1: MOV   AL,[SI]
                        CMP   AL,'$'
                        JE    asc11
                        cmp   al,'0'
                        jl    asc2
                        cmp   al,'9'
                        jg    asc2
                        SUB   AL,30H
                        mov   AH,0
                        MUL   BL
                        ADD   binv,aL
                        mov   ax,10
                        mul   bx
                        mov   bx,ax
                  ASC11:dec   si
                        loop  asc1
                        
                  asc2: POP     DI
                        POP   SI
                        POP   DX
                        POP   CX
                        POP   BX
                        POP   AX
ENDM