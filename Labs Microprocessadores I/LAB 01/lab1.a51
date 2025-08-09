; Desenvolva um código em Assembly para família MCS51 que leia uma lista de  
; oito números e informe no registrador R1 qual o maior número da lista, no registrador R0 
; qual o menor valor e no registrador R2 a quantidade de valores da lista que são números 
; primos*.  
; Usar como base o exemplo abaixo 
; // Aponta para inicio da  lista 
; MOV DPTR, #LISTA 
; //Move para A índice da lista  
; MOV A, #0 
; // Le valor 
; MOVC A, @A+DPTR  
; // Seu código … 
; LISTA: 
; DB 23, 8, 10, 68, 31, 17, 9, 36 
; END

MOV DPTR, #LISTA   ; Aponta para o início da lista
MOV R2, #0       ; Inicializa R2 para contar os números primos
MOV R3, #0		 ; Inicializa R3 para ser o registrador auxiliar
MOV R6, #7       ; Número de elementos na lista (8)

MOV A, R6       	; Inicializa o índice (A) para acessar a lista
MOVC A, @A+DPTR  	; Move o valor da lista (A + DPTR) para o acumulador A
MOV R0, A			; Inicializa o primeiro número da lista como maior
MOV R1, A			; Inicializa o primeiro número da lista como menor

LOOP:
	CLR C
	MOV A, R6         ; Inicializa o índice (A) para acessar a lista
    MOVC A, @A+DPTR   ; Move o valor da lista (A + DPTR) para o acumulador A
	MOV R3, A				; Utiliza R3 para guardar o número da lista que estamos analisando neste loop
	MOV B, R3				; Move R3 para B
    MOV A, R1				; Move o valor de R1 para A
    CJNE A, B, CHECK_MAX	; Se A != R1, verifica o maior valor

CHECK_MAX:
	SUBB A, B		; Subtrati o número atual que estamos analisando do maior
	JC MAX			; Caso o número atual for maior, vai para MAX
    JNC CHECK_MIN	; Se R3 < R1, pula para verificar o mínimo

MAX:
	MOV A, R3		; Registra o número atual como maior
	MOV R1, A
	JMP CHECK_PRIME	; Vai verificar se o número é primo

CHECK_MIN:
	MOV A, R3		; Faz as atribuições necessárias
	MOV B, R0
	SUBB A, B		; Subtrai o número que estamos analisando do menor
	JC MIN			; Caso o número atual for menor, vai para MIN
	JNC CHECK_PRIME	; Caso não, vai checar se o número atual é primo

MIN:
	MOV A, R3		; Registra o número atual como menor
	MOV R0, A
	JMP CHECK_PRIME ; Vai checar se o número atual é primo
	
CHECK_PRIME:
	MOV A, R3
   	MOV R5, A		; Coloca o número atual em R5
	DEC R5          ; Decrementa R5
	CJNE A, #1, DIV_LOOP ; Se não for 1, verifica se é primo
    SJMP NOT_PRIME	; 1 não é primo

DIV_LOOP:
	MOV B, R5		; Move o divisor para B
    MOV A, R3		; Move o número a ser verificado para A
    DIV AB          ; A = R3 (número atual a ser verificado) / R5 (possíveis divisores)
	MOV A, B
	JZ NOT_PRIME   ; Se o resto é zero, não é primo
	DEC R5          ; Decrementa R5
	MOV A, R5
    CJNE A, #1, DIV_LOOP	; Faz a verificação até o divisor ser 1. Caso seja e passe daqui, o número é primo

    ; Se chegou aqui, o número é primo
    INC R2          ; Incrementa R2
	JMP NEXT	; Vai verificar o próximo número

NOT_PRIME:
    JMP NEXT	; Vai verificar o próximo núemro

NEXT:
    DEC R6		; Decrementa o contador e repete o loop para os 8 números
	MOV A, R6	; Move o valor atual para A
	INC A		; Increenta A. Se chegar em 0, a lista acabou
	JZ FIM		; Se acabou a lista, vai para o FIM
	JMP LOOP	; Se não, recomça o loop

FIM:			; Loop final para travar o programa
	JMP FIM

LISTA:
    DB 23, 8, 10, 68, 31, 17, 9, 36
		
END
