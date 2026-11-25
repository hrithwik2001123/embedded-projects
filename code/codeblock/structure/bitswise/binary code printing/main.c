#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,n1;
    printf("enter a number ");
    scanf("%d",&n);
     printf("how much bit:");
       scanf("%d",&n1);
    printf("the binary of this :");
     for (int i = n1-1;i>=0;i--) {
        int bit =((n>>i)&1);
        printf("%d", bit);
    }
}

