#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,b;
    printf("enter two numbers ");
    scanf("%d%d",&a,&b);
    switch(a>=b||b>=a){
    case ('a'>='b'): printf("enter %d is greater",a);
                break;
    case('a'<='b'):  printf("enter %d is greater",b);
                break;
    }
    return 0;
}
