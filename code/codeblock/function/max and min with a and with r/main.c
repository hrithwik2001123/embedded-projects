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
   if(x==l)
   {
      printf("max number is %d min is %d",l,y);
   }
   else {
        printf("max number is %d min is %d",l,x);

   }


}
