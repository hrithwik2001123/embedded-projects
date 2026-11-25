#include <stdio.h>
#include <stdlib.h>

int main()
{
    int r, c, i, j, k;
    printf("Enter number of rows: ");
    scanf("%d", &r);
    printf("Enter number of columns: ");
    scanf("%d", &c);
    int a[r][c], a1[r][c], m[r][c];
    printf(" the first matrix:\n");
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    printf(" the second matrix:\n");
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            scanf("%d", &a1[i][j]);
        }
    }
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
            *(*(m+i)+j)=0;
            for(k = 0; k < c; k++)
            {
                *(*(m+i)+j) += *(*(a+i)+k) * *(*(a1+k)+j);
            }
        }
    }


    printf("The result\n");
    for(i = 0; i < r; i++)
    {
        for(j = 0; j < c; j++)
        {
     printf("%d ", *(*(m+i)+j));
        }
        printf("\n");
    }

    return 0;
}
