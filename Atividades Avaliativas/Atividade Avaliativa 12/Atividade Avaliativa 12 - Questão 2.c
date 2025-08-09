//Lucas Anjos da Silva
/*
    Este programa adquire um vetor e verifica quantas vezes um valor se repete nele

        Entradas: tamanho do vetor; valor do vetor; valor alvo a ser analisado.
        Sa�das: quantas vezes esse valor se repete no vetor.
*/

#include <stdio.h>
#include <locale.h>

int contaValores(int v[], int tam, int n, int contador, int i); //Fun��o que faz a contagem por recursividade
void enunciado(); //Fun��o para imprimir o enunciado do programa

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    int tam, n, i, contador=0; //Declara��o das vari�veis

    enunciado();

    do //Aquisi��o do tamanho do vetor
    {
        scanf("%d", &tam);
        if(tam<1)
            printf("O tamanho n�o pode ser menor que 1. Informe novamente: ");
    }while(tam<1);

    int v[tam]; //Declara��o do vetor com o tamanho especificado

    //Aquisi��o das informa��es do vetor
    printf("\nInforme o vetor: ");
    for(i=0; i<tam; i++)
    {
        scanf("%d", &v[i]);
    }

    //Aquisi��o do valor a ser procurado
    printf("\nValor alvo: ");
    scanf("%d", &n);

    //Atribui��o de i como 0 para evitar erros
    i=0;

    //Imprime a sa�da ao usu�rio, chamando a fun��o dentro do printf
    printf("\nO vetor cont�m %d ocorr�ncias do valor %d\n", contaValores(v, tam, n, contador, i), n);

    return 0;
}

void enunciado() //Imprime as informa��es iniciais do programa ao usu�rio
{
    printf("---------------------------------------------------------------------------------------\n");
    printf("INFORME UM VETOR E AVALIE O N�MERO DE VEZES QUE UM VALOR 'n' APARECE EM UM VETOR 'v'\n");
    printf("---------------------------------------------------------------------------------------\n\n");
    printf("Informe o tamanho do vetor de entrada: ");
}

int contaValores(int v[], int tam, int n, int contador, int i) //Fun��o para contagem
{
    if(i==tam) //Condi��o de parada da recursividade
    {
        return contador; //Retorna, ao finalizar a procura, o valor do contador
    }
    else
    {
        //Verifica se o valor analisado � igual ao requerido

        //Se for, atribui +1 ao contador e ao �ndice de contagem de at� onde foi percorrido o vetor e chama a si mesmo novamente
        if(v[i]==n)
        {
            contador++;
            i++;
            return contaValores(v, tam, n, contador, i);
        }
        //Se n�o for, atribui +1 ao �ndice de contagem e chama a si mesmo novamente
        else
        {
            i++;
            return contaValores(v, tam, n, contador, i);
        }
    }
}
