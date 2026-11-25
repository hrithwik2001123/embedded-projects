#include <stdio.h>
#include <stdlib.h>
   struct employ
    {
        char name [20];
        int admite_number ;
        int salary;
    } ;
int main()
{
 struct employ s1;
 struct employ*ptr=&s1;
 printf("enter a detail of employ name,admite number ,salary");
 scanf("%s%d%d",ptr->name,&ptr->admite_number,&ptr->salary);
  FILE* file_ptr = NULL;
file_ptr=fopen("employ.text","w");
if (file_ptr==NULL)
{
    printf("error\n");
return 1;
}
fprintf(file_ptr,"%s\n%d\n%d",ptr->name,ptr->admite_number,ptr->salary);
fclose(file_ptr);

    return 0;
}
