#include <stdio.h>

int main()
{
    int a, b, max, i = 1,j;
    printf("Enter the first number: ");
    scanf("%d", &a);
    printf("Enter the second number: ");
    scanf("%d", &b);
   max=(a>b)?a:b;
   while(1){
    if(max%a==0&&max%b==0)
    {
    printf("lcm of %d and %d is %d",a,b,max);
        break;
    }
    max++;
   }

}
