//Lucas Anjos da Silva
/*Este programa recebe uma quantidade predeterminada de pontos, calcula a dist�ncia entre eles e exibe ao usu�rio a maior delas
    Entradas: coordenadas x e y dos pontos.
    Sa�das: pontos mais dist�ntes entre si, dist�ncia entre os pontos.*/

#include <stdio.h>
#include <math.h>
#include <locale.h>

#define N 5 //N�mero que define a quantidade de pontos a serem analisados

void recebe_pontos(float x[], float y[], int tamanho); //Fun��o para receber a coordenada x e y dos pontos
float calcula_dist(float x1, float y1, float x2, float y2); //Fun��o para calcular a distancia entre dois pontos
float pontos_distantes(float x[], float y[], float p1[], float p2[], float d, int tamanho); //Fun��o para determinar qual a maior dist�ncia entre os pontos e quais s�o esses pontos


int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    float x[N], y[N]; //Declara��o dos vetores para coordenadas dos pontos
    float p1[2], p2[2], d; //Declara��o das sa�das
    int tamanho=N;

    recebe_pontos(x, y, tamanho); //Chamada da fun��o para ler as coordenadas
    d = pontos_distantes(x, y, p1, p2, d, tamanho); //Atribu��o do valor de d como a maior dist�ncia entre os pontos

    printf("\nO par de pontos mais distantes entre si � (%.2f, %.2f) e (%.2f, %.2f), cuja dist�ncia � %.2f\n", p1[0], p1[1], p2[0], p2[1], d); //Imprime a sa�da ao usu�rio

    return 0;
}

void recebe_pontos(float x[], float y[], int tamanho)
{
    int i;
    for(i=0; i<tamanho; i++) //La�o de repeti��o para receber a quantidade predeterminada de pontos
    {
        printf("Informe as coordenadas x e y do ponto %d: ", i+1); //P�de ao usu�rio as coordenadas
        scanf("%f%f", &x[i], &y[i]); //L� as coordenadas
    }
}

float calcula_dist(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2)); //F�rmula para c�lculo da dist�ncia entre dois pontos
}

float pontos_distantes(float x[], float y[], float p1[], float p2[], float d, int tamanho)
{
    int i, o;
    float maior;

    maior = calcula_dist(x[0], y[0], x[1], y[1]); //Atribui a maior dist�ncia entre dois pontos quaisquer para fazer a compara��o

    //La�o de repeti��o duplo para comparar todos os pontos
    for(o=0; o<tamanho; o++)
    {
        for(i=0; i<tamanho; i++)
        {
            d = calcula_dist(x[o], y[o], x[i], y[i]);
            if(d>maior)
            {   //Atribui��o dos valores de sa�da
                maior = d;
                p1[0] = x[o];
                p1[1] = y[o];
                p2[0] = x[i];
                p2[1] = y[i];
            }
        }
    }
    return maior; //Retorna o valor da maior dist�ncia calculada
}
