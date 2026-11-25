#include <stdio.h>
#include <stdlib.h>

int main()
{


    char arry[10];
    char*ptr=arry;
    for(int i=0;i!=10;i++)
    {

        scanf("%c",(ptr+i));
    }
     for(int i=0;i!=10;i++)
    {

        printf("%c",*(ptr+i));
    }
    return 0;
}
