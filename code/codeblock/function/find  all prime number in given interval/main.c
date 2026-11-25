#include <stdio.h>
#include <stdlib.h>
int prime (int num)
{
    if (num < 2)
        return 0;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}
int main()
{
    int a,i;
    printf("enter a number ");
    scanf("%d",&a);
   printf("the prime are :");
   for(i=2;i<=a;i++){
  if(prime(i))
  {
      printf("%d \n./",i);
  }

   }
    return 0;
}
