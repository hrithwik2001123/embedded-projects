#include <stdio.h>
#include <stdlib.h>
struct car {
char model [100];
int year;
float amount;

};
void v(struct car *ptr){
printf("car name :%s\nyear:%d\nAMount:%.2fL",ptr->model,ptr->year,ptr->amount);
}
int main()
{
    struct car c1={"Nissan patrol",1999,10.00};
    v(&c1);
    return 0;
}
