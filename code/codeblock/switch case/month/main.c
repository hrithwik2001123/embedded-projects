#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter days\n1.28\n2.30\n3.31\n");
    scanf("%d",&a);
    switch(a){
    case 1: printf("february");
            break;
    case 2: printf("april\njune\nseptember\nnovember");
            break;
    case 3: printf("january\nmarch\nmay\njuly\naugust\noctober\ndecember\n");
            break;

    default:printf("not avilable");
    break;
    }
    return 0;
}
