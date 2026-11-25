#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,rem,rev,i,tem,m=1,j,sum,am;
    printf("enter a number to check the amstrong or not");
    scanf("%d",&a);
    tem=a;
    am=a;
    for(i=0;a>0;i++)
    {

        rem=a%10;
        a=a/10;
    }
    while(tem>0){
            rem=tem%10;
            m=1;
    for(j=1;j<=i;j++){
            m=m*rem;
    }
    sum=sum+m;
    tem=tem/10;
    }
    if(sum==am)
    {
            printf("%d its amstorng \n",sum);
    }
    else {
        printf("its not a amstorng");
    }

    return 0;
}
