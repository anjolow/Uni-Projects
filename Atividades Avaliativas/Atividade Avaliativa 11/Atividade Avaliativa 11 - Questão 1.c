//Lucas Anjos da Silva
/*
    Este programa l� um arquivo .txt que define um mapa que distribui um jogador e inimigos por ele e coloca todos os caracteres
    que representam as posi��es em uma matriz. Ap�s, o programa acha as posi��es do jogador e de todos os inimigos no arquivo e
    as coloca em um novo arquivo .txt com o nome definido pelo usu�rio.

        Entradas: nome do arquivo a ser lido; nome do arquivo para registrar os dados de sa�da.
        Sa�das: novo arquivo .txt; posi��es do jogador e dos inimigos (ninjas).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NUM_NINJAS 50 //Defini��o do n�mero m�ximo de ninjas
#define LINHAS 23 //Defini��o do n�mero de linhas do mapa
#define COLUNAS 61 //Defini��o do n�mero de colunas do mapa

//Estrutura para salvar as posi��es
typedef struct posicoes
{
    int x;
    int y;
}POSICAO;

//Declara��o do prot�ripo das fun��es
int infomapa(char mapa[], POSICAO *jogador, POSICAO *ninjas, int *n_ninjas, char mat[][COLUNAS]);
void out(char saida[], POSICAO *jogador, POSICAO *ninjas, int n_ninjas);

//Programa principal
int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    POSICAO jogador; //Declara��o da estrutura da posi��o do jogador
    POSICAO ninjas[NUM_NINJAS]; //Declara��o da estrutura da posi��o dos ninjas
    char mapa[20], saida[20], mat[LINHAS][COLUNAS]; //Declara��o das strings para receber o nome dos arquivos e da matriz que recebe o mapa
    int error, n_ninjas=0; //Vari�veis para: 1-receber o valor retornado pela fun��o infomapa; 2-calcular o n� de ninjas

    //Enunciado
    printf("---LEIA AS INFORMA��ES DE UM ARQUIVO DE TEXTO E ESCREVA-AS EM OUTRO---\nOBS: o n�mero m�ximo de ninjas que esse programa analisa � %d\n\n", NUM_NINJAS);

    //Aquisi��o do nome do arquivo a ser lido
    printf("Informe o nome do arquivo a ser lido: ");
    scanf("%s", mapa);

    //Chamada da fun��o principal
    error = infomapa(mapa, &jogador, ninjas, &n_ninjas, mat);

    //Verifica��o de erro ao abrir o arquivo
    if(error==0)
        printf("A leitura do arquivo \"%s\" foi mal sucedida.\n", mapa);
    else
    {
        //Aquisi��o do nome do arquivo de sa�da
        printf("Informe o nome do arquivo de sa�da: ");
        scanf("%s", saida);
        printf("\n");
        //Chamada da fun��o para escrever no arquivo de sa�da
        out(saida, &jogador, ninjas, n_ninjas);
    }
    return 0;
}
//Fun��o para ler e analisar as informa��es do mapa
int infomapa(char mapa[], POSICAO *jogador, POSICAO *ninjas, int *n_ninjas, char mat[][COLUNAS])
{
    int i, j, c=0; //Declara��o de vari�veis de aux�lio
    FILE *file; //Ponteiro para manipula��o de arquivo

    file=fopen(mapa, "r"); //Abertura do arquivo para leitura
    if(!file)
        return 0; //Caso ocorra erro, retorna 0 e finaliza o programa
    else
    {

        for(i=0; i<LINHAS; i++)
        {
            for(j=0; j<COLUNAS; j++)
            {
                //Atribui��o de cada caractere do texto na matriz
                if(!fscanf(file, "%c", &mat[i][j]))
                    printf("Erro na leitura.\n");
                else
                //Verifica��o das posi��es do jogador e dos ninjas
                    switch(mat[i][j])
                    {
                    case 'J':
                        jogador->x = i+1;
                        jogador->y = j+1;
                        break;
                    case 'N':
                        ninjas[c].x = i+1;
                        ninjas[c].y = j+1;
                        c++;
                        break;
                    }
            }
        }
        *n_ninjas = c; //Atribui��o da contagem de ninjas na vari�vel n_ninjas
        fclose(file); //Fecha o arquivo
        return 1;
    }
}
//Fun��o para criar novo arquivo .txt e colocar as informa��es adquiridas nele, al�m de imprimi-las ao usu�rio
void out(char saida[], POSICAO *jogador, POSICAO *ninjas, int n_ninjas)
{
    int i; //Vari�vel de aux�lio
    FILE *file; //Ponteiro para manipula��o de arquivo

    file = fopen(saida, "w"); //Cria um arquivo para escrita
    if(!file) //Verifica se houve erro na cria��o
        printf("Erro na cria��o do novo arquivo.\n");
    else
    {
        //Coloca a informa��o da posi��o do jogador no aquivo e depois a imprime para o usu�rio
        fprintf(file, "Posi��o do jogador: %d, %d\n", jogador->x, jogador->y);
        printf("Posi��o do jogador: %d, %d\n", jogador->x, jogador->y);

        //Coloca a informa��o da posi��o dos ninjas no aquivo e as imprime para o usu�rio
        for(i=0; i<n_ninjas; i++)
        {
            fprintf(file, "Posi��o do ninja %d: %d, %d\n", i+1, ninjas[i].x, ninjas[i].y);
            printf("Posi��o do ninja %d: %d, %d\n", i+1, ninjas[i].x, ninjas[i].y);
        }
        fclose(file); //Fecha o arquivo
    }
}
