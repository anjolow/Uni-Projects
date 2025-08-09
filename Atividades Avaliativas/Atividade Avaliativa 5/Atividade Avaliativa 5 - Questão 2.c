//Lucas Anjos da Silva
/*Este programa realiza opera��es de dep�sito, saque e transfer�ncia entre contas, al�m de mostrar ao usu�rio o saldo da conta
desejada.
    Entradas: saldo das contas, opera��o que deseja realizar, c�digo da conta, valores a serem operados;
    Sa�das: saldo atual das contas p�s opera��o.*/

#include <stdio.h>
#include <locale.h>

#define QTD 3 //Define um valor para a quantidade de contas

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    int i, o, p, cod, conta, conta2; //Vari�ves: "i" para utilizar no for; "o" e "p" para utilizar na verifica��o do c�digo da conta; "conta" e "conta2" para a leitura de qual das contas o usu�rio quer trabalhar
    float saldo[QTD], quantidade[QTD]; //Declara��o de arranjos para guardar o saldo e a quantidade de contas
    float deposito, saque, transf; //Vari�veis para realizar as opera��es

    for(i=0; i<QTD; i++)
    {
        printf("Informe o saldo da conta %d: ", i+1);
        scanf("%f", &saldo[i]);
    }

    for(i=0; i<QTD; i++)
    {
        quantidade[i]=i+1; //Atribui cada elemento do arranjo com o valor de i+1, i+2 ... i+n, com n sendo o valor de QTD
    }

    do //come�a o la�o de repeti��o
    {
        p=0;//Redefine o valor das vari�veis p e o para evitar erros nos c�lculos
        o=0;
        printf("\nInforme a op��o desejada (0-sair, 1-Saldo, 2-dep�sito, 3-Saque, 4-Transfer�ncia): "); //Solicita a opear��o a ser realizada
        scanf("%d", &cod);
        switch(cod) //Analisa o n�mero da opera��o e realiza a a��o descrita
        {
            case 0: break;
            case 1:
                printf("Informe o c�digo da conta (de 1 � %d): ", QTD); //Solicita o c�digo da conta, que varia de 1 ao m�ximo definido anteriormente
                scanf("%d", &conta);
                //Analisa o valor inserido para confirmar que est� dentro do intervalo desejado. Se n�o estiver, volta a pedir a opera��o banc�ria.
                //Faz isso para todos os casos
                do
                {
                    if (conta == quantidade[o])
                        p = 1;
                    else
                        o++;
                }while (o <= QTD && p == 0);
                if(p==1)
                    printf("O saldo atual da conta %d � de R$ %.2f\n", conta, saldo[conta-1]); //Imprime o saldo atual da conta ao usu�rio
                else
                    printf("C�digo da conta inv�lido.\n");
                break;

            case 2:
                printf("Informe o c�digo da conta (de 1 � %d): ", QTD);
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
                    printf("Informe o valor de dep�sito: R$ "); //Solicita o valor a ser depositado
                    scanf("%f", &deposito);

                    //Caso o valor inserido seja igual ou menor que zero, informa ao usu�rio que o valor � inv�lido e volta a pedir a opera��o banc�ria
                    if(deposito>0)
                    {
                    saldo[conta-1]=saldo[conta-1]+deposito;
                    printf("Opea��o efetuada com sucesso!\n");
                    printf("Saldo atual da conta: R$ %.2f\n", saldo[conta-1]);
                    }
                    else
                        printf("Valor inv�lido.\n");
                }
                else
                    printf("C�digo da conta inv�lido.\n");
                break;

            case 3:
                printf("Informe o c�digo da conta (de 1 � %d): ", QTD);
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


                    //Analisa se h� saldo suficiente na conta para realizar o saque. Caso n�o houver, informa isso ao usu�rio
                    if(saldo[conta-1]>=saque)
                    {
                        saldo[conta-1] = saldo[conta-1] - saque;
                        printf("Opea��o efetuada com sucesso!\n");
                        printf("Saldo atual da conta: R$ %.2f\n", saldo[conta-1]);
                    }
                    else
                        printf("Saldo insuficiente!\n");
                }
                else
                    printf("\nC�digo da conta inv�lido.\n");
                break;

            case 4:
               printf("Informe o c�digo da conta (de 1 � %d): ", QTD);
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
                    printf("Informe o c�digo da conta de destino (de 1 � %d): ", QTD); //Solicita o c�digo da conta de destino
                    scanf("%d", &conta2);
                    //Faz a mesma an�lise, varificando se o n�mero de conta inserido est� dentro do intervalo desejado
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
                        if(transf<=0 || transf>saldo[conta-1]) //Verifica se h� saldo o suficiente para realizar a transa��o. Se n�o houver, informa ao usu�rio. Verifica tamb�m se o valor inserido � maior que zero
                            printf("Saldo insuficiente para realizar a transa��o.");
                        else
                        {
                            saldo[conta2-1]=saldo[conta2-1]+transf;
                            saldo[conta-1]=saldo[conta-1]-transf;
                            printf("Opea��o efetuada com sucesso!\n");
                            printf("Saldo atual da conta %d: R$ %.2f\n", conta, saldo[conta-1]);
                        }
                    }
                    else
                        printf("C�digo da conta inv�lido.\n");
                }
                else
                    printf("C�digo da conta inv�lido.\n");
                break;
            default:
                printf("C�digo Inv�lido!\n");
        }
    }while(cod!=0); //Finaliza o programa quando o usu�rio informar 0 como valor da opera��o a ser realizada

    printf("Sistema finalizado.\n");

    return 0;
}
