#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter a value");
    scanf("%d",&a);
    if (1<=a){
        printf("%d is postive ",a);

    }else if (a==0){
        printf("enter is zero");
    }
    else {
    printf("%d is nag",a);
    }
    return 0;
}
