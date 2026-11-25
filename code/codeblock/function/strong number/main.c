#include <stdio.h>

int strong(int x)
{
    int sum = 0, i;
    int temp = x;

    while (temp > 0)
    {
        int rem = temp % 10;
        int factorial = 1;

        for (i = 1; i <= rem; i++)
        {
            factorial *= i;
        }

        sum += factorial;
        temp /= 10;
    }

    return sum;
}

int main()
{
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    int s = strong(x);

    if (x == s)
    {
        printf("%d is a strong number.\n", x);
    }
    else
    {
        printf("%d is not a strong number.\n", x);
    }

    return 0;
}
