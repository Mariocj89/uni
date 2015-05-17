
pedir MACRO lon,dir
        local fin_pedir,pedir1
	PUSH	AX
	PUSH    BX
	PUSH	CX
	PUSH	DX
	PUSH	SI
	PUSH	DI
	MOV CX,lon ;indico el nº de elementos a leer
	INC  CX
	CLD	   ;hago que el stosb vaya hacia adelante
	MOV AL,'$'
	LEA DI,dir ;cargo direccion para la salida
	REP STOSB  ; inicializa la direccion dir con $
	MOV CX,lon
	LEA DI,dir ;devuelvo cadena
pedir1: MOV AH,1
	INT 21h
	CMP AL,13  ;si pulso intro salgo
	JE  fin_pedir
	STOSB      ;copio resto de cadena
	LOOP pedir1
fin_pedir:
	POP	DI
	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	AX	
	
	ENDM

escribir MACRO mem
        PUSH    DX
        PUSH    AX
        LEA     DX,mem
        MOV     AH,09H
        INT     21h
        POP     AX
        POP     DX
        ENDM
        
CURSOR   MACRO  FILA,COL
        PUSH    AX
        PUSH    BX
        PUSH    DX
        MOV     DH,fila
        MOV     DL,col
        MOV     BH,0
        MOV     AH,2
        INT     10h
        POP     DX
        POP     BX
        POP     AX
         ENDM

BORRAR MACRO
       MOV AL,0 ;limpio pantalla
       MOV CX,0
       MOV DX,2479h
       MOV BH,7
       MOV AH,6
       INT 10h
       ENDM
       
DECASC  MACRO  BINVC,ASCC
        LOCAL DEC1,DEC2
	PUSH	AX
	PUSH    BX
	PUSH	CX
	PUSH	DX
	PUSH	SI
	PUSH	DI
	LEA	DI,ASCC;
	
	MOV 	CX,3
	MOV	AL,' '
	REP     STOSB
	
        MOV  	AH,0       ;parte alta vacia para las comparaciones
        MOV     AL,BINVC 
        LEA	DI,ASCC[2] ; me situo al final de la cadena
        
        MOV	BL,10      ; constante para la division
        
DEC1:	CMP	AL,10      ; si es menor de 10 solo le sumo 30h y salgo
	JL	DEC2
	DIV	BL         ; en ah=resto, el al=cociente
	ADD     AH,30H     ;sumo cero hexadecimal
	MOV	[DI],AH    ;llevo a la salida
	DEC	DI     	   ;me voy al elemento siguiente de mas peso
	JMP	DEC1
DEC2:	ADD     AL,30H     ;si menor de 10 solo sumo 30h
	MOV	[DI],AL    ;llevo a la salida
	
	POP	DI
	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	AX
        ENDM 
       
ASCDEC  MACRO ASC,BINV ;esta macro pasa a binario numeros
    ;de dos cifras decimales unicamente
  LOCAL ASC1,ASC2,ASC11
	PUSH	AX
	PUSH    BX
	PUSH	CX
	PUSH	DX
	PUSH	SI
	PUSH	DI
    LEA	SI,ASC[1]  ; numero de menor peso
    mov cx,2
    MOV BX,1
    MOV	BINV,0
ASC1:   MOV AL,[SI]	; lo dejo en al para operar con el
	
	CMP	AL,'0'      ; filtro que solo sean numeros
	JL	asc2
	CMP	AL,'9'
	JG	asc2
	SUB     AL,30H     ; lo dejo ya en binario
	MOV     AH,0
    MUL     BL         ; en ax=al*bl salida en Al el otro operando
    ADD     binv,AL    ; suma acumulada
	MOV	AX,10
	MUL	BX         ; en ax salida en Al el otro operando
	MOV	BX,AX
ASC11:	DEC	SI
	LOOP    asc1	
asc2:   POP     DI
	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	AX                                        
        ENDM
        

burbuja MACRO n,v

LOCAL b1,b2,ord,sb2,sb1

        PUSH SI
        PUSH DI
        push bx
        PUSH CX
	
	mov di,0
	mov bx,0
        MOV SI,1   ;valor de inicio
        mov cl,n
        lea bx,v

b1: MOV DI,1
         
b2: MOV AL, [BX+DI-1]
        MOV AH, [BX+DI]
        CMP AH,AL
        JA ord  ;si estan bien no intercambio y sigo jg menor a mayor
        		;jb mayor a menor
                                
        MOV [BX+DI-1],AH ;si no intercambio
        MOV [BX+DI],AL
ord:
        MOV AX,CX  ;calculo nueva posici¢n
        SUB AX,SI

        CMP  DI,AX
        JAE  sb2
        INC  DI
        JMP  b2
sb2:
        CMP SI, Cx
        JAE sb1
        INC SI
        JMP b1
sb1:
	POP CX
 	pop bx
        POP DI
        POP SI
       
   ENDM
   


raizcuadra MACRO dimen, resul  ;macro usada en la practica 7
        local  fin,otrav
	PUSH	AX
	PUSH    BX
	PUSH	CX
	PUSH	DX
	PUSH	SI
	PUSH	DI
;usaremos el algoritmo de la resta de números enteros

    xor cx,cx ; pone cx a cero
    mov cl,[dimen] ;este valor es N x N (9 para 3 x 3)
    xor ax,ax ;en al estara el resultado 
    mov dx,-1    
    mov bx,cx ;dimension en bx
otrav:inc ax
    add dx,2  ; en dl los impares 
    sub bx,dx	;resta 1 de la dimension 9-1=8
	jbe fin
	jmp otrav
fin: mov [resul],al	
	
	POP	DI
	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	AX	
	
ENDM
   


genera MACRO num        ;macro usada en la practica 7
        
	PUSH	AX
	PUSH    BX
	PUSH	CX
	PUSH	DX
	PUSH	SI
	PUSH	DI
;usaremos el algoritmo de generacion de ruido pseudo-aleatorio
    xor ax,ax
    mov [num],078eh ;se da un valor inicial cualquiera 
    mov dx,[num]
    mov bx,dx
    and bx,7781h    ;realiza el producto logico con los puntos de control
desp:    shr bx,1
    adc ax,0    ;acumulo en ax el número de unos 
    cmp bx,0
    jnz desp  
    mov cl,2 
    div cl 
    shl dx,1
    shr ah,1      ;desplaza a la derecha ah
    adc dx,0  
    and dx,07ffh
    mov [num],dx
       
	
	POP	DI
	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	AX	
	
	ENDM