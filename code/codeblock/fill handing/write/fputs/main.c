#include <stdio.h>
#include <stdlib.h>

int main()
{


FILE*ptr=NULL;
ptr=fopen("n2.text","w");
char ch[]="hello";
if (ptr==NULL)
{
    printf("error\n");

}
fputs(ch,ptr);
fclose(ptr);
}
