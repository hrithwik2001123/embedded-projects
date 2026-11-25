#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i,count=1,j;
    printf("enter a limit");
    scanf("%d",&n);
    int arry[n];
    for(i=0;i<n;i++)
    {
        scanf("%d",&arry[i]);

    }
        for(i=0;i<n-1;i++)
        {
            for(j=0;j<n;j++)
            {

                if(arry[i]==arry[j]&&i!=j)
                {

                    break;
                }
            }
            if(j==n)
            {

                printf("unique element %d",arry[i]);
                ++count;
            }
        }


    return 0;
}
