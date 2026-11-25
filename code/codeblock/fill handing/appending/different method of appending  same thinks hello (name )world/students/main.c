#include <stdio.h>
#include <stdlib.h>
struct student
{
    int rollno;
    char name[20];
    float mark;

}s1={10,"hrithwik",10.32};
int main()
{

    printf("%d\n%s\n%.2f",s1.rollno,s1.name,s1.mark);
    return 0;
}
