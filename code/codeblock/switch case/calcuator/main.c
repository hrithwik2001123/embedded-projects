#include <stdio.h>
#include <stdlib.h>

int main()
{
    float a,c,out;
    char b;
    printf("enter your -,+,*,/" );
    scanf("%f%c%f",&a,&b,&c);
    switch(b){
    case '-': out=a-c;
            printf("output %f ",out);
            break;
    case '+':out=a+c;
            printf("output %f ",out);
            break;
    case '*': out=a*c;
             printf("output %f ",out);
             break;
    case '/': out=a/c;
            printf("output %f ",out);
            break;
        }
    return 0;
}
