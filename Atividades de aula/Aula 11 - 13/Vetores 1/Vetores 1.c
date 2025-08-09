#include <stdio.h>
# define CODMAX 99
# define CODMIN 10

int main ()
{
    int cod;
    int achou; // flag que indica se achou codigo (vale 0 ou 1)
    float preco [CODMAX-CODMIN+1];
    float preco_buscado;
    //obter pre�os
    for (cod = 0; cod <=  CODMAX-CODMIN; cod++) {
        printf("Entre o preco da mercadoria com codigo %d:", CODMIN + cod);
        scanf("%f", &preco[cod] );
    }
    //Pede o valor buscado
    printf("Informe o valor buscado:\n");
    scanf("%f", &preco_buscado);

    achou = 0;
    cod = 0;
    do{
        if (preco[cod] == preco_buscado)
        achou = 1;
        else
        cod++;
    }while  (cod  <=  CODMAX - CODMIN && achou == 0);

    if (achou == 1)
        printf ("Codigo desejado: %d", cod + CODMIN);
    else
        printf("Codigo n�o encontrado!");

    return 0;
}
