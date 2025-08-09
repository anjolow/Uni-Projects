//Lucas Anjos da Silva
/*
Este programa adquire informações sobre funcionários de uma empresa e os grava em um arquivo denominado "funcionarios.dat"
    Entradas: nome e salário do funcionário.
    Saídas: lista de funcionários já adquiridos.
*/

/*
Curiosidade: fiquei 2h30min tentando descobrir porque o programa não estava funcionando, e era porque
eu estava escrevendo "&funcionario" ao invés de "&(*funcionario)" na funções de fread e fwrite.
*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Definição da estrutura para aquisição do nome e do salário de um funcionário
typedef struct funcionario
{
    char nome[80];
    float salario;
}FUNCIONARIO;

//Declaração do protótipo das funções
int le_funcionario(FUNCIONARIO *funcionario, char file_name[]);
void mostra_lista(FUNCIONARIO *funcionario, char file_name[]);

int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    FILE *file; //Declaração do ponteiro para manipulação de arquivo
    FUNCIONARIO funcionario; //Declaração da estrutura de funcionário
    char file_name[]={"funcionarios.dat"}; //Declaração do nome do arquivo, para mudança mais rápida caso se deseje
    int op, end=0, erro; //Variáveis para manipulação da execução atual do programa e verificação de erros em funções

    printf("-----ARMEZENE INFORMAÇÕES DE FUNCIONÁRIOS EM UM ARQUIVO-----\n");

    while(end!=1) //Início do laço de repetição para execução do programa enquanto o usuário desejar
    {
        printf("\n");
        printf("Incluir novo funcionário (1), mostrar funcionários (2) ou sair (3)? "); //Imprime as opções de ações ao usuário
        scanf("%d", &op); //Adquire a opção
        switch(op)
        {
            case 1: //Opção para registrar um novo funcioário
                erro = le_funcionario(&funcionario, file_name); //Chama a função para ler o funcionário e atribui ela à variável de erro para verificar se haverá algum
                if(erro==1) //Caso a função retorne 1, significa que não houve nenhum erro em sua execução
                {
                    break;
                }
                else if(erro==2) //Caso a função retorne 2, significa que houve erro ao abrir o arquivo
                {
                    printf("Erro na abertura do arquivo.\n");
                    break;
                }
                else //Caso a função retorne 0, significa que houve erro ao gravar as informações do funcionário
                {
                    printf("Ocorreu um erro ao salvar as informacoes do funcionario.\n");
                    break;
                }
            case 2: //Opção para mostrar a lista de funcionários já existente
                mostra_lista(&funcionario, file_name); //Chama a função que executa esta ação
                break;
            case 3: //Opção para finalizar o programa
                end = 1; //Atribui a variável de controle como 1 para finalizar o programa
                break;
            default: //Caso o usuário digite qualquer outro número sem ser 1, 2 ou 3, o programa informa que a opção não existe
                printf("Opção não existe.\n");
        }
    }

    printf("\nSistema finalizado.\n"); //Imprime que o programa foi finalizado

    return 0;
}

int le_funcionario(FUNCIONARIO *funcionario, char file_name[]) //Função que lê as informações de um funcionário
{
    FILE *file;
    //Abre o arquivo "funcionarios.dat" para escrita ao final dele, caso já exista um. Se não, cria um arquivo novo com este nome
    file = fopen(file_name, "ab");
    //Verifica se houve erro na abertura
    if(!(file))
    {
        return 2;
    }
    else
    {
        //Adquire o nome do funcionário
        printf("Informe o nome: ");
        getchar();
        do
        {
            fgets(funcionario->nome, 80, stdin);
            if(strlen(funcionario->nome)==1 || funcionario->nome[0] == 32) //Caso o nome for deixado em branco, pede ao usuário que informe novamente
                printf("Nome inválido! Não dê espaço antes de inrerir o nome e não deixe ele em branco.\nInforme novamente: ");
        }while(strlen(funcionario->nome)==1 || funcionario->nome[0] == 32);

        //Adquire o salário do funcionário
        printf("Informe o salário: R$ ");
        do
        {
            scanf("%f", &funcionario->salario);
            if(funcionario->salario<=0) //Caso o salário inserido for 0 ou negativo, pede ao usuário que informe novamente
                printf("Salário inválido!\nInforme novamente: R$");
        }while(funcionario->salario<=0);

        //Escreve as informações adquiridas no arquivo "funcionarios.dat"
        if(fwrite(&(*funcionario), sizeof(FUNCIONARIO), 1, file)!=1)
        {
            //Caso ocorra erro na escrita, fecha o arquivo e retorna 0
            fclose(file);
            return 0;
        }
        //Se der tudo certo, fecha o arquivo e retorna 1
        fclose(file);
        return 1;
    }
}

void mostra_lista(FUNCIONARIO *funcionario, char file_name[]) //Função que imprime ao usuário a lista de funcionários registrados
{
    FILE *file;
    //Abre o arquivo "funcionarios.dat" para leitura
    file = fopen(file_name, "rb");
    //Verifica se houve erro na abertura
    if(!(file))
    {
        //Se houver, informa ao usuário
        printf("Erro ao abrir arquivo.");
    }
    else
    {
        //Executa ações até encontrar o final do arquivo
        while(!(feof(file)))
        {
            //Lê as informações registradas no arquivo
            if(fread(&(*funcionario), sizeof(FUNCIONARIO), 1, file) == 1)
            {
                //Imprime ao usuário as informações dos funcionários já registrados
                printf("Nome: %s", funcionario->nome);
                printf("Salário: R$ %.2f\n\n", funcionario->salario);
            }
        }
        //Fecha o arquivo
        fclose(file);
    }
}
