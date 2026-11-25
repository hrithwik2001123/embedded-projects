#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,starting,end,j,start,ed;
    printf("enter a starting number and end number ");
    scanf("%d%d",&starting,&end);
    start=starting;
    ed=end;
   for(i=start;i<=end;i++)
    {
        if(i%2==0)
        {

            printf("%d ,",i);
        }
        }
        printf("\n");
        for(j=start;j<=ed;j++)
            {
        if(i%2!=0){
            printf("%d,",j);
        }
    }
    return 0;
}
