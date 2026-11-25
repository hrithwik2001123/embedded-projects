#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,flag=0,comp;
    char c[100];
    printf("enter a your name   ");
    scanf("%s",c);
    char a[100]="hi david hello hrithwik";
    char b[100];
    for(i=0,j=0;a[i]!='\0';i++,j++)
    {
        b[j]=a[i];
        if(b[j]==' ')
        {
            b[j]='\0';
            j=-1;
        comp=strcmp(b,c);
        if(comp==0){
            flag=1;
            break;
        }
        }
    }
    b[j]='\0';
    comp=strcmp(b,c);
    if(comp==0)
    {
        flag=1;
    }
    if(flag==1)
    {
        printf("word found");
    }
    else{
        printf("word not found");
    }

}
