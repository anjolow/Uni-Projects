//Lucas Anjos da Silva
/*Este programa realiza operações de depósito, saque e transferência entre contas, além de mostrar ao usuário o saldo da conta
desejada.
    Entradas: saldo das contas, operação que deseja realizar, código da conta, valores a serem operados;
    Saídas: saldo atual das contas pós operação.
*/

#include <stdio.h>
#include <locale.h>

#define QTD 3

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    int i, o, cod, conta, conta2, achou;
    float saldo[QTD], deposito, saque, transf, quantidade[QTD];

    for(i=0; i<QTD; i++)
    {
        printf("Informe o saldo da conta %d: ", i+1);
        scanf("%f", &saldo[i]);
    }

    for(i=0; i<QTD; i++)
    {
        quantidade[i]=i+1;
    }

    do
    {
        achou=0;
        o=0;
        printf("\nInforme a opção desejada (0-sair, 1-Saldo, 2-depósito, 3-Saque, 4-Transferência): ");
        scanf("%d", &cod);
        if(cod!=0)
        {
            printf("Informe o código da conta (de 1 à %d): ", QTD);
            scanf("%d", &conta);
            do
            {
                if (conta == quantidade[o])
                    achou = 1;
                else
                    o++;
            }while (o <= QTD && achou == 0);
        
            if(achou==1)
                switch(cod)
                {
                    case 1:
                        printf("O saldo atual da conta %d é de R$ %.2f\n", conta, saldo[conta-1]);
                        break;

                    case 2:
                        printf("Informe o valor de depósito: R$ ");
                        scanf("%f", &deposito);

                        if(deposito>0)
                        {
                            saldo[conta-1]=saldo[conta-1]+deposito;
                            printf("Opeação efetuada com sucesso!\n");
                            printf("Saldo atual da conta: R$ %.2f\n", saldo[conta-1]);
                        }
                        else
                            printf("Valor inválido.\n");
                        break;

                    case 3:
                        printf("Informe o valor a ser sacado: R$ ");
                        scanf("%f", &saque);
                        if(saldo[conta-1]>=saque)
                        {
                            saldo[conta-1] = saldo[conta-1] - saque;
                            printf("Opeação efetuada com sucesso!\n");
                            printf("Saldo atual da conta: R$ %.2f\n", saldo[conta-1]);
                        }
                        else
                            printf("Saldo insuficiente!\n");
                        break;

                    case 4:
                        printf("Informe o código da conta de destino (de 1 à %d): ", QTD);
                        scanf("%d", &conta2);
                        do
                        {
                            if (conta2 == quantidade[o])
                                achou = 1;
                            else
                                o++;
                        }while (o <= QTD && achou == 0);
                                
                        if(achou==1)
                        {
                            printf("Informe o valor a ser transferido: ");
                            scanf("%f", &transf);
                            if(transf<=0 || transf>saldo[conta-1])
                                printf("Saldo insuficiente para realizar a transação.");
                            else
                            {
                                saldo[conta2-1]=saldo[conta2-1]+transf;
                                saldo[conta-1]=saldo[conta-1]-transf;
                                printf("Opeação efetuada com sucesso!\n");
                                printf("Saldo atual da conta %d: R$ %.2f\n", conta, saldo[conta-1]);
                            }
                        }
                        else
                            printf("Código da conta inválido.\n");
                        break;
                
                    default:
                        printf("Código Inválido!");
                }
            else
                printf("Código da conta inválido.\n");
        }
    }while(cod!=0);

    printf("Sistema finalizado.\n");

    return 0;
}