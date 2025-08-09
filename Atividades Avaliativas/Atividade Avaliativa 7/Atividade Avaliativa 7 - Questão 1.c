//Lucas Anjos da Silva
/*Este programa recebe valores de coordenadas do centro de um círulo, seu raio e uma quantidade definida de pontos para calcular
se estes pontos estão dentro ou fora do círculo.
    Entradas: raio do círculo, coordenadas do centro do círculo, quantidade de pontos a serem avaliados, coordenadas dos pontos.
    Saídas: informação se o ponto está dentro ou fora do círculo.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

float local_ponto(float raio, float x_centro, float y_centro, float x_ponto, float y_ponto) //Função que calcula se o ponto está dentro ou fora do círculo e retorna um valor informando isto.
{
    float distancia;

    distancia = sqrt(pow(x_centro-x_ponto, 2) + pow(y_centro-y_ponto, 2));

    if(distancia>raio) return 1;
    else if(distancia<raio) return -1;
    else if(distancia=raio) return 0;

}

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    float raio, centro[2], armazena; //Variáveis para armazenar as informações do círculo e para armazenar o valor retornado pela função local_ponto
    float xy[99][2]; //Matriz para armazenar as coordenadas x e y dos pontos
    int qtd_pontos, i; //Variáveis para armazenar a quantidade de pontos que o usuário gostaria de avaliar e para auxiliar no laço de repetição


    //Usuário informa as informações do círculo
    printf("Informe o raio do círculo: ");
    scanf("%f", &raio);
    printf("Informe as coordenadas do centro do círculo (no formato 'x' 'y'): ");
    scanf("%f%f", &centro[0], &centro[1]);

    //Usuário informa a quantidade de pontos que quer avaliar
    printf("Informe a quantidade de pontos que gostaria de avaliar: ");
    do
    {
        scanf("%d", &qtd_pontos);
        if(qtd_pontos<1 || qtd_pontos>100)
            printf("Quantidade de pontos inválida. Ela deve estar entre 1 e 100.\nInforme novamente: ");
    }while(qtd_pontos<1 || qtd_pontos>100);

    //Laço de repetição onde o usuário informa a coordenada dos pontos e o programa retorna a informação da localidade do ponto
    for(i=0; i<qtd_pontos; i++)
    {
        printf("\nInforme as coordenadas do ponto %d (no formato 'x' 'y'): ", i+1);
        scanf("%f%f", &xy[i][0], &xy[i][1]);
        armazena = local_ponto(raio, centro[0], centro[1], xy[i][0], xy[i][1]);
        if(armazena==-1) printf("O ponto está dentro do círculo!\n");
        else if(armazena==1) printf("O ponto está fora do círculo!\n");
        else if(armazena==0) printf("O ponto está na borda do círculo!\n");
    }

    return 0;
}
