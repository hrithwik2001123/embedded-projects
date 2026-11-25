#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[10];
    char s1[10];
    printf("enter string");
    scanf("%s",s);
    char*ptr=s;
    char*ptr1=s1;
    int i;
    for(i=0;i<10;i++)
    {
       *(ptr1+i)=*(ptr+i);

    }
    printf("the copying string   :%s",s1);
    return 0;
}
