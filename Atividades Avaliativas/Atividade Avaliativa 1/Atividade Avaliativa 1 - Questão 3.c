/*Lucas Anjos da Silva
Este programa recebe 6 coordenadas para formar 3 pontos diferentes P1, P2 e P3 com coordenadas P1(x1,y1), P2(x2,y2) e P3(x3,y3).
Após, calcula a distância entre P1 e P2; entre P1 e P3; entre P2 e P3.
Caso a distância entre os pontos forme um triângulo, o programa calcula sua área e informa ao usuário.
    Entradas: 6 variáveis para as coordenadas;
    Saídas: distâncias entre os pontos; área do triângulo (se for o caso);*/

#include <stdio.h>
#include <locale.h>
#include <math.h>

int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    float x1, x2, x3, y1, y2, y3; //Declaração de variáveis de coordenadas
    float d_p1_p2, d_p1_p3, d_p2_p3; //Declaração de variáveis das distâncias entre os pontos
    float l1, l2, l3; //Declaração de variáveis de lado do triângulo
    float area, perimetro, p; //Declaração de varáveis de área, perímetro e p (que é o perímetro dividido por 2) do triângulo

    printf("  Calcule a distância entre 3 pontos (P1(x1, y1), P2(x2, y2), P3(x3, y3)) e verifique se eles formam um triângulo no plano.\n\n"); //Enunciado para guiar o usuário
    printf("Informe os valores de x1 e y1, respectivamente: "); //Leitura das variáveis do P1
    scanf("%f %f", &x1, &y1);
    printf("\nInfrome os valores de x2 e y2, respectivamente: "); //Leitura das variáveis do P2
    scanf("%f %f", &x2, &y2);
    printf("\nInfrome os valores de x3 e y3, respectivamente: "); //Leitura das variáveis do P3
    scanf("%f %f", &x3, &y3);

    printf("\nP1=(%.2f, %.2f)\t\tP2=(%.2f, %.2f)\t\tP3=(%.2f, %.2f)\n", x1, y1, x2, y2, x3, y3); //Imprime os pontos P1, P2 e P3 para facilitar o entendimento do usuário

    d_p1_p2 = sqrt(pow((x1-x2),2)+pow((y1-y2),2)); //Cálculo de d(P1,P2)
    d_p1_p3 = sqrt(pow((x1-x3),2)+pow((y1-y3),2)); //Cálculo de d(P1,P3)
    d_p2_p3 = sqrt(pow((x2-x3),2)+pow((y2-y3),2)); //Cálculo de d(P2,P3)

    l1 = d_p1_p2; //Atribuição das variáveis de distância como lados do triângulo para facilitar interpretação e escrita do algoritmo
    l2 = d_p1_p3;
    l3 = d_p2_p3;

    printf("\ndistância(P1,P2) = %.2f", d_p1_p2); //Imprime as distâncias calculadas
    printf("\ndistância(P1,P3) = %.2f", d_p1_p3);
    printf("\ndistância(P2,P3) = %.2f", d_p2_p3);

    if(((l1+l2)>l3 && abs(l1-l2)<l3) || ((l1+l3)>l2 && abs(l1-l3)<l2) || ((l2+l3)>l1 && abs(l2-l3)<l1)) //Verifica se os pontos formam um triângulo
    {
        perimetro = l1 + l2 + l3; //Calcula o perímetro do triângulo
        p = perimetro/2; //Divide o perímetro por 2
        area = sqrt((p*(p-l1)*(p-l2)*(p-l3))); //Aplica a fórmula de Heron para calcular a área do triângulo
        printf("\n\nÁrea do triângulo formado pelos três pontos: %.2f \n", area); //Imprime o valor da área ao usuário
    }
    else //Caso os pontos não formarem um triângulo, imprime essa informação ao usuário
    {
    printf("\n\nEstes pontos não formam um triângulo.\n");
    }

    return 0;
}
