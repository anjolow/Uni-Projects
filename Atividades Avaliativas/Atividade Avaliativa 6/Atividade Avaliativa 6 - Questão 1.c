//Lucas Anjos da Silva
/*Este programa auxilia um mercado a analisar as vendas das filiais (F) para cada produto (P) do mercado ao final de um m�s.
    Entradas: nome, c�digo, pre�o e vendas para cada filial de cada produto;
    Sa�das: M�dias de unidades vendidas de cada produto por filial, Faturamento total de cada filial,
            Produto que gerou o maior faturamento.*/

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define PRODUTOS 3
#define TAM_PRDT 50
#define FILIAIS 3

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    char nome_prdt[PRODUTOS][TAM_PRDT+1], ler_prdt[TAM_PRDT+1]; //Matrizes para ler o nome dos produtos
    float tabela_prdt[PRODUTOS][2+FILIAIS]; //Matriz para guardar as informa��es dos produtos
    float media[PRODUTOS], acu_media=0; //Arranjo e vari�vel para o calculo da média de unidades vendidas por filial
    float faturamento[FILIAIS], fatu_prdt[PRODUTOS], maior; //Arranjos para o calculo do faturamento
    int cod, unidades=0; //Variáveis auxiliares para cálculos
    int p, f, i; //Variáveis auxiliares para usar no for
    int l=0; //Variáveis para verificação de validade de repetição

    //Pede a informa��o dos produtos ao usu�rio
    for(p=0; p<PRODUTOS; p++)
    {
        printf("Informe o nome do produto %d: ", p+1);
        fgets(nome_prdt[p],(TAM_PRDT-1),stdin);
        nome_prdt[p][strcspn(nome_prdt[p], "\n")] = 0;
        printf("Informe o c�digo do produto %d: ", p+1);
        scanf("%f", &tabela_prdt[p][0]);
        printf("Informe o pre�o do produto %d: ", p+1);
        scanf("%f", &tabela_prdt[p][1]);
        for(f=0; f<FILIAIS; f++)
        {
            printf("Informe a quantidade do produto %d vendida na filial %d no m�s: ", p+1, f+1);
            scanf("%f", &tabela_prdt[p][f+2]);
        }
        getchar();
        printf("\n");
    }

    printf("\n");

    //Imprime a informa��o dos produtos ao usu�rio em forma de tabela
    printf("Nome\t\t\t\t\t\tC�digo\t\tPre�o\t\t\t");
    for(f=1; f<=FILIAIS; f++)
    {
        printf("Qtd Filial %d\t\t", f);
    }

    for(i=0; i<PRODUTOS; i++)
    {
        printf("\n");
        printf("%*s", -TAM_PRDT, nome_prdt[i]);
        printf("%.0f\t\t%.2f\t\t\t", tabela_prdt[i][0], tabela_prdt[i][1]);
        for(f=2; f<(2+FILIAIS); f++)
        {
            printf("%.0f\t\t\t", tabela_prdt[i][f]);
        }
    }

    printf("\n\n");

    //Pede ao usu�rio informar o nome de um produto e mostra o c�digo e o pre�o desse produto
    do //Verifica��o de validade do nome inserido
    {
        printf("Informe o nome de um produto: ");
        gets(ler_prdt);
        for(i=0; i<PRODUTOS; i++)
        {
            if(strcmp(ler_prdt, nome_prdt[i]) == 0)
                l++;
        }
        if(l<=0)
            printf("Nome do produto inv�lido!\n");
    }while(l<=0);

    for(i=0; i<PRODUTOS; i++)
    {
        if(strcmp(ler_prdt, nome_prdt[i]) == 0)
        {
            printf("C�digo do produto: %.0f\tPre�o: %0.2f", tabela_prdt[i][0], tabela_prdt[i][1]);
        }
    }

    printf("\n\n");
    l=0; //Atribui��o da vari�vel l como 0 para poder us�-la novamente para a verifica��o de validade de repeti��o

    //Pede ao usu�rio para informar o c�digo de um produto e informa quantas unidades desse produto foram vendidas no total
    do //Verifica��o de validade do c�digo inserido
    {
        printf("Informe o c�digo de um produto: ");
        scanf("%d", &cod);
        for(p=0; p<PRODUTOS; p++)
        {
            if(cod==tabela_prdt[p][0])
                l++;
        }
        if(l<=0)
            printf("C�digo do produto inv�lido!\n");
    }while(l<=0);

    for(p=0; p<PRODUTOS; p++)
    {
        if(cod == tabela_prdt[p][0])
        {
            for(f=0; f<FILIAIS; f++)
            {
                unidades = unidades + tabela_prdt[p][f+2];
            }
            printf("%s: Foram vendidas %d unidades no total\n\n", nome_prdt[p], unidades);
            unidades=0;
        }
    }

    printf("\n\n");

    //Calcula a m�dia de unidades vendidas de cada produto por filial e imprime isso ao usu�rio
    printf("M�dia de unidades vendidas de cada produto por filial:");
    for(i=0; i<PRODUTOS; i++)
    {
        printf("\n");
        printf("%*s", -TAM_PRDT, nome_prdt[i]);
        printf("C�digo: %.0f\t\tPre�o %.2f\t\t", tabela_prdt[i][0], tabela_prdt[i][1]);
        for(f=0; f<FILIAIS; f++)
        {
            acu_media += tabela_prdt[i][f+2];
        }
        media[i] = acu_media/f;
        printf("M�dia: %.2f", media[i]);
        acu_media=0;
    }

    printf("\n\n\n");

    //Calcula e imprime o faturamento total de cada Filial
    printf("Faturamento total de cada Filial:\n");
    for(f=0; f<FILIAIS; f++)
    {
        for(p=0; p<PRODUTOS; p++)
        {
            faturamento[f] += tabela_prdt[p][1] * tabela_prdt[p][f+2];
        }
    }

    for(f=0; f<FILIAIS; f++)
    {
        printf("Filial %d: R$ %.2f\n", f+1, faturamento[f]);
    }

    printf("\n\n");

    //Calcula e imprime o produto que gerou o maior faturamento
    printf("Produto que gerou o maior faturamento:\n");
    for(p=0; p<PRODUTOS; p++)
    {
        for(f=0; f<FILIAIS; f++)
            fatu_prdt[p] += tabela_prdt[p][1] * tabela_prdt[p][f+2];
    }

    fatu_prdt[0] = maior;
    for(p=1; p<PRODUTOS; p++)
    {
        if(fatu_prdt[p]>maior)
        {
            maior=fatu_prdt[p];
            l=p;
        }
    }

    for(p=0; p<PRODUTOS; p++)
    {
        if(fatu_prdt[p]==maior)
            printf("%s:\tC�digo: %.0f\tFaturamento: R$ %.2f\n", nome_prdt[p], tabela_prdt[p][0],fatu_prdt[p]);
    }


    printf("\n");
    return 0;
}
