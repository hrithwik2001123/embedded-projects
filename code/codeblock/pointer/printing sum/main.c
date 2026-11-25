#include <stdio.h>
#include <stdlib.h>

int main()
{
     int  x=10;
     int  y=5;
     int * ptr1,*ptr2;
     ptr1=&x;
     ptr2=&y;

     int  sum = *ptr1+ *ptr2;    //int *ptr=x+y;
     printf("sum=%d",sum);

    return 0;
}
