#include <stdio.h>
#include <stdlib.h>

int main()
{
     int a,rem,rev,b;
    printf("enter a number ");
    scanf("%d",&a);
    b=a;
    while(a>0)
    {
        rem=a%10;
        a=a/10;
        rev=rev*10+rem;
    }
    printf("%d",rev);
        if(rev==b){
            printf("\nenter is palindrome");
        }
        else{
            printf(" \nits not palindrome");
        }

    return 0;
}
