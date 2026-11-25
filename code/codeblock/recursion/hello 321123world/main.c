#include <stdio.h>
#include <stdlib.h>
void display (int m)
{
    if(m<1)
    {
        return;
    }
    else
        {
            printf("%d,",m);
            display(m-1);
            printf("%d,",m);
        }
}
int main()
{ int m=5;
    printf("Hello ");
    display(m);
    printf(" world");
    printf("world!\n");
    return 0;
}
