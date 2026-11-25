#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,rem,c,i=0,sum=0,b,r=1,j,n,m=1;
    printf("enter a number ");
    scanf("%d",&a);
    int tem=a;
    for(i=0;a>0;i++){
        rem=a%10;
        a=a/10;

    }

    while(tem>0){
        rem=tem%10;
         m=1;
    for(j=1;j<=i;j++){
        m=m*rem;
    }
    sum+=m;
    tem=tem/10;
    }
    printf("%d \n",sum);
    return 0;
}
