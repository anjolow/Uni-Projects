#include <stdio.h>
#include <locale.h>

int main(){

    setlocale(LC_CTYPE,"Portuguese");

    int n,i;
    float m;

    for(i = 0; i < 3; i++){
        printf("Informe o n�mero de matr�cula do aluno: ");
        scanf("%d", &n);
        printf("\nInforme a m�dia do aluno: ");
        scanf("%f", &m);
        if( m >= 6.0 ){
        printf("\nAluno %d aprovado\n\n\n", n);
        }
        else{
        printf("\nAluno %d reprovado\n\n\n", n);
        }
    }
    return 0;
}
