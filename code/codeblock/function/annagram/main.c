#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int annagram(char s[100],char s1[100])
{


    int i, count = 0,j;
    int len=strlen(s);
    int len1=strlen(s1);

 if (len!=len1)
 {
    printf("its not a annagram because the len is not equal ");
 }

printf("lenth is equal\n");
//int used[100] = {0};
    for(i=0;s[i]!='\0';i++)
    {
        for(j=0;s1[j]!='\0';j++)
        {
       // if (s[i] == s1[j]&&used[j]==0)
       if (s[i] == s1[j])
        {
            count++;
          //used[j]=1;
          s[i]=0;
          //break;
        }
    }
    }
     if (count == len)
       {
        printf("The annagram\n");
      }else{
        printf("The not  annagram\n");
    }
return 0;
}

int main()
{
    char s[100];
    char s1[100] ;
    printf("enter a words ");
    scanf("%s",s );
    printf("enter a another one ");
    scanf("%s",s1);
    annagram(s,s1);

}
