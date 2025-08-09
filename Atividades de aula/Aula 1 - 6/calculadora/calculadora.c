#include <stdio.h>
#include <locale.h>

int main(){

    setlocale(LC_CTYPE, "Portuguese");

    char oper;
    float n1,n2;

    printf("Informe a operacao\n");
    scanf("%c",&oper);
    printf("Informe o primeiro numero\n");
    scanf("%f",&n1);
    printf("Informe o segundo numero\n");
    scanf("%f",&n2);

    switch(oper){
        case '+' : printf("%f\n",n1+n2);
                   break;
        case '-' : printf("%f\n",n1-n2);
                   break;
        case '*' : printf("%f\n",n1*n2);
                   break;
        case '/' : if (n2 != 0)
                       printf("%f\n",n1/n2);
                   else
                       printf("Divisao por zero\n");
                   break;
        default : printf("Operacao invalida\n");
    }
    return 0;
}
