#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[] = "hello";
    char s1[] = "hell";
    int i, count = 0;
    while( s[i] != '\0'||s1[i]!='\0')
    {
        if (s1[i] == s[i])
        {
            count++;
        }
        i++;
    }

    if (count == i)
    {
        printf("The strings are  same\n");
    }
    else
    {
        printf("The strings are not  same\n");
    }

    return 0;
}
