#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,count=0,b,j,c;
    printf("enter a number ");
    int i=1;
    scanf("%d",&a);
while (i<=a)
   {
    if(a%i==0){
            count++;
            printf("%d\n",i);

    }
    b=i;
    for(j=0;j<b;j++)
    {
        if(a%b==0){
            c++;
        }
        if(c==2){
            printf("%d,",i);
        }
    }
    i++;
   }

    return 0;
}
