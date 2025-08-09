/* Le uma matriz inteira 10 x 10 e calcula sua transposta
Entradas: matriz 10 x 10
Saida: matriz 10 x 10 (transposta da entrada) */

#include<stdio.h>
# define TAMMAT 4

int main()
{
    int m[TAMMAT][TAMMAT], t[TAMMAT][TAMMAT]; // t armazena a transposta
    int linha, coluna;

    // Leitura matriz
    for (linha = 0; linha < TAMMAT; linha++)
    {
        printf("Entre os elementos da linha %d:\n", linha+1);
        for (coluna = 0; coluna < TAMMAT; coluna++)
            scanf("%d", &m[linha][coluna]);
    }

    // gera a transposta
    for (linha = 0; linha < TAMMAT; linha++)
        for (coluna = 0; coluna < TAMMAT; coluna++)
            t[linha][coluna] = m[coluna][linha];
    // Imprime matriz original (exercicio)
    // Imprime matriz transposta (exercicio)
    return 0;
}
