#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int main()
{
    int i;
    int j;

    char mat[23][61];

    FILE *file;
    file=fopen("mapa1.txt", "r");

    for(i=0; i<23; i++)
    {
        for(j=0; j<61; j++)
        {
            if (!fscanf(file, "%c", &mat[i][j]))
            break;
        }

    }
    fclose(file);
}
