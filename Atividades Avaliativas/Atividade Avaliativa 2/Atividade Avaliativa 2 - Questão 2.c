/*Lucas Anjos da Silva
Este programa realiza uma entre tr�s opera��es banc�rias especificadas pelo usu�iro.
O saldo da conta � informado pelo usu�rio e n�o pode ficar negativo.
    Entradas: saldo atual, c�digo de opera��o, valor a ser operado e, caso for um transfer�ncia, n�mero da conta de destno.
    Sa�das: Saldo final da conta*/
#include <stdio.h>
#include <locale.h>


int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    float saldo, valor, saldo_final; //VAri�veis de saldo atual, valor a ser operado e salfo final
    int codigo, conta; //Vari�veis de c�digo e n�mero da conta


    printf("Informe o saldo atual da conta: R$"); //Sequ�ncia de entradas fornecidas pelo usu�rio
    scanf("%f", &saldo);
    printf("\n\n C�digos de Opera��o:\n1 - Dep�sito\t2 - Saque\t3 - Transfer�ncia");
    printf("\n\nInforme um c�digo de opera��o: ");
    scanf("%d", &codigo);
    if(codigo == 3){
        printf("\nInforme o n�mero da conta destino: ");
        scanf("%d", &conta);
    }
    printf("\nInforme o valor a ser operado: R$");
    scanf("%f", &valor);


    switch(codigo){ //An�lise do c�digo e realiza��o da opera��o desejada
        case 1:
            saldo_final = saldo + valor;
            printf("\nOpera��o realizada com sucesso!\nSaldo atual: R$%.2f\n", saldo_final);
            break;
        case 2:
            if(saldo < valor){
                printf("\nSaldo insuficiente para realizar a opera��o.\n");
            }
            else{
                saldo_final = saldo - valor;
                printf("\nOpera��o realizada com sucesso!\nSaldo atual: R$%.2f\n", saldo_final);
            }
            break;
        case 3:
            if(saldo < valor){
                printf("\nSaldo insuficiente para realizar a opera��o.\n");
            }
            else{
                saldo_final = saldo - valor;
                printf("\nOpera��o realizada com sucesso!\nSaldo atual: R$%.2f\n", saldo_final);
            }
            break;
    }

    return 0;
}
