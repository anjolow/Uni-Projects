/*Lucas Anjos da Silva
Este programa realiza uma entre três operações bancárias especificadas pelo usuáiro.
O saldo da conta é informado pelo usuário e não pode ficar negativo.
    Entradas: saldo atual, código de operação, valor a ser operado e, caso for um transferência, número da conta de destno.
    Saídas: Saldo final da conta*/
#include <stdio.h>
#include <locale.h>


int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    float saldo, valor, saldo_final; //VAriáveis de saldo atual, valor a ser operado e salfo final
    int codigo, conta; //Variáveis de código e número da conta


    printf("Informe o saldo atual da conta: R$"); //Sequência de entradas fornecidas pelo usuário
    scanf("%f", &saldo);
    printf("\n\n Códigos de Operação:\n1 - Depósito\t2 - Saque\t3 - Transferência");
    printf("\n\nInforme um código de operação: ");
    scanf("%d", &codigo);
    if(codigo == 3){
        printf("\nInforme o número da conta destino: ");
        scanf("%d", &conta);
    }
    printf("\nInforme o valor a ser operado: R$");
    scanf("%f", &valor);


    switch(codigo){ //Análise do código e realização da operação desejada
        case 1:
            saldo_final = saldo + valor;
            printf("\nOperação realizada com sucesso!\nSaldo atual: R$%.2f\n", saldo_final);
            break;
        case 2:
            if(saldo < valor){
                printf("\nSaldo insuficiente para realizar a operação.\n");
            }
            else{
                saldo_final = saldo - valor;
                printf("\nOperação realizada com sucesso!\nSaldo atual: R$%.2f\n", saldo_final);
            }
            break;
        case 3:
            if(saldo < valor){
                printf("\nSaldo insuficiente para realizar a operação.\n");
            }
            else{
                saldo_final = saldo - valor;
                printf("\nOperação realizada com sucesso!\nSaldo atual: R$%.2f\n", saldo_final);
            }
            break;
    }

    return 0;
}
