/*Lucas Anjos da Silva
Este programa utiliza de uma altura e peso referências para verificar quais entre 3 pessoas
devem ser monitoradas por estarem acima do peso de referência e abaixo da altura de referência.
    Entradas: altura de referência, peso de referência, alturas e pesos de 3 pessoas.
    Saída: média dos pesos das pessoas, média das alturas das pessoas, quantidade de pessoas a serem monitoradas*/

#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    float alt_ref, peso_ref; //Variávies de altura e peso referências
    float alt_1, peso_1, alt_2, peso_2, alt_3, peso_3; //Variáveis das pessoas a serem avaliadas
    float media_alt, media_peso; //Variáveis das médias de altura e peso
    int monitoradas; //Variável da quantidade de pessoas a serem monitoradas

    printf("Informe uma altura (m) de referência: ");
    scanf("%f", &alt_ref);
    printf("\nInforme um peso (kg) de referência: ");
    scanf("%f", &peso_ref);

    printf("\nInforme a altura (m) e o peso (kg), respectivamente, da pessoa 1: ");     //Aquisição de informações a serem processadoas:
    scanf("%f %f", &alt_1, &peso_1);                                                    //altura e peso, respectivamente, de todas as 3 pessoas
    printf("\nInforme a altura (m) e o peso (kg), respectivamente, da pessoa 2: ");
    scanf("%f %f", &alt_2, &peso_2);
    printf("\nInforme a altura (m) e o peso (kg), respectivamente, da pessoa 3: ");
    scanf("%f %f", &alt_3, &peso_3);

    media_alt = (alt_1+alt_2+alt_3)/3;     //Cálculo das médias de altura e peso
    media_peso = (peso_1+peso_2+peso_3)/3;

    //Abaixo: sequencia de três condições para a contagem de pessoas a serem monitoradas
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

    printf("\n\nMédia das alturas das 3 pessoas: %.2f", media_alt); //Imprime a media das alturas fornecidos das 3 pessoas
    printf("\nMédia dos pesos das 3 pessoas: %.2f", media_peso); //Imprime a media dos pesos fornecidos das 3 pessoas
    printf("\nQuantidade de pessoas a serem monitoradas: %d", monitoradas); //Imprime a quantidade de pessoas a serem monitoradas

    return 0;
}
