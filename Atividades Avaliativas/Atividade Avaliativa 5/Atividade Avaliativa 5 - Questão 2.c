//Lucas Anjos da Silva
/*Este programa realiza operações de depósito, saque e transferência entre contas, além de mostrar ao usuário o saldo da conta
desejada.
    Entradas: saldo das contas, operação que deseja realizar, código da conta, valores a serem operados;
    Saídas: saldo atual das contas pós operação.*/

#include <stdio.h>
#include <locale.h>

#define QTD 3 //Define um valor para a quantidade de contas

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    int i, o, p, cod, conta, conta2; //Variáves: "i" para utilizar no for; "o" e "p" para utilizar na verificação do código da conta; "conta" e "conta2" para a leitura de qual das contas o usuário quer trabalhar
    float saldo[QTD], quantidade[QTD]; //Declaração de arranjos para guardar o saldo e a quantidade de contas
    float deposito, saque, transf; //Variáveis para realizar as operações

    for(i=0; i<QTD; i++)
    {
        printf("Informe o saldo da conta %d: ", i+1);
        scanf("%f", &saldo[i]);
    }

    for(i=0; i<QTD; i++)
    {
        quantidade[i]=i+1; //Atribui cada elemento do arranjo com o valor de i+1, i+2 ... i+n, com n sendo o valor de QTD
    }

    do //começa o laço de repetição
    {
        p=0;//Redefine o valor das variáveis p e o para evitar erros nos cálculos
        o=0;
        printf("\nInforme a opção desejada (0-sair, 1-Saldo, 2-depósito, 3-Saque, 4-Transferência): "); //Solicita a opearção a ser realizada
        scanf("%d", &cod);
        switch(cod) //Analisa o número da operação e realiza a ação descrita
        {
            case 0: break;
            case 1:
                printf("Informe o código da conta (de 1 à %d): ", QTD); //Solicita o código da conta, que varia de 1 ao máximo definido anteriormente
                scanf("%d", &conta);
                //Analisa o valor inserido para confirmar que está dentro do intervalo desejado. Se não estiver, volta a pedir a operação bancária.
                //Faz isso para todos os casos
                do
                {
                    if (conta == quantidade[o])
                        p = 1;
                    else
                        o++;
                }while (o <= QTD && p == 0);
                if(p==1)
                    printf("O saldo atual da conta %d é de R$ %.2f\n", conta, saldo[conta-1]); //Imprime o saldo atual da conta ao usuário
                else
                    printf("Código da conta inválido.\n");
                break;

            case 2:
                printf("Informe o código da conta (de 1 à %d): ", QTD);
                scanf("%d", &conta);
                do
                {
                    if (conta == quantidade[o])
                        p = 1;
                    else
                        o++;
                }while (o <= QTD && p == 0);
                if(p==1)
                {
                    printf("Informe o valor de depósito: R$ "); //Solicita o valor a ser depositado
                    scanf("%f", &deposito);

                    //Caso o valor inserido seja igual ou menor que zero, informa ao usuário que o valor é inválido e volta a pedir a operação bancária
                    if(deposito>0)
                    {
                    saldo[conta-1]=saldo[conta-1]+deposito;
                    printf("Opeação efetuada com sucesso!\n");
                    printf("Saldo atual da conta: R$ %.2f\n", saldo[conta-1]);
                    }
                    else
                        printf("Valor inválido.\n");
                }
                else
                    printf("Código da conta inválido.\n");
                break;

            case 3:
                printf("Informe o código da conta (de 1 à %d): ", QTD);
                scanf("%d", &conta);
                do
                {
                    if (conta == quantidade[o])
                        p = 1;
                    else
                        o++;
                }while (o <= QTD && p == 0);
                if(p==1)
                {
                    printf("Informe o valor a ser sacado: R$ "); //Solicita o valor a ser sacado
                    scanf("%f", &saque);


                    //Analisa se há saldo suficiente na conta para realizar o saque. Caso não houver, informa isso ao usuário
                    if(saldo[conta-1]>=saque)
                    {
                        saldo[conta-1] = saldo[conta-1] - saque;
                        printf("Opeação efetuada com sucesso!\n");
                        printf("Saldo atual da conta: R$ %.2f\n", saldo[conta-1]);
                    }
                    else
                        printf("Saldo insuficiente!\n");
                }
                else
                    printf("\nCódigo da conta inválido.\n");
                break;

            case 4:
               printf("Informe o código da conta (de 1 à %d): ", QTD);
                scanf("%d", &conta);
                do
                {
                    if (conta == quantidade[o])
                        p = 1;
                    else
                        o++;
                }while (o <= QTD && p == 0);
                if(p==1)
                {
                    printf("Informe o código da conta de destino (de 1 à %d): ", QTD); //Solicita o código da conta de destino
                    scanf("%d", &conta2);
                    //Faz a mesma análise, varificando se o número de conta inserido está dentro do intervalo desejado
                    do
                    {
                        if (conta2 == quantidade[o])
                            p = 1;
                        else
                            o++;
                    }while (o <= QTD && p == 0);
                    if(p==1)
                    {
                        printf("Informe o valor a ser transferido: "); //Solicita o valor a ser transferido
                        scanf("%f", &transf);
                        if(transf<=0 || transf>saldo[conta-1]) //Verifica se há saldo o suficiente para realizar a transação. Se não houver, informa ao usuário. Verifica também se o valor inserido é maior que zero
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
                }
                else
                    printf("Código da conta inválido.\n");
                break;
            default:
                printf("Código Inválido!\n");
        }
    }while(cod!=0); //Finaliza o programa quando o usuário informar 0 como valor da operação a ser realizada

    printf("Sistema finalizado.\n");

    return 0;
}
