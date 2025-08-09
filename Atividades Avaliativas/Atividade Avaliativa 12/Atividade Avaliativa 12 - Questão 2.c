//Lucas Anjos da Silva
/*
    Este programa adquire um vetor e verifica quantas vezes um valor se repete nele

        Entradas: tamanho do vetor; valor do vetor; valor alvo a ser analisado.
        Saídas: quantas vezes esse valor se repete no vetor.
*/

#include <stdio.h>
#include <locale.h>

int contaValores(int v[], int tam, int n, int contador, int i); //Função que faz a contagem por recursividade
void enunciado(); //Função para imprimir o enunciado do programa

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    int tam, n, i, contador=0; //Declaração das variáveis

    enunciado();

    do //Aquisição do tamanho do vetor
    {
        scanf("%d", &tam);
        if(tam<1)
            printf("O tamanho não pode ser menor que 1. Informe novamente: ");
    }while(tam<1);

    int v[tam]; //Declaração do vetor com o tamanho especificado

    //Aquisição das informações do vetor
    printf("\nInforme o vetor: ");
    for(i=0; i<tam; i++)
    {
        scanf("%d", &v[i]);
    }

    //Aquisição do valor a ser procurado
    printf("\nValor alvo: ");
    scanf("%d", &n);

    //Atribuição de i como 0 para evitar erros
    i=0;

    //Imprime a saída ao usuário, chamando a função dentro do printf
    printf("\nO vetor contém %d ocorrências do valor %d\n", contaValores(v, tam, n, contador, i), n);

    return 0;
}

void enunciado() //Imprime as informações iniciais do programa ao usuário
{
    printf("---------------------------------------------------------------------------------------\n");
    printf("INFORME UM VETOR E AVALIE O NÚMERO DE VEZES QUE UM VALOR 'n' APARECE EM UM VETOR 'v'\n");
    printf("---------------------------------------------------------------------------------------\n\n");
    printf("Informe o tamanho do vetor de entrada: ");
}

int contaValores(int v[], int tam, int n, int contador, int i) //Função para contagem
{
    if(i==tam) //Condição de parada da recursividade
    {
        return contador; //Retorna, ao finalizar a procura, o valor do contador
    }
    else
    {
        //Verifica se o valor analisado é igual ao requerido

        //Se for, atribui +1 ao contador e ao índice de contagem de até onde foi percorrido o vetor e chama a si mesmo novamente
        if(v[i]==n)
        {
            contador++;
            i++;
            return contaValores(v, tam, n, contador, i);
        }
        //Se não for, atribui +1 ao índice de contagem e chama a si mesmo novamente
        else
        {
            i++;
            return contaValores(v, tam, n, contador, i);
        }
    }
}
