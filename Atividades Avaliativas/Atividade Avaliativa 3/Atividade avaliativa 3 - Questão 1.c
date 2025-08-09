/*Lucas Anjos da Silva
Este programa lê certa quantidade de itens que o usuário pode ler em uma tabela e calcula quanto que o usuário irá
pagar ao final da compra do tipo de produto e quantidade que ele quer. O programa também calcula um desconto de 2%
caso o total dê maior que 100 reais.

    Entradas: quantidade de itens, código do protudo, quantidade de produto;
    Saídas: total a pagar, total a pagar com desconto.*/

#include <stdio.h>
#include <locale.h>

//Define os preços dos produtos como constantes
#define PAO 2.25
#define LEITE 7.65
#define BISCOITO 6.93
#define ARROZ 30.21
#define FEIJAO 12.33

int main(){

    setlocale(LC_CTYPE, "Portuguese");

    int qtd_itens, i; //Define as variáveis de quantidade de itens e índice para usar na repetição
    int cod, quant; //Define as variáveis de código de produto e quantidade
    float precos; //Define a variável acumuladora/contadora
    float total; //Define a variável de total a pagar

    //Imprime a tabela de preços para o usuário
    printf("Código do Produto\tProduto\t\t\tValor unitário\n");
    printf("10\t\t\tPão\t\t\tR$ 2.25\n");
    printf("23\t\t\tLeite (1L)\t\tR$ 7.65\n");
    printf("8\t\t\tBiscoito (pct 300g)\tR$ 6.93\n");
    printf("90\t\t\tArroz (pct 1kg)\t\tR$ 30.21\n");
    printf("76\t\t\tFeijão (pct 1kg)\tR$ 12.33\n");
    printf("\nO mercado oferece 2%% de desconto para compras acima de R$ 100.00\n\n");

    printf("Informe a quantidade de itens que você deseja comprar: "); //Usuário informa a quantidade de itens que quer comprar
    scanf("%d", &qtd_itens);

    precos = 0; //Atribui a variável contadora como 0, para iniciar a contagem

    for(i = 1; i <= qtd_itens; i++) //Inicia a repetição, onde pede o código do produto para o usuário e a quantidade de produtos daquele tipo e atribui valor à variável acumuladora conforme o informado
    {
        printf("\nInforme o código do item %d: ", i);
        scanf("%d", &cod);
        switch(cod){
        case 10:
            printf("Informe a quantidade do item %d: ", i);
            scanf("%d", &quant);
            precos = precos + PAO*quant;
            break;
        case 23:
            printf("Informe a quantidade do item %d: ", i);
            scanf("%d", &quant);
            precos = precos + LEITE*quant;
            break;
        case 8:
            printf("Informe a quantidade do item %d: ", i);
            scanf("%d", &quant);
            precos = precos + BISCOITO*quant;
            break;
        case 90:
            printf("Informe a quantidade do item %d: ", i);
            scanf("%d", &quant);
            precos = precos + ARROZ*quant;
            break;
        case 76:
            printf("Informe a quantidade do item %d: ", i);
            scanf("%d", &quant);
            precos = precos + FEIJAO*quant;
            break;
        default:
            printf("\nCódigo inválido!\n\n");
        }
    }

    total = precos;
    printf("\n\nTotal: R$ %.2f\n", total); //Imprime o total a pagar
    if(total>100)
        printf("Total com desconto: R$ %.2f\n", total*0.98); //Imprime o total a pagar caso o valor a pagar seja maior que 100 reais

    return 0;
}
