//Lucas Anjos da Silva
/*
Este programa adquire informa��es sobre funcion�rios de uma empresa e os grava em um arquivo denominado "funcionarios.dat"
    Entradas: nome e sal�rio do funcion�rio.
    Sa�das: lista de funcion�rios j� adquiridos.
*/

/*
Curiosidade: fiquei 2h30min tentando descobrir porque o programa n�o estava funcionando, e era porque
eu estava escrevendo "&funcionario" ao inv�s de "&(*funcionario)" na fun��es de fread e fwrite.
*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//Defini��o da estrutura para aquisi��o do nome e do sal�rio de um funcion�rio
typedef struct funcionario
{
    char nome[80];
    float salario;
}FUNCIONARIO;

//Declara��o do prot�tipo das fun��es
int le_funcionario(FUNCIONARIO *funcionario, char file_name[]);
void mostra_lista(FUNCIONARIO *funcionario, char file_name[]);

int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    FILE *file; //Declara��o do ponteiro para manipula��o de arquivo
    FUNCIONARIO funcionario; //Declara��o da estrutura de funcion�rio
    char file_name[]={"funcionarios.dat"}; //Declara��o do nome do arquivo, para mudan�a mais r�pida caso se deseje
    int op, end=0, erro; //Vari�veis para manipula��o da execu��o atual do programa e verifica��o de erros em fun��es

    printf("-----ARMEZENE INFORMA��ES DE FUNCION�RIOS EM UM ARQUIVO-----\n");

    while(end!=1) //In�cio do la�o de repeti��o para execu��o do programa enquanto o usu�rio desejar
    {
        printf("\n");
        printf("Incluir novo funcion�rio (1), mostrar funcion�rios (2) ou sair (3)? "); //Imprime as op��es de a��es ao usu�rio
        scanf("%d", &op); //Adquire a op��o
        switch(op)
        {
            case 1: //Op��o para registrar um novo funcio�rio
                erro = le_funcionario(&funcionario, file_name); //Chama a fun��o para ler o funcion�rio e atribui ela � vari�vel de erro para verificar se haver� algum
                if(erro==1) //Caso a fun��o retorne 1, significa que n�o houve nenhum erro em sua execu��o
                {
                    break;
                }
                else if(erro==2) //Caso a fun��o retorne 2, significa que houve erro ao abrir o arquivo
                {
                    printf("Erro na abertura do arquivo.\n");
                    break;
                }
                else //Caso a fun��o retorne 0, significa que houve erro ao gravar as informa��es do funcion�rio
                {
                    printf("Ocorreu um erro ao salvar as informacoes do funcionario.\n");
                    break;
                }
            case 2: //Op��o para mostrar a lista de funcion�rios j� existente
                mostra_lista(&funcionario, file_name); //Chama a fun��o que executa esta a��o
                break;
            case 3: //Op��o para finalizar o programa
                end = 1; //Atribui a vari�vel de controle como 1 para finalizar o programa
                break;
            default: //Caso o usu�rio digite qualquer outro n�mero sem ser 1, 2 ou 3, o programa informa que a op��o n�o existe
                printf("Op��o n�o existe.\n");
        }
    }

    printf("\nSistema finalizado.\n"); //Imprime que o programa foi finalizado

    return 0;
}

int le_funcionario(FUNCIONARIO *funcionario, char file_name[]) //Fun��o que l� as informa��es de um funcion�rio
{
    FILE *file;
    //Abre o arquivo "funcionarios.dat" para escrita ao final dele, caso j� exista um. Se n�o, cria um arquivo novo com este nome
    file = fopen(file_name, "ab");
    //Verifica se houve erro na abertura
    if(!(file))
    {
        return 2;
    }
    else
    {
        //Adquire o nome do funcion�rio
        printf("Informe o nome: ");
        getchar();
        do
        {
            fgets(funcionario->nome, 80, stdin);
            if(strlen(funcionario->nome)==1 || funcionario->nome[0] == 32) //Caso o nome for deixado em branco, pede ao usu�rio que informe novamente
                printf("Nome inv�lido! N�o d� espa�o antes de inrerir o nome e n�o deixe ele em branco.\nInforme novamente: ");
        }while(strlen(funcionario->nome)==1 || funcionario->nome[0] == 32);

        //Adquire o sal�rio do funcion�rio
        printf("Informe o sal�rio: R$ ");
        do
        {
            scanf("%f", &funcionario->salario);
            if(funcionario->salario<=0) //Caso o sal�rio inserido for 0 ou negativo, pede ao usu�rio que informe novamente
                printf("Sal�rio inv�lido!\nInforme novamente: R$");
        }while(funcionario->salario<=0);

        //Escreve as informa��es adquiridas no arquivo "funcionarios.dat"
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

void mostra_lista(FUNCIONARIO *funcionario, char file_name[]) //Fun��o que imprime ao usu�rio a lista de funcion�rios registrados
{
    FILE *file;
    //Abre o arquivo "funcionarios.dat" para leitura
    file = fopen(file_name, "rb");
    //Verifica se houve erro na abertura
    if(!(file))
    {
        //Se houver, informa ao usu�rio
        printf("Erro ao abrir arquivo.");
    }
    else
    {
        //Executa a��es at� encontrar o final do arquivo
        while(!(feof(file)))
        {
            //L� as informa��es registradas no arquivo
            if(fread(&(*funcionario), sizeof(FUNCIONARIO), 1, file) == 1)
            {
                //Imprime ao usu�rio as informa��es dos funcion�rios j� registrados
                printf("Nome: %s", funcionario->nome);
                printf("Sal�rio: R$ %.2f\n\n", funcionario->salario);
            }
        }
        //Fecha o arquivo
        fclose(file);
    }
}
