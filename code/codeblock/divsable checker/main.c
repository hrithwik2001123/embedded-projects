#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter a value");
    scanf("%d",&a);
    if (a%5==0&&11%a==0){
        printf("%d its divisible by both ",a);

    }else if (a%5==0){
        printf("%d its divisible by 5",a);
    }
    else if(a%11==0) {
    printf("%d is divisible by 11",a);
    }
    else{
        printf("its not divisible by both");
    }
    return 0;
}
