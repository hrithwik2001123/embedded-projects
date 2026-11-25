#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s1[10];
    char s2[10];
    printf("enter a string\n ");
    scanf("%s",s1);
    char*ptr1=s1;
    printf("enter a second string \n");
    scanf("%s",s2);
    char*ptr2=s2;
    int c=0;
    for(int i=0;s1[i]!='\0';i++)
    {
      c++;
    }
    int count=0,i,j;
    for(i=0,j=0;j<c,i<c;i++,j++){
    if(*(ptr1+i)==*(ptr2+j))
    {
        count++;
    }
    }
    if(count==c)
    {
        printf("enter string is same ");

    }
    else {
        printf("enter a string is not same ");
    }

    return 0;
}
