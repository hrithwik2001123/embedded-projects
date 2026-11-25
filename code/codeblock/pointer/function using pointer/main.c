#include <stdio.h>
#include <stdlib.h>

void display(int a,int b)
{
    printf("sum=%d",a+b);
}
int main()
{
    void(*ptr)(int,int)=&display;
    int x ,y;

    printf("enter a two value ");
    scanf("%d%d",&x,&y);
    display(x,y);
    return 0;
}
