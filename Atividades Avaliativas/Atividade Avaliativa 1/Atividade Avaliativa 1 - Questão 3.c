/*Lucas Anjos da Silva
Este programa recebe 6 coordenadas para formar 3 pontos diferentes P1, P2 e P3 com coordenadas P1(x1,y1), P2(x2,y2) e P3(x3,y3).
Ap�s, calcula a dist�ncia entre P1 e P2; entre P1 e P3; entre P2 e P3.
Caso a dist�ncia entre os pontos forme um tri�ngulo, o programa calcula sua �rea e informa ao usu�rio.
    Entradas: 6 vari�veis para as coordenadas;
    Sa�das: dist�ncias entre os pontos; �rea do tri�ngulo (se for o caso);*/

#include <stdio.h>
#include <locale.h>
#include <math.h>

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    float x1, x2, x3, y1, y2, y3; //Declara��o de vari�veis de coordenadas
    float d_p1_p2, d_p1_p3, d_p2_p3; //Declara��o de vari�veis das dist�ncias entre os pontos
    float l1, l2, l3; //Declara��o de vari�veis de lado do tri�ngulo
    float area, perimetro, p; //Declara��o de var�veis de �rea, per�metro e p (que � o per�metro dividido por 2) do tri�ngulo

    printf("  Calcule a dist�ncia entre 3 pontos (P1(x1, y1), P2(x2, y2), P3(x3, y3)) e verifique se eles formam um tri�ngulo no plano.\n\n"); //Enunciado para guiar o usu�rio
    printf("Informe os valores de x1 e y1, respectivamente: "); //Leitura das vari�veis do P1
    scanf("%f %f", &x1, &y1);
    printf("\nInfrome os valores de x2 e y2, respectivamente: "); //Leitura das vari�veis do P2
    scanf("%f %f", &x2, &y2);
    printf("\nInfrome os valores de x3 e y3, respectivamente: "); //Leitura das vari�veis do P3
    scanf("%f %f", &x3, &y3);

    printf("\nP1=(%.2f, %.2f)\t\tP2=(%.2f, %.2f)\t\tP3=(%.2f, %.2f)\n", x1, y1, x2, y2, x3, y3); //Imprime os pontos P1, P2 e P3 para facilitar o entendimento do usu�rio

    d_p1_p2 = sqrt(pow((x1-x2),2)+pow((y1-y2),2)); //C�lculo de d(P1,P2)
    d_p1_p3 = sqrt(pow((x1-x3),2)+pow((y1-y3),2)); //C�lculo de d(P1,P3)
    d_p2_p3 = sqrt(pow((x2-x3),2)+pow((y2-y3),2)); //C�lculo de d(P2,P3)

    l1 = d_p1_p2; //Atribui��o das vari�veis de dist�ncia como lados do tri�ngulo para facilitar interpreta��o e escrita do algoritmo
    l2 = d_p1_p3;
    l3 = d_p2_p3;

    printf("\ndist�ncia(P1,P2) = %.2f", d_p1_p2); //Imprime as dist�ncias calculadas
    printf("\ndist�ncia(P1,P3) = %.2f", d_p1_p3);
    printf("\ndist�ncia(P2,P3) = %.2f", d_p2_p3);

    if(((l1+l2)>l3 && abs(l1-l2)<l3) || ((l1+l3)>l2 && abs(l1-l3)<l2) || ((l2+l3)>l1 && abs(l2-l3)<l1)) //Verifica se os pontos formam um tri�ngulo
    {
        perimetro = l1 + l2 + l3; //Calcula o per�metro do tri�ngulo
        p = perimetro/2; //Divide o per�metro por 2
        area = sqrt((p*(p-l1)*(p-l2)*(p-l3))); //Aplica a f�rmula de Heron para calcular a �rea do tri�ngulo
        printf("\n\n�rea do tri�ngulo formado pelos tr�s pontos: %.2f \n", area); //Imprime o valor da �rea ao usu�rio
    }
    else //Caso os pontos n�o formarem um tri�ngulo, imprime essa informa��o ao usu�rio
    {
    printf("\n\nEstes pontos n�o formam um tri�ngulo.\n");
    }

    return 0;
}
