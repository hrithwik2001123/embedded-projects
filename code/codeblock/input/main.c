#include <stdio.h>
#include <stdlib.h>

int main()
{
    float c,f,ans,ans1;
    printf("enter the Celsiuse  value  ");
    scanf("%f",&c);
    printf("enter the fahrenheit value ");
    scanf("%f",&f);
    ans=c*9/5+32;
    ans1=(f-32)*5/9;
    printf("total is %f\n",ans);
    printf("total is %f",ans1);
    return 0;
}
