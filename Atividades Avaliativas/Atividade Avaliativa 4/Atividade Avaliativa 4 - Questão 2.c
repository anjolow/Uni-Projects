//Lucas Anjos da Silva
/*Este programa simula a movimentação de um objeto em um plano cartesiano dentro de um limite quadrangular ou retangular definido
pelo usuário.
    Entradas: coordenadas dos pontos 1 e 2 de delimitação, coordenadas iniciais do objeto, passo de deslocamento do objeto;
    Sa�das: novas posiçõees a cada movimento, quantidade de movimentos realizadas pelo objeto até sair do perímetro delimitado.*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>

int main()
{
    setlocale(LC_CTYPE, "Portuguese");

    char direcao; //Variável para o usu�rio indicar a direção que o objeto irá se mover
    int movi=0; //Variaável para contar a quantidade de movimentos realizados pelo objeto
    float x1, x2, x0; //Coordenadas em x dos pontos e do objeto
    float y1, y2, y0; //Coordenadas em y dos pontos e do objeto
    float passo; //Passo de deslocamento do objeto

    printf("Informe as coordenadas do ponto P1: "); //Usuário informa as coordenadas do ponto 1
    scanf("%f%f", &x1, &y1);

    printf("Informe as coordenadas do ponto P2: "); //Usuário informa as coordenadas do ponto 2
    do
    {
        scanf("%f%f", &x2, &y2);
        if(x2<=x1 || y2<=y1) //Caso as coordenadas sejam de valor inferior ao do ponto 1, pede ao usuário que informe novamnete
            printf("Coordenadas do ponto P2 inválidas. Informe-as novamente: ");
    } while(x2<=x1 || y2<=y1);

    printf("Informe as coordenadas iniciais do objeto: "); //Usuário informa as coordenadas do objeto
    do
    {
        scanf("%f%f", &x0, &y0);
        if((x0<x1 || x0>x2) || (y0<y1 || y0>y2)) //Caso o objeto esteja fora da delimitação dos pontos 1 e 2, pede ao usuário para que informe novamente as coordenadas
            printf("Coordenadas iniciais do objeto inv�lidas. Informe-as novamente: ");
    } while((x0<x1 || x0>x2) || (y0<y1 || y0>y2));


    printf("Informe o passo de deslocamento: "); //Usuário informa o passo de deslocamento
    do
    {
        scanf("%f", &passo);
        if(passo<=0) //Caso o passo seja negativo ou nulo, pede ao usuário que informe novamente
            printf("O passo deve ser positivo. Informe-o novamente: ");
    } while(passo<=0);

    //Imprime uma tabela mostrando como indicar a direção do movimento desejada
    printf("\nA(a): anda para a esquerda, conforme o passo definido.");
    printf("\nD(d): anda para a direita, conforme o passo definido.");
    printf("\nS(s): anda para baixo, conforme o passo definido.");
    printf("\nW(w): anda para a cima, conforme o passo definido.\n");

    do //Pede a direção de deslocamento desejada e imprime a nova posição do objeto. Faz isso até o objeto sair da delimitação imposta pelos pontos 1 e 2
    {
        fflush(stdin);
        printf("\nInforme a direção de deslocamento: ");
        scanf("%c", &direcao);
        direcao = toupper(direcao);
        switch(direcao)
        {
            case 'A':
                x0 = x0-passo;
                break;
            case 'D':
                x0 = x0+passo;
                break;
            case 'S':
                y0 = y0-passo;
                break;
            case 'W':
                y0 = y0+passo;
                break;
            default: printf("Direção Inválida.\n");
        }
        if(direcao=='A'||direcao=='D'||direcao=='S'||direcao=='W')
        {
            printf("Nova posi��o: %.2f %.2f", x0, y0);
            movi++;
        }
    } while((x0>=x1 && x0<=x2) && (y0>=y1 && y0<=y2));

    printf("\n\nO objeto saiu do perímetro realizando %d movimentos\n\n", movi); //Imprime quantos movimentos o objeto realizou até sair da delimitação

    return 0;
}
