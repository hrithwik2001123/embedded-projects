#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i=1;
    printf("enter a number to find factor");
    scanf("%d",&a);
    while(i<=a){
            if(a%i==0){

            printf("%d\n",i);
           }
           i++;
        }
         return 0;
    }


