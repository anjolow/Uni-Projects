//Lucas Anjos da Silva
/*
    Este programa lê um arquivo .txt que define um mapa que distribui um jogador e inimigos por ele e coloca todos os caracteres
    que representam as posições em uma matriz. Após, o programa acha as posições do jogador e de todos os inimigos no arquivo e
    as coloca em um novo arquivo .txt com o nome definido pelo usuário.

        Entradas: nome do arquivo a ser lido; nome do arquivo para registrar os dados de saída.
        Saídas: novo arquivo .txt; posições do jogador e dos inimigos (ninjas).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define NUM_NINJAS 50 //Definição do número máximo de ninjas
#define LINHAS 23 //Definição do número de linhas do mapa
#define COLUNAS 61 //Definição do número de colunas do mapa

//Estrutura para salvar as posições
typedef struct posicoes
{
    int x;
    int y;
}POSICAO;

//Declaração do protóripo das funções
int infomapa(char mapa[], POSICAO *jogador, POSICAO *ninjas, int *n_ninjas, char mat[][COLUNAS]);
void out(char saida[], POSICAO *jogador, POSICAO *ninjas, int n_ninjas);

//Programa principal
int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    POSICAO jogador; //Declaração da estrutura da posição do jogador
    POSICAO ninjas[NUM_NINJAS]; //Declaração da estrutura da posição dos ninjas
    char mapa[20], saida[20], mat[LINHAS][COLUNAS]; //Declaração das strings para receber o nome dos arquivos e da matriz que recebe o mapa
    int error, n_ninjas=0; //Variáveis para: 1-receber o valor retornado pela função infomapa; 2-calcular o n° de ninjas

    //Enunciado
    printf("---LEIA AS INFORMAÇÕES DE UM ARQUIVO DE TEXTO E ESCREVA-AS EM OUTRO---\nOBS: o número máximo de ninjas que esse programa analisa é %d\n\n", NUM_NINJAS);

    //Aquisição do nome do arquivo a ser lido
    printf("Informe o nome do arquivo a ser lido: ");
    scanf("%s", mapa);

    //Chamada da função principal
    error = infomapa(mapa, &jogador, ninjas, &n_ninjas, mat);

    //Verificação de erro ao abrir o arquivo
    if(error==0)
        printf("A leitura do arquivo \"%s\" foi mal sucedida.\n", mapa);
    else
    {
        //Aquisição do nome do arquivo de saída
        printf("Informe o nome do arquivo de saída: ");
        scanf("%s", saida);
        printf("\n");
        //Chamada da função para escrever no arquivo de saída
        out(saida, &jogador, ninjas, n_ninjas);
    }
    return 0;
}
//Função para ler e analisar as informações do mapa
int infomapa(char mapa[], POSICAO *jogador, POSICAO *ninjas, int *n_ninjas, char mat[][COLUNAS])
{
    int i, j, c=0; //Declaração de variáveis de auxílio
    FILE *file; //Ponteiro para manipulação de arquivo

    file=fopen(mapa, "r"); //Abertura do arquivo para leitura
    if(!file)
        return 0; //Caso ocorra erro, retorna 0 e finaliza o programa
    else
    {

        for(i=0; i<LINHAS; i++)
        {
            for(j=0; j<COLUNAS; j++)
            {
                //Atribuição de cada caractere do texto na matriz
                if(!fscanf(file, "%c", &mat[i][j]))
                    printf("Erro na leitura.\n");
                else
                //Verificação das posições do jogador e dos ninjas
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
        *n_ninjas = c; //Atribuição da contagem de ninjas na variável n_ninjas
        fclose(file); //Fecha o arquivo
        return 1;
    }
}
//Função para criar novo arquivo .txt e colocar as informações adquiridas nele, além de imprimi-las ao usuário
void out(char saida[], POSICAO *jogador, POSICAO *ninjas, int n_ninjas)
{
    int i; //Variável de auxílio
    FILE *file; //Ponteiro para manipulação de arquivo

    file = fopen(saida, "w"); //Cria um arquivo para escrita
    if(!file) //Verifica se houve erro na criação
        printf("Erro na criação do novo arquivo.\n");
    else
    {
        //Coloca a informação da posição do jogador no aquivo e depois a imprime para o usuário
        fprintf(file, "Posição do jogador: %d, %d\n", jogador->x, jogador->y);
        printf("Posição do jogador: %d, %d\n", jogador->x, jogador->y);

        //Coloca a informação da posição dos ninjas no aquivo e as imprime para o usuário
        for(i=0; i<n_ninjas; i++)
        {
            fprintf(file, "Posição do ninja %d: %d, %d\n", i+1, ninjas[i].x, ninjas[i].y);
            printf("Posição do ninja %d: %d, %d\n", i+1, ninjas[i].x, ninjas[i].y);
        }
        fclose(file); //Fecha o arquivo
    }
}
