#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i;
    printf("enter a size of arry\n");
    scanf("%d",&n);
    int*ptr=(int*)calloc(n,sizeof(int));
    if (ptr==NULL)
    {
        printf("not space");
        exit(0);
    }
    for(i=0;i<n;i++)
    {
        scanf("%d",&ptr[i]);

    }
    for(i=0;i<n;i++)
    {
        printf("%d\n",ptr[i]);
    }

    free(ptr);
}
