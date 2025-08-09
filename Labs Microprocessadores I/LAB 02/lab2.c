// Código desenvolvido pela dupla: Lucas Anjos e Patrick R. Lodi


char code MEDICOES [10][10] ={
	-12,  1, 32, 49, 70, 79, 89, 88,  78, 89, 
	-17, -2, 30, 58, 79, 91, 83, 83,  71, 97,
	 -9, 18, 39, 53, 78, 87, 93, 97,  98, 100,
	 -7, 29, 58, 79, 91, 90, 97, 98,  99, 100,
	  3, 31, 59, 70, 87, 91, 96, 99, 100, 99,
	  8, 39, 67, 79, 84, 93, 97, 100, 98, 97,
	 19, 43, 70, 79, 89, 92, 93, 97,  99, 98,
	 27, 49, 68, 73, 84, 90, 93, 96,  97, 98,
	 38, 52, 71, 81, 89, 92, 94, 96,  99, 97,
 	 43, 52, 74, 82, 87, 90, 91, 93,  94, 98};
// Lista de resultados
unsigned char AREA;
unsigned char NDVI;		
unsigned char POS_X, POS_Y;

void main ()
{
	char i, j;						// auxiliares para percorrer a matriz
	unsigned long num=0;	// auxiliares para calculo da media
	char den=0;						// auxiliares para calculo da media
	char lim_esq=0, lim_dir=10, lim_cima=0, lim_baixo=10;
	
	
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
	POS_X = (lim_esq+lim_dir)/2;
	POS_Y = (lim_cima+lim_baixo)/2;
	
	while (1);
}