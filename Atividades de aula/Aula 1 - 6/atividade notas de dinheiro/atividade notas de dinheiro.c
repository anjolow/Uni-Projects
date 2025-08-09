#include <stdio.h>
/*Dado a parte inteira de um valor em reais,
calcular e mostrar o mínimo de notas
equivalentes a este valor.*/


int main(){

    int valor, v; //Entradas
    int n100, n50, n20, n10, n5, n2, n1; //Saídas de notas

    printf("Insira um valor em reais: R$ ");
    scanf("%d", &valor);

    v = valor;
//Cálculo de notas
    n100 = v/100;
    v = v%100;
    n50 = v/50;
    v = v%50;
    n20 = v/20;
    v = v%20;
    n10 = v/10;
    v = v%10;
    n5 = v/5;
    v = v%5;
    n2 = v/2;
    n1 = v%2;

    printf("Valor lido: %d \n 100:\t%d \n 50:\t%d \n 20:\t%d \n 10:\t%d \n 5:\t%d \n 2:\t%d \n 1:\t%d", valor, n100, n50, n20, n10, n5, n2, n1);

    return 0;

}
