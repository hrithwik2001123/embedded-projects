#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter a number to check even or odd");
    scanf("%d",&a);
    if(a%2==0&&a!=0){
        printf("its even");

    }
    else if(a==0) {
            printf("its zero");

    }
    else{
        printf("odd");
    }
    return 0;
}
