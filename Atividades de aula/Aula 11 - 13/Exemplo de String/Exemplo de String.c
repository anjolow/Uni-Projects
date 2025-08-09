/*Exemplo de leitura de n strings, sem parar no 
branco:*/

#include <stdio.h>

int main()
{
    int seguir;
    char nome[30];
    seguir = 1;
    while (seguir)
    {   puts("\nNome:");
        gets(nome);
        //para quando sem conteúdo – enter direto
        if (nome[0] == '\0')
        seguir = 0;else 
        //não pode puts:2 conteúdos
        printf("\nNome informado: %s", nome);
    }
    return 0;
} 