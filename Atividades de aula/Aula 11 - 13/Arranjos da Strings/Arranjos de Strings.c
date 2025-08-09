/* Armazenar os nomes, notas e frequência de um aluno de uma turma
    Entradas: nomes dos alunos, notar e frequencias
    Saidas: nomes dos alunos e respectivos conceitos */

#include<stdio.h>
#include<string.h>
#define TAM_TURMA 40
#define TAM_NOME 20
#define TAM_AVISO 60

int main()
{
    //array que armazena os nomes. Vetor de strings ou matriz de char
    char nome[TAM_TURMA][TAM_NOME];
    float nota[TAM_TURMA]; //array para as notas
    int freq[TAM_TURMA]; //array para a frequencia
    char mensagem[TAM_AVISO]; //string para imprimir na tela
    int tam, i;

    //leitura dos nomes, notas e frequencia
    printf("Entre o número de alunos da turma:\n");
    scanf("%d", &tam);
    
    for(i=0;i<tam;i++)
    {
        getchar();
        printf("Entre o nome do aluno %d:", i+1);
        gets(nome[i]);
        printf("Entre a nota do aluno %d:", i+1);
        scanf("%f", &nota[i]);
        printf("Entre a frequencia do aluno %d:", i+1);
        scanf("%d", &freq[i]);
    }

    printf("\n\n");
    
    // imprime os nomes dos alunos e o conceito final
    for (i=0; i<tam; i++)
    {
        strcpy(mensagem,nome[i]); // copia o nome pra variavel de impressao
        if (freq[i]<0.75*45) // frequencia minima
            strcat(mensagem, ": conceito FF");
        else
            if (nota[i] >= 8.5)
                strcat(mensagem, ": conceito A");
            else
                if (nota[i] >= 7.5)
                    strcat(mensagem, ": conceito B");
                else
                    if (nota[i] >= 6)
                        strcat(mensagem, ": conceito C");
                    else
                        strcat(mensagem, ": conceito D");
        puts(mensagem);
    }
    return 0;
}