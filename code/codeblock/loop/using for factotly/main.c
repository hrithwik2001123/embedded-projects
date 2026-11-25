#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,b;
    b=1;
  printf("enter a number");
  scanf("%d",&a);
    for(i=1;i<=5;i++){
        b=b*i;
    }
    printf("%d",b);
    return 0;
}
