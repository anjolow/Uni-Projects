// Calcula a idade média de 5 pessoas
# include <stdio.h>
# define QTD_PESSOAS 5
int main()
{
    int soma_idades, idade, contador, conta_menores;
    float media_idades;

    soma_idades = 0; // inicializa acumulador em 0
    conta_menores = 0; // inicializa contador em 0

    for (contador = 1; contador <= QTD_PESSOAS; contador ++)
    {
        printf("informe idade %d :", contador); // utiliza contador
        scanf("%d", &idade);
        // vai acumulando idades lidas
        soma_idades = soma_idades + idade;
        if (idade < 18)
            conta_menores++; // incrementa 1 no contador
    }

    // cast, para resultado ser real
    media_idades = (float) soma_idades/QTD_PESSOAS;
    printf("\nA media das %d idades lidas eh %.2f.\n", QTD_PESSOAS, media_idades);
    printf("\nExistem %d pessoas menores de idade.\n", conta_menores);
    return 0;
}
