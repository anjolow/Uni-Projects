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

#include <reg52.h>

//Inicializa as constantes RS e E nas portas as quais o LCD esta ligado
sbit RS = P3^6;
sbit E = P3^7;
sbit LED = P3^4;
		
void inicializa_timer_0()
{
	TMOD = 2; 	// Habilita timer() como temporizador de 8 bits
	TL0 = 0;	// Valor inicial para 256 contagens
	TH0 = 0;	// Valor inicial para 256 contagens
	TF0 = 0;		// Zera a sinalizacao de estouro
	TR0 = 1;		// Liga timer()
}	

void inicializa_timer_2()
{
	T2CON = 4;	// Liga timer 2
	TH2 = 0x00;
	TL2 = 0x00;
	TF2 = 0;
}	
	
void atraso_lcd()
{
	TL0 = 182;		// Valor inicial para 40 contagens
	TH0 = 182;		// Valor inicial para 40 contagens
	TF0 = 0;			// Zera a sinalizacao de estouro
	while(!TF0);	// Aguarda estouro do timer
}

// função de delay de 1ms do algoritmo de debounce com timer de 1ms
void atraso()
{
	// Para 1843 contagens (65536 - 1000) = F8CD
	TH0 = 0xF8;
	TL0 = 0xCD;
	TF0 = 0;
	while(!TF0);
}

void inverte_led() interrupt 5
{
	TF2 = 0;
	LED = !LED;
}

void onda_100()
{
	// Para contagens (65536 - 9216) = DC00
	EA = 1;
	ET2 = 1;
	TH2 = 0xDC;
	TL2 = 0x00;
	RCAP2H = 0xDC;
	RCAP2L = 0x00;
	TF2 = 0;
}

void onda_200()
{
	// Para contagens (65536 - 4608) = EE00
	EA = 1;
	ET2 = 1;
	TH2 = 0xEE;
	TL2 = 0x00;
	RCAP2H = 0xEE;
	RCAP2L = 0x00;
	TF2 = 0;
}

void onda_300()
{
	// Para contagens (65536 - 3072) = F4000
	EA = 1;
	ET2 = 1;
	TH2 = 0xF4;
	TL2 = 0x00;
	RCAP2H = 0xF4;
	RCAP2L = 0x00;
	TF2 = 0;
}

void escreve_dado(char dado)
{
	RS=1;									// Habilita a funcao de escrita no LCD
	P1 &= 0x0F;						// Limpa porta 1
	P1 |= (dado & 0xF0);	// Verifica o proximo pino a ser preenchido
	E=1;									// Sobre e desce o enable para realizar a escrita
	E=0;
	P1 &= 0x0F;						// Limpa porta 1
	P1 |= (dado << 4);		// Esreve o dado no pino ainda nao preenchido da porta 1
	E=1;									// Sobre e desce o enable para realizar a escrita
	E=0;
	atraso_lcd();					// Chama o atraso para tudo ocorrer corretamente
}


void escreve_comando(char dado)
{
	RS=0;									// Habilita a funcao de comando no LCD
	P1 &= 0x0F;						// Limpa porta 1
	P1 |= (dado & 0xF0);	// Verifica o proximo pino a ser preenchido
	E=1;									// Sobre e desce o enable para realizar a escrita
	E=0;
	P1 &= 0x0F;						// Limpa porta 1
	P1 |= (dado << 4);		// Esreve o dado no pino ainda nao preenchido da porta 1
	E=1;									// Sobre e desce o enable para realizar a escrita
	E=0;
	atraso_lcd();					// Chama o atraso para tudo ocorrer corretamente
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

// algoritmo de debounce com atraso de 1ms, retorna o tecla atual
char debounce(char deb)
{
		char BOUNCE = 7;		// quantas repetições de bounce precisa fazer
	
		char count = 0;		// contagem de bounces
		char key_last = 0;			// última tecla guardada para comparação
		char key_now;				// tecla atual lida
			
		while(count<BOUNCE)		// enquanto contagem for menor do que o número de repetições
		{
				atraso();		// delay de 1ms
				key_now = (P0&(1<<deb));

				if(key_now==key_last)		// se uma for igual a outro
				{
					count++;		// aumenta a contagem
				}
				else
				{
					count=0;		// caso contrário zera a contagem
				}
			
				key_last = key_now;		// substituição de tecla para comparação
		}
			
		return key_now;		// devolve a tecla atual na função
}

// função que le a tecla pressionada e retorna o valor
char leitor_teclado()
{
		atraso();				//atraso de 1ms
		P0 &=~(1<<7);
		atraso();

		if(!debounce(0))
		{
			return '1';		// caso clique em 1
		}
		
		if(!debounce(1))
		{
			return '2';		// caso clique em 2
		}
		
		if(!debounce(2))	
		{
			return '3';		// caso clique em 3
		}

		P0 |= (1<<7);
		atraso();
		
		return '0';			// se não clicar em nenhum botão, retornar zero
}

void analise_terreno(num_min, num_max){
	
	char i, j;						// auxiliares para percorrer a matriz
	unsigned long num=0;	// auxiliares para calculo da media
	char den=0;						// auxiliares para calculo da media
	char lim_esq=0, lim_dir=9, lim_cima=0, lim_baixo=9;
	char escreve[8];
	
	escreve_comando(0x01);
	
	for (i=0; i<10; i++) // percorre as linhas da matriz
	{
		for (j=0; j<10; j++) // percorre as colunas da matriz
		{
			if (num_min <= MEDICOES[i][j] &&  MEDICOES[i][j] <= num_max) // verifica se o valor esta dentro do intervalo requerido
			{
				num = num + MEDICOES[i][j];				// soma o numerador da fra??o para calculo da media
				den++;
			}
			else	// define os limites onde a casa nao pode estar
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
}


void main ()
{
	char tecla_atual;
	char tecla_anterior = '0';
	
	inicializa_timer_0();
	inicializa_timer_2();
	inicializa_lcd();
	
	while(1)		// fica em loop lendo a tecla
		{
			atraso();
			tecla_atual = leitor_teclado();		// variável recepe a tecla do teclado
			switch(tecla_atual)		// função switch case, recebe um numero e compara com casos
			{
					case '1':		// se clicar em 1, limite de 45<= NDVI <= 95
							analise_terreno(45,95);
							tecla_anterior = '1';
							onda_100();
					break;
					
					case '2':		// se clicar em 2,  limite de 50<= NDVI <= 90
							analise_terreno(50,90);
							tecla_anterior = '2';
							onda_200();
					break;
						
					case '3':		// se clicar em 3,  limite de 55<= NDVI <= 85
							analise_terreno(55,85);
							tecla_anterior = '3';
							onda_300();
					break;
			}
		}
}
