#include <stdio.h>
#include <stdlib.h>
int gra()
{
 int x;
     printf("enter a two number ");
    scanf("%d",&x);
    if(x%2==0){
            printf("even %d",x);
    }
    else{
        printf("odd %d",x);

    }
}
int main()
{
    gra();

}
