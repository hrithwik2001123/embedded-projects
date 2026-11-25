#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str1[20] = "Hello ";
    char str2[] = "World!";
   str1[20]=strcat(str1,str2);
    void*ptr=str1;
    printf("%s",*(char*)ptr);
    return 0;
}
