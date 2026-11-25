#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[]="hello";
    int i,count=0,j;
    for(i=0;s[i]!='\0';i++)
    {
      count++;
    }
    for(j=count-1;j>=0;j--)
    {
        printf("%c",s[j]);
    }
    return 0;
}
