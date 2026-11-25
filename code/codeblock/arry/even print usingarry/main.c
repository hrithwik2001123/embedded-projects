#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,n;
    printf("enter a limte");
    scanf("%d",&n);
    int arry[n];
    printf("enter a number");
    for(i=0;i<n;i++)
    {
        scanf("%d",&arry[i]);

    }
    for(j=0;j<n;j++)
        {
            if(arry[j]%2==0){
            printf(" %d\n",arry[j]);
            }

    }

}
