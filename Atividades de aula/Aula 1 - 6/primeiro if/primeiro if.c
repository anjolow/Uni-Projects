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
        printf("\n\tCUIDADO! Voc� pode ser preso!\n\tMas tamb�m pode dirigir. Esse � um b�nus.\n");
    }

    else
    {
        printf("\n\tVoc� n�o pode ser preso (ainda).\n\tMas n�o pode dirigir kkkkkkkkkk\n");
    }

    return 0;
}
