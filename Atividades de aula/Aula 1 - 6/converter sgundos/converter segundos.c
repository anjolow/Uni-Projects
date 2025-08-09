/*Esse programa converte um valor em segundos para minutos, no formato MM:SS
    Entradas: segundos
    Saídas: Minutos:Segundos*/

#include <stdio.h>

int main(){

    int segundos, minutos, seg_seg;

    printf("Informe os segundos a serem convetidos - ");
    scanf("%d", &segundos);

    minutos = segundos/60;
    seg_seg = segundos%60;

    printf("Segundos em minutos: %d:%d", minutos, seg_seg);

    return 0;
}
