//Lucas Anjos da Silva
/*
Este programa realiza a movimentação de um Ninja através de um determinado mapa definido por coordenadas cartesianas.
As coordenadas estão orientadas de tal forma que o eixo X aumenta para direita e o eixo Y aumenta para baixo.
    Entradas: coordenadas limites superior e inferior do mapa; coordenadas iniciais do ninja; passo de deslocamento do ninja.
    Saídas: quantos passos o ninja deu até chegar à borda do mapa
*/

#include <stdio.h>
#include <locale.h>

typedef struct //Estrutura para definir a posição do ninja
{
    int x;
    int y;

}POSICAO;

typedef struct //Estrutura para definir o deslocamento realizado pelo ninja
{
    int x;
    int y;

}DIRECAO;

typedef struct //Declaração da estrutura de informações que compõem o ninja
{
    POSICAO pos;
    DIRECAO descl;

}NINJA;

int moveNinja(NINJA *ninja, POSICAO sup, POSICAO inf); //Função que move o ninja

int main()
{
    setlocale(LC_CTYPE, "Portuguese");
    int passos=0; //Variável para contar os passos realizados pelo ninja
    POSICAO superior; //Declaração estrutura que define o limite superior do mapa
    POSICAO inferior; //Declaração estrutura que define o limite inferior do mapa
    NINJA ninja; //Declaração do ninja

    printf("Informe a posição do canto superior esquerdo do mapa: "); //Aquisição das coordenadas superiores do mapa
    scanf("%d %d", &superior.x, &superior.y);

    printf("Informe a posição do canto inferior esquerdo do mapa: "); //Aquisição das coordenadas inferiores do mapa
    scanf("%d %d", &inferior.x, &inferior.y);

    printf("Informe as coordenadas x e y da posição do ninja: "); //Aquisição das coordenadas do ninja, realizando a consistência de estar dentro do limite do mapa
    do
    {
        scanf("%d %d", &ninja.pos.x, &ninja.pos.y);
        if((ninja.pos.x<superior.x || ninja.pos.x>inferior.x) || (ninja.pos.y<superior.y || ninja.pos.y>inferior.y))
            printf("Posição inválida. Deve estar entre (%d, %d) e (%d, %d). Informe novamente: ", superior.x, superior.y, inferior.x, inferior.y);
    }while((ninja.pos.x<superior.x || ninja.pos.x>inferior.x) || (ninja.pos.y<superior.y || ninja.pos.y>inferior.y));

    printf("Informe os deslocamentos do ninja em x e y: "); //Aquisição do deslocamento do ninja, realizando a consistência de ser -1, 0 ou 1, tanto em x quanto em y
    do
    {
        scanf("%d %d", &ninja.descl.x, &ninja.descl.y);
        if((ninja.descl.x!=-1 && ninja.descl.x!=0 && ninja.descl.x!=1) || (ninja.descl.y!=-1 && ninja.descl.y!=0 && ninja.descl.y!=1))
            printf("Deslocamento inválido. Deve ser -1, 0 ou 1. Informe novamente: ");
        else if(ninja.descl.x==0 && ninja.descl.y==0)
            printf("Deslocamento inválido. O deslocamento não pode ser nulo em ambas as coordenadas. Informe novamente: ");
    }while((ninja.descl.x!=-1 && ninja.descl.x!=0 && ninja.descl.x!=1) || (ninja.descl.y!=-1 && ninja.descl.y!=0 && ninja.descl.y!=1) || (ninja.descl.x==0 && ninja.descl.y==0));

    printf("O Ninja está caminhando...\n");

    while(moveNinja(&ninja, superior, inferior)!=0) //Laço de repetição para fazer o ninja caminhar enquanto não acha a borda do mapa
    {
        passos++;
        printf("Posição do ninja após passo %d: (%d, %d)\n", passos, ninja.pos.x, ninja.pos.y); //Informa a posição passo a passo
    }

    printf("\nO ninja deu %d passos até encontrar o limite.\n", passos); //Informa quantos passos o ninja deu até encontrar o limite do mapa

    return 0;
}

int moveNinja(NINJA *ninja, POSICAO sup, POSICAO inf)
{

    if((ninja->pos.x == sup.x || ninja->pos.x == inf.x) || (ninja->pos.y == sup.y || ninja->pos.y == inf.y)) //Verifica se o ninja está no limite do mapa e retorna 0
        return 0;
    else //Caso ainda não estiver, realiza o deslocamento adquirido anteriormente e retorna 1
    {
        ninja->pos.x = ninja->pos.x + ninja->descl.x;
        ninja->pos.y = ninja->pos.y + ninja->descl.y;
        return 1;
    }
}
