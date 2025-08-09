//Lucas Anjos da Silva
/*Converte um valor em Reais para Dólar
    Entradas: preço em real, taxa de conversão
    Saídas: preço em dólar*/

#include <stdio.h>

int main(){

    float precoReal, taxa, precoDolar;

    printf("Informe o preco em Real: R$ "); //Entrada de preço em real
    scanf("%f", &precoReal);
    printf("Informe a taxa de converao: R$ "); //Entrada de taxa de conversão em reais
    scanf("%f", &taxa);

    precoDolar = precoReal/taxa;
    printf("O preco em dolar vale: US$ %4.2f", precoDolar);

    return 0;
}
