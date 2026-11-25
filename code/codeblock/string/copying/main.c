s#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[]="hello";
    char s1[6];
    int i,n;
    for(i=0;s[i]!='\0';i++)
    {
      s1[i]=s[i];
    }
    for(i=0;i!=6;i++)
{
 printf("%c",s1[i]);
}
    return 0;
}
