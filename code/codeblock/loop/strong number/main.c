#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,temp,factorial,rem,sum=0;
    printf("enter a number ");
    scanf("%d",&a);
    temp=a;
    while(temp>0){
        rem=temp%10;
        factorial=1;
        for(i=1;i<=rem;i++){
            factorial=factorial*i;
        }
        sum+=factorial;
        temp=temp/10;
    }
    printf("sum=%d",sum);
}
