
signo MACRO numero, signo ; extrae el signo y magnitud de un número en c-2
    local positivo, final
    MOV AX, [numero]
    SHL AX, 1 ; desplaza a la izq. un bit CF=S
    JNC positivo ; salta si no acarreo, nº positivo
    MOV [signo],80h
    RCR AX,1 ; desplaza a la derecha introduciendo CF
    NEG AX ; realiza el complemento a 2
    JMP final
    positivo: SHR AX,1
    MOV [signo], 00h
    final: MOV [numero], AX
ENDM
                   
                   
signores MACRO s1,s2,sres ;Obtener el signo del resultado
    local positivo, final
    MOV AL, [s1]
    MOV AH, [s2]
    XOR AL,AH ; SI ES CERO EL SIGNO + Y SI ES 1 NEGATIVO
    CMP AL,0 ;POSITIVO
    JZ positivo
    MOV [sres], 2Dh ; negativo
    JMP final
    positivo: MOV [sres],2Bh ; codigo ascii del +
    final: MOV [sres], Al
ENDM                   


leer_datos MACRO var1 ;en var1 guardara lo que se haya obtenido por teclado   
    lea dx, var1 
    mov ah, 0Ah
    int 21h  
    mov cl, var1[1]  
    mov var1[cl+2], "$"
ENDM    

                                                                                                                                    