#include <stdio.h>
#include <stdlib.h>
struct student {
char name[20];
int regnumber;
float mark;

};
int main()
{
    printf("enter how much student are in this class");
    int n;
    scanf("%d",&n);
    struct student s[n];
    for(i=0;i<n;i++)
    {
        struct student*ptr[n]=s[n];
        while(i!=n||i==n)
        {
            scanf("%c%d%f",ptr->name,&ptr->regnumber,&ptr->mark);
        }
    }
    return 0;
}
