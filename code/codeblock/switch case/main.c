#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    printf("1.tea\n2.rice\n3.butter chicken\n4.noodles entered only the number ");
    scanf("%d",&c);
    switch(c){
    case 1:printf("you entered tea");
    break;
    case 2:printf("you entered rice");
    break;
    case 3:printf("you entered butter chicken");
    break;
    case 4:printf("you entered noodles");
    break ;
    default:printf("not avilable");
    break;
    }
    return 0;
}
