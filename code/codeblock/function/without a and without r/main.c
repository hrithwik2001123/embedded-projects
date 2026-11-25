#include <stdio.h>
#include <stdlib.h>
int gra()
{
 int x,y;
     printf("enter a two number ");
    scanf("%d%d",&x,&y);
    if(x>y){
            printf("enter largest %d",x);
    }
    else{
        printf("enter largest %d",y);

    }
}
int main()
{
    gra();

}
