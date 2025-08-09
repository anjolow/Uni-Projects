#include <stdio.h>
#include <math.h>
#include <locale.h>


int main()
{
    setlocale(LC_CTYPE,"Portuguese");

    int valor;

    valor = 2;

    switch (valor)
    {
        case 0:
            printf("\nCaso 0\n");
            break;
        case 1:
            printf("\nCaso 1\n");
            break;
        case 2:
            printf("\nCaso 2\n");
            break;
    }


    return 0;
}
