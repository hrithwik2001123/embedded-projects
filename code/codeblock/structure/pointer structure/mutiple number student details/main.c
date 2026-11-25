#include <stdio.h>
#include <stdlib.h>

struct employ {
    char name[20];
    int admite_number;
    int salary;
};

void function(struct employ s[],int i) {
    struct employ *ptr = &s[i];
    printf("Name: %s\nAdmit Number: %d\nSalary: %d\n", ptr->name, ptr->admite_number, ptr->salary);
}

int main() {
    printf("Enter the number of employees: ");
    int n;
    scanf("%d", &n);

    struct employ s[n];

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
    function(&s,i);
}
    return 0;
}
