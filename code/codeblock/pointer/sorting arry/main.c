#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, j, t = 0, min;
    int arry[5];
    int *ptr = arry;
    for (i = 0;i < 5;i++)
    {
        scanf("%d",(ptr+i));

    }
    printf("before sorting\n");
     for (i = 0; i < 5; i++)
    {
        printf("%d, ",*(ptr+i));
    }
    printf("\nafter sorting\n");
    for (i = 0; i < 5; i++)
    {
        min = i;
        for (j = i + 1; j < 5; j++)
        {
            if (*(ptr+min) > *(ptr+j))
            {
                min = j;
            }
        }
        if (min != i)
        {
            t = *(ptr+i);
            *(ptr+i) = *(ptr+min);
            *(ptr+min) = t;
        }
    }

    for (i = 0; i < 5; i++)
    {
        printf("%d, ",*(ptr+i));
    }

}
