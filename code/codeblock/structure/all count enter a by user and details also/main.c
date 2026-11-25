#include <stdio.h>
#include <stdlib.h>
struct student
{
    int rollno;
    char name[20];
    float mark;

};
int main()
{

    int n;
          printf("enter how many students you need");
          scanf("%d",&n);
            struct student s[n];
           printf("your order to enter like e.g:rollno name mark ");
          for (int i=0;i<n;i++){
        scanf("%d",&s[i].rollno);
        scanf("%s",s[i].name);
        scanf("%f",&s[i].mark);
        printf("enter a %d person",i);

          }

        for(int i=0;i<n;i++)
        {
           printf("\n%d\n%s\n%.2f\n",s[i].rollno,s[i].name,s[i].mark);
           printf("print a %d person",i);
        }
    return 0;
}
