//Lucas Anjos da Silva
/*Este programa adquire valores para um vetor de tamanho predeterminado, imprime ao usu�rio os valores em ordem, solicita um novo valor
ao usu�rio, coloca este valor como o primeiro do vetor e desloca todos os outros uma casa para a direita. Ap�s, atribui o valor de todas
as casas �mapres como o a posi��o dela. Ex: casa 1, valor=1. Por fim, o programa calcula a m�dia de todos os componentes do vetor e v�
qual deles est� mais próximo da média.
    Entradas: vetor inicial, novo valor;
    Saídas: novo vetor, média dos valores, valor mais pr�ximo da m�dia.*/

#include <stdio.h>
#include <locale.h>
#include <math.h>

#define N 10

int main()
{
    setlocale(LC_CTYPE,"Portuguese");
    int i, o=9;
    float vet[N], new_value, acu=0, acu2=0, media, elem;

    for(i=0; i<N; i++)
    {
        printf("Informe o %d� de %d n�meros: ", i+1, N); //Pede que o usu�rio informe os valores do vetor
        scanf("%f", &vet[i]);
    }

    for(i=0; i<N; i++)
    {
        printf("%.2f\t", vet[i]); //Imprime o vetor ao usu�rio
    }

    printf("\nInfrome um novo valor: "); //Pede um novo valor ao usu�rio para ocupar a primeira casa do vetor
    scanf("%f", &new_value);

    //Desloca todos os elementos para as posi��es subsequentes e insere o novo valor como o primeiro do vetor
    for(i=0; i<(N-1); i++)
    {
        vet[o]=vet[o-1];
        o=o-1;
    }
    vet[0] = new_value;

    printf("\nNovo vetor com deslocamento:\n");
    for(i=0; i<N; i++)
    {
        printf("%.2f\t", vet[i]);
    }

    printf("\nNovo vetor com substitui��es:\n");
    //Faz as substitui��es solicitadas e imprime o vetor
    vet[1]=1;
    vet[3]=3;
    vet[5]=5;
    vet[7]=7;
    vet[9]=9;
    for(i=0; i<N; i++)
    {
        printf("%.2f\t", vet[i]);
    }

    //Acumula os valores de todos os vetores em uma vari�vel acumuladora e realiza o c�lculo da m�dia desses valores
    for(i=0; i<N; i++)
    {
        acu = acu + vet[i];
    }
    media = acu/N;

    //Calcula qual dos valores que comp�e o vetor est� mais pr�ximo da m�dia
    elem = vet[0];
    acu2 = media - vet[0];
    acu2 = abs(acu2);
    for(i=1; i<N; i++)
    {
        acu = 0;
        acu = media - vet[i];
        acu = abs(acu);
        if(acu<acu2)
        {
            elem = vet[i];
            acu2 = acu;
        }
    }
    //Imprime a m�dia e o valor mais pr�ximo dela
    printf("\nA m�dia dos elementos do vetor �: %.2f\n", media);
    printf("O elemento mais pr�ximo da m�dia � %.2f\n", elem);

    return 0;
}
