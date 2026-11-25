#include <stdio.h>
#include <stdlib.h>
int amstrong(int a)
{
    for(int i=1;i<=a;i++)
    {
      int n=check_amstrong(i);
      if(i==n)
      {
          printf("%d\n",n);
      }

    }

}
int check_amstrong(int a)
{
     int rem,c,i=0,sum=0,b,r=1,j,n,m=1;
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
    return sum;
}
int main()
{
    int a;
    printf("enter a number");
    scanf("%d",&a);
    amstrong(a);
    return 0;
}
