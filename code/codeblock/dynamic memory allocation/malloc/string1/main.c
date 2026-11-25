#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *ptr=malloc(50);
    char s[]="hello";
    char s2[100];
    strcpy(ptr,s);
    printf("%s\n",ptr);
    printf("address=%p\n",&ptr);
    int newsize;
    printf("enter the size of second string:\n");
    scanf("%d",&newsize);
    ptr=realloc(ptr,newsize);
    printf("enter the second string :");
    scanf("%s",&s2);
    printf("%s",s);
    printf("\naddress now=%p\n",&ptr);
    return 0;
}
