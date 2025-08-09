//Lucas Anjos da Silva
/*
Este programa adquire um percentual para aumento salarial e informa qual o salário antigo e novo dos funcionários registrados.
    Entradas: percentual.
    Saídas: nome, salário antigo e salário aqualizado de todos os funcionários.
*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Estrutura do funcionário (mesma utilizada no programa anterior
typedef struct funcionario
{
    char nome[80];
    float salario;
}FUNCIONARIO;

//Estrutura para o registro do novo salário
typedef struct novo
{
    float salario;
}NEW_WAGE;

//Protótipos das funções
void atualiza(FUNCIONARIO *func, float percentual, char file_name[], NEW_WAGE *novo, char new_file[]);
void escreve(NEW_WAGE *novo, char new_file[]);
void mostra_lista(FUNCIONARIO *func, char file_name[], NEW_WAGE *novo, char new_file[]);

//Programa principal
int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    float percentual; //Variável para adrquirir o percentual
    FUNCIONARIO func; //Declaração da estrutura de funcionário
    NEW_WAGE novo; //Declaração da estrutura de novo salário
    char file_name[]={"funcionarios.dat"}; //Atribuição de nome do arquivo gerado pelo programa anterior (se for mudado no programa anterior, deve conter o mesmo nome neste programa)
    char new_file[]={"atualizados.dat"}; //Atribuição de nome do novo arquivo gerado por este programa, para mudança mais rápida caso se deseje

    //Adquire o percentual desejado
    printf("Informe o percentual de aumento salarial: ");
    scanf("%f", &percentual);

    //Chamada da função para atualizar o salário dos funcionários
    atualiza(&func, percentual, file_name, &novo, new_file);

    //Impressão das saídas
    printf("\nFuncionários:\n\n");
    mostra_lista(&func, file_name, &novo, new_file);

    return 0;
}

void atualiza(FUNCIONARIO *func, float percentual, char file_name[], NEW_WAGE *novo, char new_file[]) //Função que atualiza o salário dos funcionários
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
        {   //Executa a leitura do arquivo até o seu final
            if(fread(&(*func), sizeof(FUNCIONARIO), 1, file) == 1)
            {
                novo->salario = func->salario*(1+(percentual/100)); //Calcula o novo salário e atribui à estrutura que contém essa informação
                escreve(&(*novo), new_file); //Chamada da função para escrever o que foi calculado em um arquivo novo
            }
        }
        fclose(file); //Fecha o arquivo que estava lendo os salários
    }
}

void escreve(NEW_WAGE *novo, char new_file[]) //Função para gravar o salário atualizado em um novo arquivo
{
    FILE *file;
    //Abre o arquivo "atualizados.dat" para escrita, mantendo as informações já contidas nele.
    file = fopen(new_file, "ab");
    //Verifica se houve erro na abertura
    if(!(file))
    {
        printf("Erro ao abrir arquivo.");
    }
    else
    {
        if(fwrite(&(*novo), sizeof(NEW_WAGE), 1, file)!=1) //Escreve a informação do novo salário no arquivo
            printf("Erro na escrita.\n");

        fclose(file); //Fecha o arquivo
    }
}

void mostra_lista(FUNCIONARIO *func, char file_name[], NEW_WAGE *novo, char new_file[]) //Função para imprimir ao usuário as saídas
{
    FILE *file;
    //Abre o arquivo "funcionários.dat" para leitura
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
            while(!(feof(file))) //Executa a leitura até chegar ao final do arquivo "funcionários.dat"
            {
                if(fread(&(*func), sizeof(FUNCIONARIO), 1, file) == 1) //Lê as informçãoes do arquivo "funcionários.dat"
                    if(fread(&(*novo), sizeof(NEW_WAGE), 1, arq) == 1) //Lê as informações do arquivo "atualizados.dat"
                    {
                            //Imprime o nome, o salário anterior e o novo salário do funcionário
                            printf("Nome: %s", func->nome);
                            printf("Salário anterior: R$%.2f\n", func->salario);
                            printf("Salário atualizado: R$%.2f\n\n", novo->salario);
                    }
            }
            //Fecha ambos os arquivos
            fclose(arq);
            fclose(file);
        }
    }
}
