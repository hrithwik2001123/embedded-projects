#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i=1,b=0;
    printf("enter a number to find perfect number");
    scanf("%d",&a);

            while(a>i){
               if(a%i==0)
               {

                   b+=i;
               }

            i++;

           }
           if(b==a){
                printf(" its a perfect number ");
            }
            else {
                printf("its not a perfect number");
            }


         return 0;
    }


