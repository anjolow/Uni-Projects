//Lucas Anjos da Silva
/*Este programa faz a simula��o de uma compra de mercado, onde o usu�rio informa os produtos que deseja comprar e a quantidade,
fornecendo ao final o valor a pagar. Ele pode executar mais de uma comrpa antes de finalizar e ent�o, ao final, quando o usu�rio
informa que n�o deseja realizar uma nova compra, ele imprime o resumo de todas as compras feitas durante a execu��o do programa.
    Entradas: op��o (nova compra ou sair), c�digo e quantidade do produto;
    Sa�das: total a pagar, total arrecadado do dia, quantidade de compras realizadas, m�dia do valor das comrpas.*/

#include <stdio.h>
#include <locale.h>

//Define os pre�os dos produtos como constantes
#define PAO 2.25
#define LEITE 7.65
#define BISCOITO 6.93
#define ARROZ 30.21
#define FEIJAO 12.33

int main(){

    setlocale(LC_CTYPE, "Portuguese");

    int opcao; //Vari�vel para selecionar a op��o desejada de execu��o (nova compra ou sair)
    int cod, quant; //Vari�veis para ler o c�digo de um produto e sua quantidade
    int compras=0; //Vari�vel que conta quantas compras foram realizadas
    float precos=0, total=0; //Vari�veis para trabalhar com os pre�os e total a pagar

    //Imprime a tabela de pre�os para o usu�rio
    printf("C�digo do Produto\tProduto\t\t\tValor unit�rio\n");
    printf("10\t\t\tP�o\t\t\tR$ 2.25\n");
    printf("23\t\t\tLeite (1L)\t\tR$ 7.65\n");
    printf("8\t\t\tBiscoito (pct 300g)\tR$ 6.93\n");
    printf("90\t\t\tArroz (pct 1kg)\t\tR$ 30.21\n");
    printf("76\t\t\tFeij�o (pct 1kg)\tR$ 12.33\n");
    printf("0\t\t\tFinalizar Compra\n");
    printf("\nO mercado oferece 2%% de desconto para compras acima de R$ 100.00\n");

    do //Inicia a repeti��o de compras, enquanto o usu�rio quiser faz�-las
    {
        printf("\nInforme a op��o (0-Sair 1-Nova compra): "); //Pergunta ao usu�rio se ele deseja realizar uma nova compra e recebe essa informa��o
        scanf("%d", &opcao);

        if(opcao == 1)
        {
            do
            {
                printf("Informe o c�digo do produto: "); //Pede ao usu�rio o c�digo do produto que deseja comprar
                scanf("%d", &cod);
                switch(cod){ //Analisa o c�digo que foi informado e agr confrome o solicitado.
                case 10:
                    do //Inicia uma repeti��o para caso o usu�rio informe uma quantidade de produto inv�lda, como 0 ou n�meros negativos
                    {
                        printf("Informe a quantidade do produto %d: ", cod); //Usu�rio informa a quantidade do produto
                        scanf("%d", &quant);
                        if(quant>0)
                            precos = precos + PAO*quant; //Acumula o valor da compra deste profuto na vari�vel de pre�os
                        else
                            printf("Quantidade inv�lida!\n");
                    } while(quant<=0);
                    break;
                case 23:
                    do
                    {
                        printf("Informe a quantidade do produto %d: ", cod);
                        scanf("%d", &quant);
                        if(quant>0)
                            precos = precos + LEITE*quant;
                        else
                            printf("Quantidade inv�lida!\n");
                    } while(quant<=0);
                    break;
                case 8:
                    do
                    {
                        printf("Informe a quantidade do produto %d: ", cod);
                        scanf("%d", &quant);
                        if(quant>0)
                            precos = precos + BISCOITO*quant;
                        else
                            printf("Quantidade inv�lida!\n");
                    } while(quant<=0);
                    break;
                case 90:
                    do
                    {
                        printf("Informe a quantidade do produto %d: ", cod);
                        scanf("%d", &quant);
                        if(quant>0)
                            precos = precos + ARROZ*quant;
                        else
                            printf("Quantidade inv�lida!\n");
                    } while(quant<=0);
                    break;
                case 76:
                    do
                    {
                        printf("Informe a quantidade do produto %d: ", cod);
                        scanf("%d", &quant);
                        if(quant>0)
                            precos = precos + FEIJAO*quant;
                        else
                            printf("Quantidade inv�lida!\n");
                    } while(quant<=0);
                    break;
                case 0: //Finaliza a compra
                    printf("Compra finalizada!");
                    printf("\nTotal: R$ %.2f\n", precos);
                    if(precos>100) //Caso o total desta comrpa for maior que 100, atribui o desconto e imprime isso ao usu�rio
                    {
                        printf("Total com desconto: R$ %.2f\n", precos*0.98);
                        total = total + precos*0.98; //Acumula o valor total da compra com desconto � vari�vel de valor total de todas as compras
                    }
                    else
                        total = total + precos; //Acumula o valor total da compra � vari�vel de valor total de todas as compras
                    break;
                default:
                    printf("C�digo inv�lido!\n");
                }
            }while(cod!=0);
        compras++; //Adiciona um � vari�vel que conta quantas compras foram feitas
        precos = 0; //Reinicia a vari�vel de pre�os para que possa ser realizada outra compra
        }
        else if(opcao!=0 && opcao!=1)
             printf("\nOp��o inv�lida!\n\n");

    } while(opcao!=0);

    //Imprime o resumo das informa��es de compras realizadas
    printf("\nCaixa fechado!\n");
    printf("Estat�sticas do dia:\n");
    printf("---Quantidade de compras realizadas: %d\n", compras);
    printf("---Total faturado do dia: R$ %.2f\n", total);
    if(compras>0)
        printf("---M�dia do valor das compras: R$ %.2f\n", total=total/compras);
    else
        printf("---M�dia do valor das compras: R$ 0.00");

    return 0;
}
