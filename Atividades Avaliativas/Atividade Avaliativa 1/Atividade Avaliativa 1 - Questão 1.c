/*Lucas Anjos da Silva
Este programa calcula o valor da compra de um dos produtos dispon�veis,
com desconteo de 2% aplicado para compras acima de R$50.00
    Entradas: c�digo do produto; quantidade.
    Sa�da: valor a ser pago, com desconto (se for o caso)*/

#include <stdio.h>
#include <locale.h>

#define VP 1.50 //Constante valor do p�o (c�digo: 1)
#define VL 4.65 //Constante valor do leite (c�digo: 2)
#define VB 6.93 //Constante valor do biscoito (c�digo: 3)

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    float valor; //Vari�vel do valor a ser pago
    int quantidade; //Var��vel da quantidade do produto
    int codigo; //Vari�vel do c�digo do produto

    printf("C�digo do Produto: \t Produto: \t\t Valor Unit�rio:\n"); //Tabela de produtos para o usu�rio ter conhecimento das informa��es a serem fornecidas
    printf("1 \t\t\t P�o \t\t\t R$1.50\n");
    printf("2 \t\t\t Leite (1L) \t\t R$4.65\n");
    printf("3 \t\t\t Biscoito (pct 30g) \t R$6.93\n");
    printf("\nO mercado oferece dois por cento de desconto para compras acima de R$50,00.\n\n");

    printf("\nInforme o c�digo do produto: "); //Cliente informa o c�digo do produto desejado
    scanf("%d", &codigo);
    printf("\nInforme a quantidade desejada: "); //Cliente informa a quantidade de produto desejada
    scanf("%d", &quantidade);

    if(codigo == 1)
    {
        valor = VP*quantidade;
    }

    if(codigo == 2)
    {
        valor = VL*quantidade;
    }

    if(codigo == 3)
    {
        valor = VB*quantidade;
    }

    if(valor > 50)  //Programa calcula se h� desconto no valor final a ser pago
    {
        valor = valor - valor*0.02;
    }

    printf("\n\nValor a ser pago: R$%.2f \n", valor); //Imprime o valor a ser pago pelo cliente

    return 0;
}
