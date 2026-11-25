#include<stdio.h>
int main()
{
    char string[20];
    FILE *fp;
    fp=fopen("file.txt","r");
    fgets(string,20,fp);
    printf("The string is: %s",string);
    fclose(fp);
    return 0;
}
