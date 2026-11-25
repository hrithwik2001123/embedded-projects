#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, a, j, sp;
    printf("How many rows do you want: ");
    scanf("%d", &a);
    for (i = a; i >= 1; i--)
    {
        for (sp = 0; sp < a - i; sp++)
        {
            printf(" ");
        }

        for (j = 1; j <= 2 * i - 1; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
