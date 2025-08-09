// Código desenvolvido pela dupla: Lucas Anjos e Patrick R. Lodi


char code MEDICOES [10][10] ={
		47,	49,	63,	79,	84,	84,	93,	0,	-3,	-8,
		49,	65,	70,	82,	84,	89,	92,	0,	-7,	-9,
		57,	71,	72,	84,	87,	89,	93,	94,	 0,	-2,
		69,	72,	78,	83,	85,	86,	87,	91,	94,	 0,
		65,	71,	74,	81,	79,	83,	82,	89,	93,	94,
		64,	70,	73,	72,	76,	75,	83,	89,	91,	96,
		54,	63,	65,	68,	73,	81,	82,	87,	96,	97,
		49,	52,	62,	61,	71,	78,	79,	84,	93,	94,
		 0,	49,	54,	67,	70,	79,	81,	89,	91,	92,
		-7,	 0,	49,	63,	67,	74,	81,	87,	92,	91};

// Lista de resultados
unsigned char AREA;
unsigned char NDVI;		
unsigned char POS_X, POS_Y;

#include <reg51.h>

//Inicializa as constantes RS e E nas portas as quais o LCD esta ligado
sbit RS = P3^6;
sbit E = P3^7;
sbit DB7 = P1^7;
sbit DB6 = P1^6;
sbit DB5 = P1^5;
sbit DB4 = P1^4;

void inicializa_timer()
{
	TMOD = 2; 	// Habilita timer() como temporizador de 8 bits
	TL0 = 0;	// Valor inicial para 256 contagens
	TH0 = 0;	// Valor inicial para 256 contagens
	TF0 = 0;		// Zera a sinalizacao de estouro
	TR0 = 1;		// Liga timer()
}	

	
void atraso_lcd()
{
	TL0 = 182;		// Valor inicial para 77 contagens
	TH0 = 182;		// Valor inicial para 77 contagens
	TF0 = 0;			// Zera a sinalizacao de estouro
	while(!TF0);	// Aguarda estouro do timer
}

bit getBit(char c, char bitNumber);

void escreve_dado(char c) {
	RS = 1;
	DB7 = getBit(c, 7);
	DB6 = getBit(c, 6);
	DB5 = getBit(c, 5);
	DB4 = getBit(c, 4);
	E = 1;
	E = 0;
	DB7 = getBit(c, 3);
	DB6 = getBit(c, 2);
	DB5 = getBit(c, 1);
	DB4 = getBit(c, 0);
	E = 1;
	E = 0;
	atraso_lcd();
	}


void escreve_comando(char c)
{
	RS=0;
	DB7 = getBit(c, 7);
	DB6 = getBit(c, 6);
	DB5 = getBit(c, 5);
	DB4 = getBit(c, 4);
	E = 1;
	E = 0;
	DB7 = getBit(c, 3);
	DB6 = getBit(c, 2);
	DB5 = getBit(c, 1);
	DB4 = getBit(c, 0);
	E = 1;
	E = 0;
	atraso_lcd();
}


// Funcao para limpar o LCD
void limpa_lcd()
{
	char c;
	escreve_comando(0x01);	//Comando para limpar o LCD

	for(c=0; c<40; c++)			//Atraso necessario para realizar o comando
		atraso_lcd();
}	


// Funcao para inicializar o LCD
void inicializa_lcd()
{
	// Rotina de seguranca para garantir que o LCD funcione
	RS=0;
	P1 &= 0x0F;
	P1 |= (0x20 & 0xF0);
	E=1;
	E=0;
	
	// Sequencia de comandos para inicializar o LCD
	atraso_lcd();
	escreve_comando(0x28); // Seta numero de linhas para 2
	escreve_comando(0x0C); // Liga LCD
	escreve_comando(0x06); // Seta a direcao de movimento do cursor para a direita (incrementa)
	limpa_lcd();
}

char converte_num(char num)
{
	switch(num)
	{
		case 0: return num=48;
		case 1: return num=49;
		case 2: return num=50;
		case 3: return num=51;
		case 4: return num=52;
		case 5: return num=53;
		case 6: return num=54;
		case 7: return num=55;
		case 8: return num=56;
		case 9: return num=57;
	}
}

void escreve_num(char num, char*vetor)
{
	vetor[0] = converte_num(num/10);
	vetor[1] = converte_num(num%10);
	vetor[2] = 32;
}

void main ()
{
	char i, j;						// auxiliares para percorrer a matriz
	unsigned long num=0;	// auxiliares para calculo da media
	char den=0;						// auxiliares para calculo da media
	char lim_esq=0, lim_dir=10, lim_cima=0, lim_baixo=10;
	char escreve[8];
	
	for (i=0; i<10; i++) // percorre as linhas da matriz
	{
		for (j=0; j<10; j++) // percorre as colunas da matriz
		{
			if (45 <= MEDICOES[i][j] &&  MEDICOES[i][j] <= 95) // verifica se o valor esta dentro do intervalo requerido
			{
				num = num + MEDICOES[i][j];				// soma o numerador da fra??o para calculo da media
				den++;
			}
			else	// define os limites onde a casa n?o pode estar
			{	
				if (i<5 && i>lim_cima)				lim_cima = i;
				else if (i>=5 && i<lim_baixo)	lim_baixo = i;
				if (j<5 && j>lim_esq)					lim_esq = j;
				else if (j>=5 && j<lim_dir)		lim_dir = j;
			}
		}
	}
	
	NDVI = num/den;
	AREA = den;
	POS_X = 10*(lim_esq+lim_dir)/2;
	POS_Y = 10*(lim_cima+lim_baixo)/2;
	
	inicializa_timer();
	inicializa_lcd();

	escreve[0] = 'A';
	escreve[1] = 'R';
	escreve[2] = 'E';
	escreve[3] = 'A';
	escreve[4] = '=';
	escreve_num(AREA,&escreve[5]);
	
	for(i=0;i<8;i++)
		escreve_dado(escreve[i]);
	
	escreve[0] = 'N';
	escreve[1] = 'D';
	escreve[2] = 'V';
	escreve[3] = 'I';
	escreve[4] = '=';
	escreve_num(NDVI,&escreve[5]);
	
	for(i=0;i<8;i++)
		escreve_dado(escreve[i]);

	escreve_comando(0xC0); // Coloca cursor na segunda linha

	escreve[0] = 'P';
	escreve[1] = 'O';
	escreve[2] = 'S';
	escreve[3] = 'X';
	escreve[4] = '=';
	escreve_num(POS_X,&escreve[5]);
	
	for(i=0;i<8;i++)
		escreve_dado(escreve[i]);

	escreve[0] = 'P';
	escreve[1] = 'O';
	escreve[2] = 'S';
	escreve[3] = 'Y';
	escreve[4] = '=';
	escreve_num(POS_Y,&escreve[5]);
	
	for(i=0;i<8;i++)
		escreve_dado(escreve[i]);

	while (1);
}

bit getBit(char c, char bitNumber) {
return (c >> bitNumber) & 1;
}