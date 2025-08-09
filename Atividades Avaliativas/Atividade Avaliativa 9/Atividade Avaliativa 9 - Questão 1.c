//Lucas Anjos da Silva
/*
Este programa realiza a movimenta��o de um Ninja atrav�s de um determinado mapa definido por coordenadas cartesianas.
As coordenadas est�o orientadas de tal forma que o eixo X aumenta para direita e o eixo Y aumenta para baixo.
    Entradas: coordenadas limites superior e inferior do mapa; coordenadas iniciais do ninja; passo de deslocamento do ninja.
    Sa�das: quantos passos o ninja deu at� chegar � borda do mapa
*/

#include <stdio.h>
#include <locale.h>

typedef struct //Estrutura para definir a posi��o do ninja
{
    int x;
    int y;

}POSICAO;

typedef struct //Estrutura para definir o deslocamento realizado pelo ninja
{
    int x;
    int y;

}DIRECAO;

typedef struct //Declara��o da estrutura de informa��es que comp�em o ninja
{
    POSICAO pos;
    DIRECAO descl;

}NINJA;

int moveNinja(NINJA *ninja, POSICAO sup, POSICAO inf); //Fun��o que move o ninja

int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    int passos=0; //Vari�vel para contar os passos realizados pelo ninja
    POSICAO superior; //Declara��o estrutura que define o limite superior do mapa
    POSICAO inferior; //Declara��o estrutura que define o limite inferior do mapa
    NINJA ninja; //Declara��o do ninja

    printf("Informe a posi��o do canto superior esquerdo do mapa: "); //Aquisi��o das coordenadas superiores do mapa
    scanf("%d %d", &superior.x, &superior.y);

    printf("Informe a posi��o do canto inferior esquerdo do mapa: "); //Aquisi��o das coordenadas inferiores do mapa
    scanf("%d %d", &inferior.x, &inferior.y);

    printf("Informe as coordenadas x e y da posi��o do ninja: "); //Aquisi��o das coordenadas do ninja, realizando a consist�ncia de estar dentro do limite do mapa
    do
    {
        scanf("%d %d", &ninja.pos.x, &ninja.pos.y);
        if((ninja.pos.x<superior.x || ninja.pos.x>inferior.x) || (ninja.pos.y<superior.y || ninja.pos.y>inferior.y))
            printf("Posi��o inv�lida. Deve estar entre (%d, %d) e (%d, %d). Informe novamente: ", superior.x, superior.y, inferior.x, inferior.y);
    }while((ninja.pos.x<superior.x || ninja.pos.x>inferior.x) || (ninja.pos.y<superior.y || ninja.pos.y>inferior.y));

    printf("Informe os deslocamentos do ninja em x e y: "); //Aquisi��o do deslocamento do ninja, realizando a consist�ncia de ser -1, 0 ou 1, tanto em x quanto em y
    do
    {
        scanf("%d %d", &ninja.descl.x, &ninja.descl.y);
        if((ninja.descl.x!=-1 && ninja.descl.x!=0 && ninja.descl.x!=1) || (ninja.descl.y!=-1 && ninja.descl.y!=0 && ninja.descl.y!=1))
            printf("Deslocamento inv�lido. Deve ser -1, 0 ou 1. Informe novamente: ");
        else if(ninja.descl.x==0 && ninja.descl.y==0)
            printf("Deslocamento inv�lido. O deslocamento n�o pode ser nulo em ambas as coordenadas. Informe novamente: ");
    }while((ninja.descl.x!=-1 && ninja.descl.x!=0 && ninja.descl.x!=1) || (ninja.descl.y!=-1 && ninja.descl.y!=0 && ninja.descl.y!=1) || (ninja.descl.x==0 && ninja.descl.y==0));

    printf("O Ninja est� caminhando...\n");

    while(moveNinja(&ninja, superior, inferior)!=0) //La�o de repeti��o para fazer o ninja caminhar enquanto n�o acha a borda do mapa
    {
        passos++;
        printf("Posi��o do ninja ap�s passo %d: (%d, %d)\n", passos, ninja.pos.x, ninja.pos.y); //Informa a posi��o passo a passo
    }

    printf("\nO ninja deu %d passos at� encontrar o limite.\n", passos); //Informa quantos passos o ninja deu at� encontrar o limite do mapa

    return 0;
}

int moveNinja(NINJA *ninja, POSICAO sup, POSICAO inf)
{

    if((ninja->pos.x == sup.x || ninja->pos.x == inf.x) || (ninja->pos.y == sup.y || ninja->pos.y == inf.y)) //Verifica se o ninja est� no limite do mapa e retorna 0
        return 0;
    else //Caso ainda n�o estiver, realiza o deslocamento adquirido anteriormente e retorna 1
    {
        ninja->pos.x = ninja->pos.x + ninja->descl.x;
        ninja->pos.y = ninja->pos.y + ninja->descl.y;
        return 1;
    }
}
