/*Lucas Anjos da Silva
Este programa utiliza de uma altura e peso refer�ncias para verificar quais entre 3 pessoas
devem ser monitoradas por estarem acima do peso de refer�ncia e abaixo da altura de refer�ncia.
    Entradas: altura de refer�ncia, peso de refer�ncia, alturas e pesos de 3 pessoas.
    Sa�da: m�dia dos pesos das pessoas, m�dia das alturas das pessoas, quantidade de pessoas a serem monitoradas*/

#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    float alt_ref, peso_ref; //Vari�vies de altura e peso refer�ncias
    float alt_1, peso_1, alt_2, peso_2, alt_3, peso_3; //Vari�veis das pessoas a serem avaliadas
    float media_alt, media_peso; //Vari�veis das m�dias de altura e peso
    int monitoradas; //Vari�vel da quantidade de pessoas a serem monitoradas

    printf("Informe uma altura (m) de refer�ncia: ");
    scanf("%f", &alt_ref);
    printf("\nInforme um peso (kg) de refer�ncia: ");
    scanf("%f", &peso_ref);

    printf("\nInforme a altura (m) e o peso (kg), respectivamente, da pessoa 1: ");     //Aquisi��o de informa��es a serem processadoas:
    scanf("%f %f", &alt_1, &peso_1);                                                    //altura e peso, respectivamente, de todas as 3 pessoas
    printf("\nInforme a altura (m) e o peso (kg), respectivamente, da pessoa 2: ");
    scanf("%f %f", &alt_2, &peso_2);
    printf("\nInforme a altura (m) e o peso (kg), respectivamente, da pessoa 3: ");
    scanf("%f %f", &alt_3, &peso_3);

    media_alt = (alt_1+alt_2+alt_3)/3;     //C�lculo das m�dias de altura e peso
    media_peso = (peso_1+peso_2+peso_3)/3;

    //Abaixo: sequencia de tr�s condi��es para a contagem de pessoas a serem monitoradas
    if(alt_1<alt_ref && peso_1>peso_ref)
    {
        monitoradas = monitoradas+1;
    }

    if(alt_2<alt_ref && peso_2>peso_ref)
    {
        monitoradas = monitoradas+1;
    }

    if(alt_3<alt_ref && peso_3>peso_ref)
    {
        monitoradas = monitoradas+1;
    }

    printf("\n\nM�dia das alturas das 3 pessoas: %.2f", media_alt); //Imprime a media das alturas fornecidos das 3 pessoas
    printf("\nM�dia dos pesos das 3 pessoas: %.2f", media_peso); //Imprime a media dos pesos fornecidos das 3 pessoas
    printf("\nQuantidade de pessoas a serem monitoradas: %d", monitoradas); //Imprime a quantidade de pessoas a serem monitoradas

    return 0;
}
