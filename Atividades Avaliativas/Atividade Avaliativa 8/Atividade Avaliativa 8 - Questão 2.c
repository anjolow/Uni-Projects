//Lucas Anjos da Silva
/*Este programa adquire valores (de 0 � 100) de dois vetores e compara os valores deles, indicando quais valores possuem em comum
e colocando eles em um terceiro vetor.

    Entradas: valores do vetor 1 e 2.
    Sa�das: vetores 1, 2 e 3 impressos; quantidade de valores em comum nos vetores 1 e 2 e os pr�prios valores.*/

#include <stdio.h>
#include <locale.h>

#define N 5

void le_vetor(int v[]); //Fun��o para ler os vetores
void imprime_vetor(int v[]); //Fun��o para imprimir os vetores
void repetidos(int v[]); //Fun��o para verificar se h� um n�mero que se repete mais de uma vez e, se for o caso, n�o o repete no vetor 3
int comparacao(int v1[], int v2[], int v3[]); //Fun��o para fazer a compara��o entre o vetor 1 e 2 e atribuir os valores em comum ao vetor 3. Retorna o tamanho do vetor 3


int main() //Fun��o principal
{
    setlocale(LC_CTYPE, "Portuguese");

    int v1[N], v2[N], v3[N]={0}, tamanho, i; //Declara��o dos vetores e de vari�veis para atribuir o tamanho e auxiliar para uso do for

    printf("Leitura do vetor 1:\n"); //Informa ao usu�rio que ser� realizada a leitura do vetor 1
    le_vetor(v1);
    printf("\n\nLeitura do vetor 2:\n"); //Informa ao usu�rio que ser� realizada a leitura do vetor 2
    le_vetor(v2);

    //Imprime os vetores 1 e 2
    printf("\nVetor 1: ");
    imprime_vetor(v1);
    printf("\nVetor 2: ");
    imprime_vetor(v2);

    //Atribui a vari�vel tamanho ao valor retornado pela fun��o comparacao
    tamanho = comparacao(v1, v2, v3);

    //Imprime o vetor 3
    printf("\nVetor 3: ");
    imprime_vetor(v3);

    //Imprime as sa�das
    printf("\n\nH� %d elemento(s) n�o repetidos que est�o simultaneamente nos vetores de interesse:\t", tamanho);
    for(i=0; i<tamanho; i++)
        printf("%d\t", v3[i]);

    printf("\n");
    return 0;
}

void le_vetor(int v[]) //Pede ao usu�rio um valor para completar o vetor e realiza a consist�ncia para o valor estar entre 0 e 100
{
    int i;
    for(i=0; i<N; i++)
    {
        printf("Informe o %d� valor inteiro do vetor: ", i+1);
        do
        {
            scanf("%d", &v[i]);
            if(v[i]<0 || v[i]>100)
                printf("O valor deve estar entre 0 e 100. Informe novamente: ");
        }while(v[i]<0 || v[i]>100);
    }
}

void imprime_vetor(int v[]) //Imprime o vetor
{
    int i;
    for(i=0; i<N; i++)
        printf("%d\t", v[i]);
}

void repetidos(int v[]) //Verifica se h� valores repetidos no vetor 3. Caso houver, transforma um desses valores em 0
{
    int i, o;

    for(i=0; i<N; i++)
        for(o=0; o<N; o++)
            if(v[i]==v[o])
                if(i!=o)
                    v[o]=0;
}

int comparacao(int v1[], int v2[], int v3[])
{
    int i, o, tam=0;

    //Faz a compara��o entre o primeiro e segundo vetores e atribui os valores em comum ao vetor 3
    for(i=0; i<N; i++)
        for(o=0; o<N; o++)
        {
            if(v1[i]==v2[o])
            {
                v3[i] = v2[o];
            }
        }

    //Chama a fun��o repetidos
    repetidos(v3);

    //Verifica o tamanho do vetor 3
    for(i=0; i<N; i++)
        if(v3[i]!=0)
            tam++;

    return tam; //Retorna o n�mero de elementos do vetor 3
}
