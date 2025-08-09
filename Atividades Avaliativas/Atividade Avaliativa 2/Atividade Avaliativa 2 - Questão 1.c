/*Lucas Anjos da Silva
Este programa adquire 3 códigos de municípios, suas populações, uma população de referência, calcula
a média das populações e verifica se a população do município é maior ou menor que a média, informando isso ao usuário.
    Entradas: códigos dos municípios, população dos municípios, população de referência.
    Saídas: média das populções, população do município é maior ou menor que a média*/

#include <stdio.h>
#include <math.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    int cod1, cod2, cod3; //Variáveis dos códigos
    int pop1, pop2, pop3; //Variáveis das populações
    int ref; //Variável da referência
    float media; //Variável da média

    printf("\nInforme os códigos de 3 municípios: "); //Aqui o programa pede ao usuário as entradas
    scanf("%d %d %d", &cod1, &cod2, &cod3);
    printf("\nInforme a população do município %d: ", cod1);
    scanf("%d", &pop1);
    printf("Informe a população do município %d: ", cod2);
    scanf("%d", &pop2);
    printf("Informe a população do município %d: ", cod3);
    scanf("%d", &pop3);
    printf("\nInforme o valor referência de população: ");
    scanf("%d", &ref);


    media = (pop1+pop2+pop3)/3.0; //Cálculo da média

    printf("\n\nA média das poopulações dos 3 municípios é: %.2f", media); //Programa informa a média ao usuário


    if (pop1 <= media)
        printf("\n\nO município %d tem população menor ou igual à média", cod1);
        else printf("\nO município %d tem população maior que média", cod1);
    if (pop2 <= media)
        printf("\nO município %d tem população menor ou igual à média", cod2);
        else printf("\nO município %d tem população maior que média", cod2);
    if (pop3 <= media)
        printf("\nO município %d tem população menor ou igual à média", cod3);
        else printf("\nO município %d tem população maior que média", cod3);

    return 0;
}
