#include <stdio.h>

void centroide(float xe, float ye, float xd, float yd, float *xc, float*yc);

int main()
{
    float p1[2], p2[2], centro[2];

    printf("Informe as coordenadas do ponto inferior esquerdo do retangulo: ");
    scanf("%f%f", &p1[0], &p1[1]);
    printf("Informe as coordenadas do ponto superior direito do retangulo: ");
    scanf("%f%f", &p2[0], &p2[1]);


    centroide(p1[0], p1[1], p2[0], p2[1], &centro[0], &centro[1]);

    printf("O ponto centroide tem coordenadas x=%.2f e y=%.2f\n", centro[0], centro[1]);

    return 0;
}

void centroide(float xe, float ye, float xd, float yd, float *xc, float*yc)
{
    *xc = (xe+xd)/2;
    *yc = (ye+yd)/2;
}
