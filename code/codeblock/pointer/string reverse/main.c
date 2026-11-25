#include <stdio.h>
#include <stdlib.h>

int main()
{
    char arry[10];
    char *ptr=arry;
    int i;
    for(i=0;i!=10;i++)
    {

        scanf("%c",(ptr+i));
    }
   for(i=9;i>=0;i--)
   {
       printf("%c",*(ptr+i));
   }
    return 0;
}
