#include<stdio.h>

int main()
{
    int i, j, n, count;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter the elements of the array:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Occurrences of each element:\n");
    for(i = 0; i < n; i++)
    {
        count = 0;
        for(j = 0; j < n; j++)
        {
            if(a[i] == a[j])
            {
                count++;
            }
        }
        if(i == 0 || a[i] != a[i - 1])
        {
            printf("%d occurs %d times\n", a[i], count);
        }
    }

    return 0;
}
