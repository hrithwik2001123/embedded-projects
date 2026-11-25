#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a;
    printf("enter your password ");
    scanf("%c",&a);
    (a == 'p') ?printf("password is verified"):printf(" invalid");
    return 0;
}
