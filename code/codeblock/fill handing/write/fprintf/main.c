#include <stdio.h>
#include <stdlib.h>

int main()
{


FILE*ptr=NULL;
ptr=fopen("new-3.text","w");
if (ptr==NULL)
{
    printf("error\n");

}
fprintf(ptr,"%d\n%c\n%f",5,'a',3.14);
fclose(ptr);
}
