/*Lucas Anjos da Silva
Este programa adquire 3 c�digos de munic�pios, suas popula��es, uma popula��o de refer�ncia, calcula
a m�dia das popula��es e verifica se a popula��o do munic�pio � maior ou menor que a m�dia, informando isso ao usu�rio.
    Entradas: c�digos dos munic�pios, popula��o dos munic�pios, popula��o de refer�ncia.
    Sa�das: m�dia das popul��es, popula��o do munic�pio � maior ou menor que a m�dia*/

#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    int cod1, cod2, cod3; //Vari�veis dos c�digos
    int pop1, pop2, pop3; //Vari�veis das popula��es
    int ref; //Vari�vel da refer�ncia
    float media; //Vari�vel da m�dia

    printf("\nInforme os c�digos de 3 munic�pios: "); //Aqui o programa pede ao usu�rio as entradas
    scanf("%d %d %d", &cod1, &cod2, &cod3);
    printf("\nInforme a popula��o do munic�pio %d: ", cod1);
    scanf("%d", &pop1);
    printf("Informe a popula��o do munic�pio %d: ", cod2);
    scanf("%d", &pop2);
    printf("Informe a popula��o do munic�pio %d: ", cod3);
    scanf("%d", &pop3);
    printf("\nInforme o valor refer�ncia de popula��o: ");
    scanf("%d", &ref);


    media = (pop1+pop2+pop3)/3.0; //C�lculo da m�dia

    printf("\n\nA m�dia das poopula��es dos 3 munic�pios �: %.2f", media); //Programa informa a m�dia ao usu�rio


    if (pop1 <= media)
        printf("\n\nO munic�pio %d tem popula��o menor ou igual � m�dia", cod1);
        else printf("\nO munic�pio %d tem popula��o maior que m�dia", cod1);
    if (pop2 <= media)
        printf("\nO munic�pio %d tem popula��o menor ou igual � m�dia", cod2);
        else printf("\nO munic�pio %d tem popula��o maior que m�dia", cod2);
    if (pop3 <= media)
        printf("\nO munic�pio %d tem popula��o menor ou igual � m�dia", cod3);
        else printf("\nO munic�pio %d tem popula��o maior que m�dia", cod3);

    return 0;
}
