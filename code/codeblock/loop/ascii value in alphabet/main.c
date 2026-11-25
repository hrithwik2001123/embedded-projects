#include <stdio.h>
#include <stdlib.h>

int main()
{
    char c;
    printf("enter a alaphabet ");
    scanf("%c",&c);
    if (c>=65&&c<=90){
        printf("you entered in A-Z");
    }
    else if (c>=97&&c<=122){
        printf("you entered in  a-z");
    }
    else if (c>=48&&c<=57){
    printf("entered is number");
    }
    else{
        printf("special symbols");
    }
    return 0;
}
