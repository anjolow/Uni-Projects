//Lucas Anjos da Silva
/*Este programa recebe uma quantidade predeterminada de pontos, calcula a distância entre eles e exibe ao usuário a maior delas
    Entradas: coordenadas x e y dos pontos.
    Saídas: pontos mais distântes entre si, distância entre os pontos.*/

#include <stdio.h>
#include <math.h>
#include <locale.h>

#define N 5 //Número que define a quantidade de pontos a serem analisados

void recebe_pontos(float x[], float y[], int tamanho); //Função para receber a coordenada x e y dos pontos
float calcula_dist(float x1, float y1, float x2, float y2); //Função para calcular a distancia entre dois pontos
float pontos_distantes(float x[], float y[], float p1[], float p2[], float d, int tamanho); //Função para determinar qual a maior distância entre os pontos e quais são esses pontos


int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    float x[N], y[N]; //Declaração dos vetores para coordenadas dos pontos
    float p1[2], p2[2], d; //Declaração das saídas
    int tamanho=N;

    recebe_pontos(x, y, tamanho); //Chamada da função para ler as coordenadas
    d = pontos_distantes(x, y, p1, p2, d, tamanho); //Atribução do valor de d como a maior distância entre os pontos

    printf("\nO par de pontos mais distantes entre si é (%.2f, %.2f) e (%.2f, %.2f), cuja distância é %.2f\n", p1[0], p1[1], p2[0], p2[1], d); //Imprime a saída ao usuário

    return 0;
}

void recebe_pontos(float x[], float y[], int tamanho)
{
    int i;
    for(i=0; i<tamanho; i++) //Laço de repetição para receber a quantidade predeterminada de pontos
    {
        printf("Informe as coordenadas x e y do ponto %d: ", i+1); //Pède ao usuário as coordenadas
        scanf("%f%f", &x[i], &y[i]); //Lê as coordenadas
    }
}

float calcula_dist(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2)); //Fórmula para cálculo da distância entre dois pontos
}

float pontos_distantes(float x[], float y[], float p1[], float p2[], float d, int tamanho)
{
    int i, o;
    float maior;

    maior = calcula_dist(x[0], y[0], x[1], y[1]); //Atribui a maior distância entre dois pontos quaisquer para fazer a comparação

    //Laço de repetição duplo para comparar todos os pontos
    for(o=0; o<tamanho; o++)
    {
        for(i=0; i<tamanho; i++)
        {
            d = calcula_dist(x[o], y[o], x[i], y[i]);
            if(d>maior)
            {   //Atribuição dos valores de saída
                maior = d;
                p1[0] = x[o];
                p1[1] = y[o];
                p2[0] = x[i];
                p2[1] = y[i];
            }
        }
    }
    return maior; //Retorna o valor da maior distância calculada
}
