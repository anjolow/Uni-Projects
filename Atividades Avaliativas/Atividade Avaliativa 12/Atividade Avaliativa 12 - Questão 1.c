//Lucas Anjos da Silva
/*
    Este programa soma os d�gitos de um n�mero inteiro positivo e os retorna ao usu�rio.
    Exemplo: 12 -> 1+2=3
        Entradas: n�mero inteiro positivo a ser analisado
        Sa�das: soma dos d�gitos do n�mero
*/
#include <stdio.h>
#include <locale.h>

int somaDigitos(int n); //Prot�tipo da fun��o recursiva

int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    int n, res; //Vari�veis para receber o n�mero e para receber a soma

    printf("Informe um valor inteiro n�o negativo: ");
    do //La�o de repeti��o para o usu�rio informar um n�mero positivo
    {
        scanf("%d", &n); //Adquire o n�mero
        res = somaDigitos(n); //Chamada da fun��o
        if(res==-1) //Verifica��o do n�mero negativo
            printf("O n�mero informado � negativo. Por favor, informe um n�mero n�o negativo: ");
        else
            printf("A soma dos d�gitos de %d � %d\n", n, res); //Sa�da, informando a soma ao usu�rio
    }while(res==-1);

    return 0;
}

int somaDigitos(int n) //Fun��o que calcula a soma dos d�gitos de um n�mero por recursividade
{
    if(n<0) //Primeiro, verifica se a o usu�rio informou um n�mero negativo
        return -1;
    else
    {
        if(n==0) //Condi��o de parada da recursividade
        {
            return n; //Retorno da condi��o de parada
        }
        else
        {
            //Representa��o de fun��es para fazer o mesmo c�lculo usando um la�o de repeti��o:
            //      soma += n%10
            //      n = n/10
            return n%10+somaDigitos(n/10); //Implementa��o da recursividade
        }
    }
}
