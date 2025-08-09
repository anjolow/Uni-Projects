#include <stdio.h>
/*Esse programa define dois inteiros, soma seus valores e exibe o resultado na tela
  Entradas: dois valores inteiros (definidos no programa)
  Saída: a soma dos valores lidos*/

int main(){

    float val1, val2; //Declaracao das variaveis de entrada
    float soma; //Declaracao da variavel com o resultado (saida)

    printf("Realize a soma de dois números inteiros:\n");

    printf("Informe um valor real: ");
    scanf("%f",&val1);

    printf("Informe outro valor real: ");
    scanf("%f",&val2);

    soma = val1 + val2;

    printf("Resultado da soma: %.4f", soma);

    return(0);
}
