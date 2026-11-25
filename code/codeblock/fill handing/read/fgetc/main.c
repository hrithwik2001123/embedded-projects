#include <stdio.h>
#include <stdlib.h>

int main()
{


FILE*ptr=NULL;
ptr=fopen("D:/codeblock/fill handing/write/fputc/new.text","r");
char ch;
ch=fgetc(ptr);

printf("%c",ch);
fclose(ptr);

FILE*fptr=NULL;
fptr=fopen("D:/codeblock/fill handing/write/fputs/new-2.text","r");

while(!feof(fptr))
{
      char ch2=fgetc(fptr);
    printf("%c",ch2);
}



fclose(ptr);
FILE*fptr2=NULL;
fptr2=fopen("D:/codeblock/fill handing/read/fgets/main.c","r");
while(!feof(fptr))
{
      char ch3=fgetc(fptr2);
    printf("%c",ch3);
}
}
