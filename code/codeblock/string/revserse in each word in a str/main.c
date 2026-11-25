#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,flag=0,comp;
    int count=0;
    char a[100]="hi hello ";
    char b[100];
    for(i=0,j=0;a[i]!='\0';i++,j++)
    {
        b[j]=a[i];
         count++;
        if(b[j]==' ')
        {
            b[j]='\0';
            for(j=count;j>=0;j--)
            {
                printf("%c",b[j]);

            }
            j=-1;
            count=0;
             printf(" ");
        }

        }
    }
