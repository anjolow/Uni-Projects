//Lucas Anjos da Silva
/*Converte um valor em Reais para D�lar
    Entradas: pre�o em real, taxa de convers�o
    Sa�das: pre�o em d�lar*/

#include <stdio.h>

int main(){

    float precoReal, taxa, precoDolar;

    printf("Informe o preco em Real: R$ "); //Entrada de pre�o em real
    scanf("%f", &precoReal);
    printf("Informe a taxa de converao: R$ "); //Entrada de taxa de convers�o em reais
    scanf("%f", &taxa);

    precoDolar = precoReal/taxa;
    printf("O preco em dolar vale: US$ %4.2f", precoDolar);

    return 0;
}
