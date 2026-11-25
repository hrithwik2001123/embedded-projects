#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arry[6]={1,2,3,4,5,6};
    int *ptr=arry;
    for(int i=0;i<6;i++)
    {
      printf("%d\n",(*ptr+i));

    }
    printf("\n");
 for(int i=5;i>=0;i--)
    {
      printf("%d\n",(*ptr+i));

    }
    return 0;
}
