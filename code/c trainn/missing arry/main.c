#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,n,j;
    int arry[5]={1,2,3,5};
    n=5;
    int total_sum=n*(n+1)/2;
    int arry_sum=0;
    for(i=0;i<n-1;i++)
    {
        arry_sum+=arry[i];
    }
    int miss=total_sum-arry_sum;
    printf("%d",miss);

    return 0;
}
