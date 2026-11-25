#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=10;
    int*ptr;
    ptr=&x;
    printf("address of x =%p\n",&x);
     printf("address of x =%p\n",ptr);
      printf("address of x =%d\n",x);
       printf("address of x =%d\n",*ptr);
       printf("%d",sizeof(ptr));
        printf("%d",sizeof(x));
    return 0;
}
