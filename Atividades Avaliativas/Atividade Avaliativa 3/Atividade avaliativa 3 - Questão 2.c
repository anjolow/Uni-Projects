//Lucas Anjos da Silva
/*Este programa adquire informações sobre a renda de pessoas de certa localidade (urbano ou rural) e calcula a média entre
essas rendas de cada localidade, além de mostrar qual a maior, qual a menor e qual a porcentagem de pessoas de cada localidade
em relação ao total.
        Entradads: número de entrevistados, renda mensal, localidade;
        Saídas: Maior renda mensal, Menor renda mensal, Percentual de entrevistados de áreas urbanas,
                Percentual de entrevistados de áreas rurais, Média da renda nas áreas urbanas,
                Média da renda nas áreas rurais.*/

#include <stdio.h>
#include <locale.h>

int main(){

    setlocale(LC_CTYPE,"Portuguese");

    char local; //Variável do local
    int qtd_ent, i; //Quantidade de pessoas de entrada e índice para o for
    float tot, conta_u, conta_r; //Variáveis de contagem de quantas pessoas são do meio urbano ou do rural
    float perc_u, perc_r; //Variáveis para o cálculo das porcentagens
    float renda, maior, menor; //Variáveis para o cálculo da maior e menor renda
    float acu_u, media_u; //Variáveis para o cálculo da média da renda das pessoas no Urbano
    float acu_r, media_r; //Variáveis para o cálculo da médi ada renda das pessoa no Rural

    printf("Informe a quantidade de pessoas entrevistadas: ");
    scanf("%d", &qtd_ent);

    conta_u = conta_r = perc_u = perc_r = 0; //Atribuição destas variáveis como 0 para evitar erros em fórmulas


    printf("Informe a renda mensal e a localidade (U - urbana, R - rural) da pessoa 1: "); //Adquire informações da pessoa 1
    scanf("%f %c", &renda, &local);
    if(local == 'U' || local == 'u') //Verificação da localidade
    {
        acu_u = renda; //Acumula a renda na variável acumuladora
        conta_u++; //Soma 1 na contagem de pessoas do meio urbano
    }
    else if(local == 'R' || local == 'r')
         {
            acu_r = renda;
            conta_r++;
         }
    else printf("\nLocalidade inválida.\n"); //Informa ao usuário que a localidade informada é inválida

    maior = menor = renda; //Atribui maior e menor como a primeira renda informada para fins de comparação com o resto

    for(i = 1; i < qtd_ent; i++)
    {
        printf("Informe a renda mensal e a localidade (U - urbana, R - rural) da pessoa %d: ", i+1);
        scanf("%f %c", &renda, &local);

        if(renda>maior) //Verificação se as próximas rendas informadas substituirão o valor de maior ou menor da primeira renda informada
            maior = renda;
        else if(renda<menor)
            menor = renda;

        if(local == 'U' || local == 'u')
        {
            acu_u = acu_u + renda;
            conta_u++;
        }
        else if(local == 'R' || local == 'r')
             {
                acu_r = acu_r + renda;
                conta_r++;
             }
        else printf("\nLocalidade inválida.\n");
    }

    tot = conta_u + conta_r; //Calcula a porcentagmem de pessoas no meio urbano e no meio rural
    if(conta_u>0)
        perc_u = 100/(tot/conta_u);
    if(conta_r>0)
        perc_r = 100/(tot/conta_r);

    printf("\n\nMaior renda mensal: R$ %.2f", maior); //Imprime as saídas ao usuário
    printf("\nMenor renda mensal: R$ %.2f", menor);
    printf("\nPercentual de entrevistados de áreas urbanas: %.2f%%", perc_u);
    printf("\nPercentual de entrevistados de áreas rurais: %.2f%%\n", perc_r);

    if(conta_u > 0)
    { //Calcula a média de renda nas áreas urbanas e rurais e imprime esse valor ao usuário, caso existam pessoas nessas áreas
        media_u = acu_u/conta_u;
        printf("Média de renda nas áreas urbanas: R$ %.2f\n", media_u);
    }
    if(conta_r > 0)
    {
        media_r = acu_r/conta_r;
        printf("Média de renda nas áreas rurais: R$ %.2f\n", media_r);
    }

    return 0;
}
