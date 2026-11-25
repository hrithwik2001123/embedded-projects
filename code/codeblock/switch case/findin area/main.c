#include <stdio.h>
#include <stdlib.h>

int main()
{
    float b,l,c,area;
    int a;
    printf("1.rectangle\n2.square\n3.cicle");
    scanf("%d",&a);
    switch(a){
    case 1: printf("enter two number");
            scanf("%f%f",&l,&b);
            area=l*b;
            printf(" you entered rectangle %f",area);
            break;
    case 2: printf("enter  number");
            scanf("%f",&c);
            area=c*c;
            printf("you square %f",area);
            break;
    case 3: printf("enter  number");
            scanf("%f",&c);
            area=3.14*c;
            printf("you cicle %f",area);
            break;

    default:printf("not avilable");
    break;
    }
    return 0;
}
