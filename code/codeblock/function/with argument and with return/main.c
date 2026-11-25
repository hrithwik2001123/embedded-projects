#include <stdio.h>
#include <stdlib.h>
int gra(int x , int y)
{

    if(x>y){
        return x;
    }
    else{
        return y;
    }
}
int main()
{
     int x,y;
     printf("enter a two number ");
    scanf("%d%d",&x,&y);
   int  l=gra(x,y);
     printf("largest number is %d",l);

}
