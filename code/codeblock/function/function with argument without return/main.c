#include <stdio.h>
#include <stdlib.h>
int gra(int x , int y)
{
    if(x>y){
        printf("largest number is %d",x);
    }
    else{
        printf("largest number is %d",y);
    }
}
int main()
{
     int x,y;
     printf("enter a two number ");
    scanf("%d%d",&x,&y);
    gra(x,y);
    return 0;
}
