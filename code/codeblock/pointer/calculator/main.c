#include <stdio.h>
#include <stdlib.h>
void add(int a, int b) { printf("%d", a + b); }
void dif(int a, int b) { printf("%d", a - b); }
void muti(int a, int b) { printf("%d", a * b); }
void div(int a, int b) { printf("%d", a / b); }

int main()
{
    void (*fptr[4])(int,int)={add,dif,muti,div};
    int j;
    int a,b;
    char c;
    printf("enter a you calculation in this form (e.g:5+4)\n");
    scanf("%d%c%d",&a,&c,&b);
    if(c=='+')
    {
        j=0;
    }
    else if(c=='-')
    {
        j=1;
    }
    else if(c=='*')
    {
        j=2;
    }
    else if(c=='/')
    {
        j=4;
    }
    else {
        printf("Invalid operator!\n");
    }

    (*fptr[j])(a,b);
}
