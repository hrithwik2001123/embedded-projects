#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter a value to check");
    do{
        scanf("%d",&a);
        if (a%2==0){
            printf("%d even number",a);
        }
        else{
            printf("%d odd number",a);
        }
    }
    while(0);
    {

    }
    return 0;
}
