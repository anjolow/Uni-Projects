//Lucas Anjos da Silva
/*Este programa recebe valores de coordenadas do centro de um c�rulo, seu raio e uma quantidade definida de pontos para calcular
se estes pontos est�o dentro ou fora do c�rculo.
    Entradas: raio do c�rculo, coordenadas do centro do c�rculo, quantidade de pontos a serem avaliados, coordenadas dos pontos.
    Sa�das: informa��o se o ponto est� dentro ou fora do c�rculo.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

float local_ponto(float raio, float x_centro, float y_centro, float x_ponto, float y_ponto) //Fun��o que calcula se o ponto est� dentro ou fora do c�rculo e retorna um valor informando isto.
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

    float raio, centro[2], armazena; //Vari�veis para armazenar as informa��es do c�rculo e para armazenar o valor retornado pela fun��o local_ponto
    float xy[99][2]; //Matriz para armazenar as coordenadas x e y dos pontos
    int qtd_pontos, i; //Vari�veis para armazenar a quantidade de pontos que o usu�rio gostaria de avaliar e para auxiliar no la�o de repeti��o


    //Usu�rio informa as informa��es do c�rculo
    printf("Informe o raio do c�rculo: ");
    scanf("%f", &raio);
    printf("Informe as coordenadas do centro do c�rculo (no formato 'x' 'y'): ");
    scanf("%f%f", &centro[0], &centro[1]);

    //Usu�rio informa a quantidade de pontos que quer avaliar
    printf("Informe a quantidade de pontos que gostaria de avaliar: ");
    do
    {
        scanf("%d", &qtd_pontos);
        if(qtd_pontos<1 || qtd_pontos>100)
            printf("Quantidade de pontos inv�lida. Ela deve estar entre 1 e 100.\nInforme novamente: ");
    }while(qtd_pontos<1 || qtd_pontos>100);

    //La�o de repeti��o onde o usu�rio informa a coordenada dos pontos e o programa retorna a informa��o da localidade do ponto
    for(i=0; i<qtd_pontos; i++)
    {
        printf("\nInforme as coordenadas do ponto %d (no formato 'x' 'y'): ", i+1);
        scanf("%f%f", &xy[i][0], &xy[i][1]);
        armazena = local_ponto(raio, centro[0], centro[1], xy[i][0], xy[i][1]);
        if(armazena==-1) printf("O ponto est� dentro do c�rculo!\n");
        else if(armazena==1) printf("O ponto est� fora do c�rculo!\n");
        else if(armazena==0) printf("O ponto est� na borda do c�rculo!\n");
    }

    return 0;
}
