#include <stdio.h>

int main(){
    int a,b,res;
    for(a = 1; a<=9; a++){
        printf("Tabuada do %d\n",a);
        for(b=1; b<=9; b++){
            res = a*b;
            printf("%d * %d = %d\n",a,b,res);
        }
    }
    return 0;
}
