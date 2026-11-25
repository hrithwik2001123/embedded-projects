#include <stdio.h>
#include <stdlib.h>
int fibonacci(int a,int b,int limit)
{   int sum=0;
      sum=a+b;
    if(sum>=limit)
        return;
    printf("%d,",sum);
    return(fibonacci(b,sum,limit));

}
int main()
{
    int num;
    printf("enter a limite\n");
    scanf("%d",&num);
   fibonacci(0,1,num);
    return 0;
}
