#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,ans;
    printf("enter a number");
    scanf("%d",&a);
    while(i<=10){
        ans=a*i;
    printf(" %d * %d =%d \n",a,i,ans);
    i++;
    }
    return 0;
}
