#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,count=0;
    printf("enter a number ");
    int i=1;
    scanf("%d",&a);
while (i<=a)
   {
    if(a%i==0){
            count++;
            printf("%d\n",i);

    }
    i++;
   }
   if(count==2){
    printf("prime");
   }
    return 0;
}
