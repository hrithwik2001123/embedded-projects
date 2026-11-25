#include <stdio.h>
#include <stdlib.h>

struct employ {
    char name[20];
    int admite_number;
    int salary;
};

void function(struct employ s[], int i) {
    struct employ *ptr = &s[i];;

}


int main() {
    printf("Enter the number of employees: ");
    int n;
    scanf("%d", &n);

    struct employ s[n];
    FILE* ptr = NULL;
 ptr=fopen("more than one employ.text","w");
if (ptr==NULL)
{
    printf("error\n");
return 1;
}
    for (int i = 0; i < n; i++) {
        printf("Enter name: ");
        scanf("%s", s[i].name);

        printf("Enter admit number: ");
        scanf("%d", &s[i].admite_number);

        printf("Enter salary: ");
        scanf("%d", &s[i].salary);
    }
for ( int i=0;i<n;i++)
{
    function(&s, i);
    fprintf(ptr," name:%s\nadmite number:%d\nsalary:%dL\n",s[i].name,s[i].admite_number,s[i].salary);

}
fclose(ptr);
    return 0;
}
