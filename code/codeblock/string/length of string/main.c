#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[]="hello\0";
    int i,count=0;
    for(i=0;s[i]!='\0';i++)
    {
      count++;
    }
    printf("length is %d",count);

    return 0;
}
