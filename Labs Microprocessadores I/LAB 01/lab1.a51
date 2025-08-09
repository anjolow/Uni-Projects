; Desenvolva um c�digo em Assembly para fam�lia MCS51 que leia uma lista de  
; oito n�meros e informe no registrador R1 qual o maior n�mero da lista, no registrador R0 
; qual o menor valor e no registrador R2 a quantidade de valores da lista que s�o n�meros 
; primos*.  
; Usar como base o exemplo abaixo 
; // Aponta para inicio da  lista 
; MOV DPTR, #LISTA 
; //Move para A �ndice da lista  
; MOV A, #0 
; // Le valor 
; MOVC A, @A+DPTR  
; // Seu c�digo � 
; LISTA: 
; DB 23, 8, 10, 68, 31, 17, 9, 36 
; END

MOV DPTR, #LISTA   ; Aponta para o in�cio da lista
MOV R2, #0       ; Inicializa R2 para contar os n�meros primos
MOV R3, #0		 ; Inicializa R3 para ser o registrador auxiliar
MOV R6, #7       ; N�mero de elementos na lista (8)

MOV A, R6       	; Inicializa o �ndice (A) para acessar a lista
MOVC A, @A+DPTR  	; Move o valor da lista (A + DPTR) para o acumulador A
MOV R0, A			; Inicializa o primeiro n�mero da lista como maior
MOV R1, A			; Inicializa o primeiro n�mero da lista como menor

LOOP:
	CLR C
	MOV A, R6         ; Inicializa o �ndice (A) para acessar a lista
    MOVC A, @A+DPTR   ; Move o valor da lista (A + DPTR) para o acumulador A
	MOV R3, A				; Utiliza R3 para guardar o n�mero da lista que estamos analisando neste loop
	MOV B, R3				; Move R3 para B
    MOV A, R1				; Move o valor de R1 para A
    CJNE A, B, CHECK_MAX	; Se A != R1, verifica o maior valor

CHECK_MAX:
	SUBB A, B		; Subtrati o n�mero atual que estamos analisando do maior
	JC MAX			; Caso o n�mero atual for maior, vai para MAX
    JNC CHECK_MIN	; Se R3 < R1, pula para verificar o m�nimo

MAX:
	MOV A, R3		; Registra o n�mero atual como maior
	MOV R1, A
	JMP CHECK_PRIME	; Vai verificar se o n�mero � primo

CHECK_MIN:
	MOV A, R3		; Faz as atribui��es necess�rias
	MOV B, R0
	SUBB A, B		; Subtrai o n�mero que estamos analisando do menor
	JC MIN			; Caso o n�mero atual for menor, vai para MIN
	JNC CHECK_PRIME	; Caso n�o, vai checar se o n�mero atual � primo

MIN:
	MOV A, R3		; Registra o n�mero atual como menor
	MOV R0, A
	JMP CHECK_PRIME ; Vai checar se o n�mero atual � primo
	
CHECK_PRIME:
	MOV A, R3
   	MOV R5, A		; Coloca o n�mero atual em R5
	DEC R5          ; Decrementa R5
	CJNE A, #1, DIV_LOOP ; Se n�o for 1, verifica se � primo
    SJMP NOT_PRIME	; 1 n�o � primo

DIV_LOOP:
	MOV B, R5		; Move o divisor para B
    MOV A, R3		; Move o n�mero a ser verificado para A
    DIV AB          ; A = R3 (n�mero atual a ser verificado) / R5 (poss�veis divisores)
	MOV A, B
	JZ NOT_PRIME   ; Se o resto � zero, n�o � primo
	DEC R5          ; Decrementa R5
	MOV A, R5
    CJNE A, #1, DIV_LOOP	; Faz a verifica��o at� o divisor ser 1. Caso seja e passe daqui, o n�mero � primo

    ; Se chegou aqui, o n�mero � primo
    INC R2          ; Incrementa R2
	JMP NEXT	; Vai verificar o pr�ximo n�mero

NOT_PRIME:
    JMP NEXT	; Vai verificar o pr�ximo n�emro

NEXT:
    DEC R6		; Decrementa o contador e repete o loop para os 8 n�meros
	MOV A, R6	; Move o valor atual para A
	INC A		; Increenta A. Se chegar em 0, a lista acabou
	JZ FIM		; Se acabou a lista, vai para o FIM
	JMP LOOP	; Se n�o, recom�a o loop

FIM:			; Loop final para travar o programa
	JMP FIM

LISTA:
    DB 23, 8, 10, 68, 31, 17, 9, 36
		
END
