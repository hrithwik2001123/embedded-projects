#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,j_prime=0,j_notprime=0,i,k;
    printf("enter a limit ");
    scanf("%d",&n);
    int s[100];
    int s1[100];
    int count=0;

      for(k=2;k<=n;k++)
      {
          for(i=1;i<=k;i++)
   {
    if(k%i==0){
            count++;
    }
   }
   if(count==2){
    printf("%d\n",k);
    s[j_prime]=k;
    j_prime++;
   }
   else{
    s1[j_notprime]=k;
    j_notprime++;
   }
      }
      for(i=0;i<j_prime;i++)
       {
           printf("prime number %d\n",S[i]);

       }
       for(i=0;i<j_notprime;i++)
       {
           printf("prime number %d\n",S1[i]);

       }
}
