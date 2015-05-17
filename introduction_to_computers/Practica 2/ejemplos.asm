; multi-segment executable file template.

data segment
    ; add your data here!
    pkey db "press any key...$"
    vector DB 5     
    dato DB 2
    numero DB 10
    letras db "a$"
    letra db "abcdefghi$"

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
 ;1
    ;mov ax, 5
	;add ax, 9 
	
 ;2	
	;neg ax
	;add ax, ax
	
 ;3	    
	;mov al, [1]    
	;xchg [0],al  
	;mov [1], al 
	
 ;4
	;mov [vector], al
	;sub bl, vector 
	  
 ;5	  
	;mov al, 25
	;mul dato
	  
 ;6	  
    ;mov ax, 101
	;div numero
	  
 ;7	  
	;xor cx,cx
	  
 ;8	  
	mov bx, 100h
	mov cx, 9
	Bucle1:    
	    mov al, letras
		mov [bx], al
		inc bx
		inc letras
	LOOP Bucle1
	
	
            
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
