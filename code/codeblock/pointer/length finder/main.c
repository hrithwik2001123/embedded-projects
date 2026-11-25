#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s[100];
    printf("enterr a string\n");
    scanf("%s",s);
    char*ptr=s;
    int i,count=0;
    for(i=0;*(ptr+i)!='\0';i++)
    {

        count++;

    }
    printf("length + %d",count);
    return 0;
}
