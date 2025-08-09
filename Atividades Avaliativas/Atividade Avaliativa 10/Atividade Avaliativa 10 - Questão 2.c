//Lucas Anjos da Silva
/*
Este programa adquire um percentual para aumento salarial e informa qual o sal�rio antigo e novo dos funcion�rios registrados.
    Entradas: percentual.
    Sa�das: nome, sal�rio antigo e sal�rio aqualizado de todos os funcion�rios.
*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Estrutura do funcion�rio (mesma utilizada no programa anterior
typedef struct funcionario
{
    char nome[80];
    float salario;
}FUNCIONARIO;

//Estrutura para o registro do novo sal�rio
typedef struct novo
{
    float salario;
}NEW_WAGE;

//Prot�tipos das fun��es
void atualiza(FUNCIONARIO *func, float percentual, char file_name[], NEW_WAGE *novo, char new_file[]);
void escreve(NEW_WAGE *novo, char new_file[]);
void mostra_lista(FUNCIONARIO *func, char file_name[], NEW_WAGE *novo, char new_file[]);

//Programa principal
int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    float percentual; //Vari�vel para adrquirir o percentual
    FUNCIONARIO func; //Declara��o da estrutura de funcion�rio
    NEW_WAGE novo; //Declara��o da estrutura de novo sal�rio
    char file_name[]={"funcionarios.dat"}; //Atribui��o de nome do arquivo gerado pelo programa anterior (se for mudado no programa anterior, deve conter o mesmo nome neste programa)
    char new_file[]={"atualizados.dat"}; //Atribui��o de nome do novo arquivo gerado por este programa, para mudan�a mais r�pida caso se deseje

    //Adquire o percentual desejado
    printf("Informe o percentual de aumento salarial: ");
    scanf("%f", &percentual);

    //Chamada da fun��o para atualizar o sal�rio dos funcion�rios
    atualiza(&func, percentual, file_name, &novo, new_file);

    //Impress�o das sa�das
    printf("\nFuncion�rios:\n\n");
    mostra_lista(&func, file_name, &novo, new_file);

    return 0;
}

void atualiza(FUNCIONARIO *func, float percentual, char file_name[], NEW_WAGE *novo, char new_file[]) //Fun��o que atualiza o sal�rio dos funcion�rios
{
    FILE *file;
    //Abre o arquivo "funcionarios.dat" para leitura
    file = fopen(file_name, "rb");
    //Verifica se houve erro na abertura
    if(!(file))
    {
        printf("Erro ao abrir arquivo.");
    }
    else
    {
        while(!(feof(file)))
        {   //Executa a leitura do arquivo at� o seu final
            if(fread(&(*func), sizeof(FUNCIONARIO), 1, file) == 1)
            {
                novo->salario = func->salario*(1+(percentual/100)); //Calcula o novo sal�rio e atribui � estrutura que cont�m essa informa��o
                escreve(&(*novo), new_file); //Chamada da fun��o para escrever o que foi calculado em um arquivo novo
            }
        }
        fclose(file); //Fecha o arquivo que estava lendo os sal�rios
    }
}

void escreve(NEW_WAGE *novo, char new_file[]) //Fun��o para gravar o sal�rio atualizado em um novo arquivo
{
    FILE *file;
    //Abre o arquivo "atualizados.dat" para escrita, mantendo as informa��es j� contidas nele.
    file = fopen(new_file, "ab");
    //Verifica se houve erro na abertura
    if(!(file))
    {
        printf("Erro ao abrir arquivo.");
    }
    else
    {
        if(fwrite(&(*novo), sizeof(NEW_WAGE), 1, file)!=1) //Escreve a informa��o do novo sal�rio no arquivo
            printf("Erro na escrita.\n");

        fclose(file); //Fecha o arquivo
    }
}

void mostra_lista(FUNCIONARIO *func, char file_name[], NEW_WAGE *novo, char new_file[]) //Fun��o para imprimir ao usu�rio as sa�das
{
    FILE *file;
    //Abre o arquivo "funcion�rios.dat" para leitura
    file = fopen(file_name, "rb");
    //Verifica se a abertura foi bem sucedida
    if(!(file))
    {
        printf("Erro ao abrir arquivo.\n");
    }
    else
    {
        FILE *arq;
        //Abre o arquivo "atualizados.dat" para leitura
        arq = fopen(new_file, "rb");
        //Verifida se a abretura foi bem sucedida
        if(!(arq))
        {
            printf("Erro ao abrir arquivo.\n");
        }
        else
        {
            while(!(feof(file))) //Executa a leitura at� chegar ao final do arquivo "funcion�rios.dat"
            {
                if(fread(&(*func), sizeof(FUNCIONARIO), 1, file) == 1) //L� as inform��oes do arquivo "funcion�rios.dat"
                    if(fread(&(*novo), sizeof(NEW_WAGE), 1, arq) == 1) //L� as informa��es do arquivo "atualizados.dat"
                    {
                            //Imprime o nome, o sal�rio anterior e o novo sal�rio do funcion�rio
                            printf("Nome: %s", func->nome);
                            printf("Sal�rio anterior: R$%.2f\n", func->salario);
                            printf("Sal�rio atualizado: R$%.2f\n\n", novo->salario);
                    }
            }
            //Fecha ambos os arquivos
            fclose(arq);
            fclose(file);
        }
    }
}
