//Lucas Anjos da Silva
/*
    Este programa soma os dígitos de um número inteiro positivo e os retorna ao usuário.
    Exemplo: 12 -> 1+2=3
        Entradas: número inteiro positivo a ser analisado
        Saídas: soma dos dígitos do número
*/
#include <stdio.h>
#include <locale.h>

int somaDigitos(int n); //Protótipo da função recursiva

int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    int n, res; //Variáveis para receber o número e para receber a soma

    printf("Informe um valor inteiro não negativo: ");
    do //Laço de repetição para o usuário informar um número positivo
    {
        scanf("%d", &n); //Adquire o número
        res = somaDigitos(n); //Chamada da função
        if(res==-1) //Verificação do número negativo
            printf("O número informado é negativo. Por favor, informe um número não negativo: ");
        else
            printf("A soma dos dígitos de %d é %d\n", n, res); //Saída, informando a soma ao usuário
    }while(res==-1);

    return 0;
}

int somaDigitos(int n) //Função que calcula a soma dos dígitos de um número por recursividade
{
    if(n<0) //Primeiro, verifica se a o usuário informou um número negativo
        return -1;
    else
    {
        if(n==0) //Condição de parada da recursividade
        {
            return n; //Retorno da condição de parada
        }
        else
        {
            //Representação de funções para fazer o mesmo cálculo usando um laço de repetição:
            //      soma += n%10
            //      n = n/10
            return n%10+somaDigitos(n/10); //Implementação da recursividade
        }
    }
}
