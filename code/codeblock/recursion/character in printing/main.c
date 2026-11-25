#include <stdio.h>
#include <stdlib.h>

int main()
{
    char x= 'h';
    char y= 'i';
    char *ptr1,*ptr2;
    ptr1=&x;
    ptr2=&y;
    printf("%c%c",*ptr1,*ptr2);
    return 0;
}
