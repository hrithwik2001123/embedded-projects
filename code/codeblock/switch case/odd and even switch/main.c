#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter a  number");
    scanf("%d",&a);
    switch(a%2){
    case 0:printf("you entered is even ");
                    break;
    case 1:printf("you entered is odd ");
                    break;
    }
    return 0;
}
