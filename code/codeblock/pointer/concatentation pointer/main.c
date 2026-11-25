#include <stdio.h>
#include <stdlib.h>

int main()
{
  char s1[100],s2[100];
  printf("enter a concatentation  string ");
  scanf("%s",s1);
  printf("enter the another");
  scanf("%s",s2);
  char *ptr1=s1;
  char*ptr2=s2;
  int i,j,count=0;
  for(i=0;*(ptr1+i)!='\0';i++)
  {
      count++;
  }
  s1[count]=' ';
  for(i=count+1,j=0;*(ptr2+j)!='\0';j++,i++)
  {
      *(ptr1+i)=*(ptr2+j);
  }
  printf("the compining string   :%s",s1);
}
