#include <stdio.h>
#include <stdlib.h>
struct student
{
    int rollno;
    char name[20];
    float mark;

}s1,s2;
int main()
{


        printf("your order to enter like e.g:rollno name mark ");
        scanf("%d",&s1.rollno);
        scanf("%s",s1.name);
        scanf("%f",&s1.mark);
        printf("second details");
        scanf("%d",&s2.rollno);
        scanf("%s",s2.name);
        scanf("%f",&s2.mark);

       printf("\n%d\n%s\n%.2f\n",s1.rollno,s1.name,s1.mark);
         printf("\n%d\n%s\n%.2f",s2.rollno,s2.name,s2.mark);
    return 0;
}
