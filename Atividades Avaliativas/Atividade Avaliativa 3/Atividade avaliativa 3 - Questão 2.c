//Lucas Anjos da Silva
/*Este programa adquire informa��es sobre a renda de pessoas de certa localidade (urbano ou rural) e calcula a m�dia entre
essas rendas de cada localidade, al�m de mostrar qual a maior, qual a menor e qual a porcentagem de pessoas de cada localidade
em rela��o ao total.
        Entradads: n�mero de entrevistados, renda mensal, localidade;
        Sa�das: Maior renda mensal, Menor renda mensal, Percentual de entrevistados de �reas urbanas,
                Percentual de entrevistados de �reas rurais, M�dia da renda nas �reas urbanas,
                M�dia da renda nas �reas rurais.*/

#include <stdio.h>
#include <locale.h>

int main(){

    setlocale(LC_CTYPE,"Portuguese");

    char local; //Vari�vel do local
    int qtd_ent, i; //Quantidade de pessoas de entrada e �ndice para o for
    float tot, conta_u, conta_r; //Vari�veis de contagem de quantas pessoas s�o do meio urbano ou do rural
    float perc_u, perc_r; //Vari�veis para o c�lculo das porcentagens
    float renda, maior, menor; //Vari�veis para o c�lculo da maior e menor renda
    float acu_u, media_u; //Vari�veis para o c�lculo da m�dia da renda das pessoas no Urbano
    float acu_r, media_r; //Vari�veis para o c�lculo da m�di ada renda das pessoa no Rural

    printf("Informe a quantidade de pessoas entrevistadas: ");
    scanf("%d", &qtd_ent);

    conta_u = conta_r = perc_u = perc_r = 0; //Atribui��o destas vari�veis como 0 para evitar erros em f�rmulas


    printf("Informe a renda mensal e a localidade (U - urbana, R - rural) da pessoa 1: "); //Adquire informa��es da pessoa 1
    scanf("%f %c", &renda, &local);
    if(local == 'U' || local == 'u') //Verifica��o da localidade
    {
        acu_u = renda; //Acumula a renda na vari�vel acumuladora
        conta_u++; //Soma 1 na contagem de pessoas do meio urbano
    }
    else if(local == 'R' || local == 'r')
         {
            acu_r = renda;
            conta_r++;
         }
    else printf("\nLocalidade inv�lida.\n"); //Informa ao usu�rio que a localidade informada � inv�lida

    maior = menor = renda; //Atribui maior e menor como a primeira renda informada para fins de compara��o com o resto

    for(i = 1; i < qtd_ent; i++)
    {
        printf("Informe a renda mensal e a localidade (U - urbana, R - rural) da pessoa %d: ", i+1);
        scanf("%f %c", &renda, &local);

        if(renda>maior) //Verifica��o se as pr�ximas rendas informadas substituir�o o valor de maior ou menor da primeira renda informada
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
        else printf("\nLocalidade inv�lida.\n");
    }

    tot = conta_u + conta_r; //Calcula a porcentagmem de pessoas no meio urbano e no meio rural
    if(conta_u>0)
        perc_u = 100/(tot/conta_u);
    if(conta_r>0)
        perc_r = 100/(tot/conta_r);

    printf("\n\nMaior renda mensal: R$ %.2f", maior); //Imprime as sa�das ao usu�rio
    printf("\nMenor renda mensal: R$ %.2f", menor);
    printf("\nPercentual de entrevistados de �reas urbanas: %.2f%%", perc_u);
    printf("\nPercentual de entrevistados de �reas rurais: %.2f%%\n", perc_r);

    if(conta_u > 0)
    { //Calcula a m�dia de renda nas �reas urbanas e rurais e imprime esse valor ao usu�rio, caso existam pessoas nessas �reas
        media_u = acu_u/conta_u;
        printf("M�dia de renda nas �reas urbanas: R$ %.2f\n", media_u);
    }
    if(conta_r > 0)
    {
        media_r = acu_r/conta_r;
        printf("M�dia de renda nas �reas rurais: R$ %.2f\n", media_r);
    }

    return 0;
}
