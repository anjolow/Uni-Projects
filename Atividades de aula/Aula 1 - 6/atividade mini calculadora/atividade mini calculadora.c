#include <stdio.h>
/*Esse programa define três numeros reais, soma e multiplica seus valores e exibe o resultado na tela
  Entradas: tres números reais
  Saída: a soma e produto dos valores lidos*/

int main(){

    float val1, val2, val3; //Declaracao das variaveis de entrada
    float soma, produto; //Declaracao da variavel com o resultado (saida)
    int fechar; //Clique nessa tecla para fechar o programa

    printf("Realize a soma e a multiplicacao de tres numeros reais:\n");
    printf("Informe um valor real: ");
    scanf("%f",&val1);
    printf("Informe outro valor real: ");
    scanf("%f",&val2);
    printf("Informe um ultimo valor real: ");
    scanf("%f",&val3);

    soma = val1 + val2 + val3;
    produto = val1 * val2 * val3;

    printf("\nResultado da soma: %.2f \n", soma);
    printf("Resultado da multiplicacao: %.2f \n", produto);

    printf("\nInsira algum caractere para fechar o programa: ");
    scanf("%d", &fechar);

    return 0;
}
