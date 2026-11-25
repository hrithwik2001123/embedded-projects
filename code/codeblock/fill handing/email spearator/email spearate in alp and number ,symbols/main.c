#include <stdio.h>
#include <stdlib.h>

int main()
{
 char s[50];
 int i=0;
 printf("enter a email");
 scanf("%s",s);
 FILE*fptr=fopen("mail.text","w");
 if(fptr==NULL)
 {
     printf("error");
     return 1;
 }
 fputs(s,fptr);
 fclose(fptr);
 FILE*fptr1=fopen("alphabets.text","w");
 FILE*fptr2=fopen("number.text","w");
 FILE*fptr3=fopen("special.text","w");
   if(fptr1==NULL||fptr2==NULL||fptr3==NULL)
 {
     printf("error");
     return 1;
 }
 for(i=0;s[i]!='\0';i++)
 {
if (s[i]>=65&&s[i]<=90){
       fputc(s[i],fptr1);
    }
    else if (s[i]>=97&&s[i]<=122){
       fputc(s[i],fptr1);
    }
    else if (s[i]>=48&&s[i]<=57){
    fputc(s[i],fptr2);
    }
    else{
       fputc(s[i],fptr3);
    }
 }
 fclose(fptr1);
  fclose(fptr2);
 fclose(fptr3);
return 0;
}
