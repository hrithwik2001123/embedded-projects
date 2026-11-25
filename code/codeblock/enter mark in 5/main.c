#include <stdio.h>
#include <stdlib.h>

int main()
{
    float m1,m2,m3,m4,m5,t,a,p;
    printf("enter 5 subject mark ");
    scanf("%f%f%f%f%f",&m1,&m2,&m3,&m4,&m5);
    t=m1+m2+m3+m4+m5;
    a=t/5;
    p=(t/400)*100;
    printf("total %f\nave is %f\n perc is %f\n",t,a,p);
    return 0;
}
