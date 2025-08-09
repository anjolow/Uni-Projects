#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_CTYPE, "");
    int idade;

    printf("Informe sua idade: ");
    scanf("%d", &idade);

    if (idade>=18)
    {
        printf("\n\tCUIDADO! Você pode ser preso!\n\tMas também pode dirigir. Esse é um bônus.\n");
    }

    else
    {
        printf("\n\tVocê não pode ser preso (ainda).\n\tMas não pode dirigir kkkkkkkkkk\n");
    }

    return 0;
}
