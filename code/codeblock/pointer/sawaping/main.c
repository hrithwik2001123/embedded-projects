#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=10;
    int y=5;
    int *ptr1,*ptr2;
    ptr1=&x;
    ptr2=&y;
    int temp;
    temp=*ptr1;
    *ptr1=*ptr2;
    *ptr2=temp;
    printf("x=%d , y=%d",*ptr1,*ptr2);
    return 0;
}
