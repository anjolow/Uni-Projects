//Lucas Anjos da Silva
/*Este programa calcula o valor a ser pago a um estacionamento com base na tabela de pre�os e
no dia e hor�rio de entrada e sa�da informado pelo usu�rio.
    Entradas: hor�rio de entrada e sa�da;
    Sa�da: valor a ser pago.*/
#include <stdio.h>
#include <locale.h>
#include <math.h>

#define UMA_HORA 25.00
#define DUAS_HORAS 45.00
#define HORA_ADICIONAL 15.00

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    int hora_entrada, minuto_entrada; //Vari�veis do hor�rio de entrada
    int hora_saida, minuto_saida; //Vari�veis do hor�rio de sa�da
    int min_ent, min_sai, min_tot, hora_tot; //Vari�veis para o c�lculo do tempo que a pessoa permaneceu no estacionamento
    float pagar; //Vari�vel do falor final a ser pago

    printf("TABELA DE PRE�OS:\n1 hora: R$25.00 \t 2 horas: R$45.00 \t Hora adicional (acima de duas horas): R$15.00");

    printf("\n\nInfomre o hor�rio de entrada (formato HH MM): "); //Programa solicita as informa��es de entrada
    scanf("%d%d", &hora_entrada, &minuto_entrada);
    printf("\nInforme o hor�rio de sa�da (formato HH MM): ");
    scanf("%d%d", &hora_saida, &minuto_saida);

    min_ent = hora_entrada*60; //Convers�o de horas em minutos
    min_sai = hora_saida*60;

    if(min_ent < min_sai)
    {
        min_tot = (min_sai+minuto_saida)-(min_ent+minuto_entrada); //C�lculo dos minutos permanecidos no estacionamento
        hora_tot = min_tot/60; //C�lculo do total de horas permanecidas no estacionamento
        if((min_tot%60)!=0) //Verifica��o se o tempo permanecido n�o � alguma hora redonda. Exemplo: 1:30
            hora_tot = hora_tot + 1;
    }
    else
    {
        min_tot = (min_sai+minuto_saida)-((min_ent+minuto_entrada)-1440); //C�lculo dos minutos permanecidos no estacionamento
        hora_tot = min_tot/60; //C�lculo do total de horas permanecidas no estacionamento
        if((min_tot%60)!=0) //Verifica��o se o tempo permanecido n�o � alguma hora redonda. Exemplo: 1:30
            hora_tot = hora_tot + 1;
    }

    if(min_tot>=1440) //Verifica se o tempo permanecido � igual a 24 horas
        printf("\nSeu carro foi guinchado!\n");
        else if(hora_tot<=1) //Verifica se o tempo permanecido � at� uma hora e calcula o valor a pagar
                 pagar = UMA_HORA;
             else if(hora_tot>1&&hora_tot<=2) //Verifica se o tempo permanecido � at� duas horas e calcula o valor a pagar
                      pagar = DUAS_HORAS;
                  else if(hora_tot>2) //Verifica se o tempo permanecido � maior que duas horas e calcula o valor a pagar
                           pagar = DUAS_HORAS + (hora_tot-2)*HORA_ADICIONAL;

    printf("\nValor devido: R$%.2f\n", pagar); //Imprime o valor a pagar ao usu�rio

    return 0;
}
