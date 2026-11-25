#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, rem, rev = 0,i,temp ,zero=0;
    printf("Enter a number: ");
    scanf("%d", &a);
    while (a > 0) {
        rem = a % 10;
        rev = rev * 10 + rem;
        a /= 10;
    }
    for(i=0;rev>0;i++){
        rem=rev%10;
        rev=rev/10;
        switch (rem) {
            case 0: printf("zero ");
                    break;
            case 1: printf("one ");
                    break;
            case 2: printf("two ");
                    break;
            case 3: printf("three ");
                    break;
            case 4: printf("four ");
                    break;
            case 5: printf("five ");
                    break;
            case 6: printf("six ");
                    break;
            case 7: printf("seven ");
                    break;
            case 8: printf("eight ");
                    break;
            case 9: printf("nine ");
                    break;
        }
    }
       temp = a;
    while (temp % 10 == 0) {
        zero++;
        temp /= 10;
    }
    for(i=0;i<=zero;i++){
        printf("zero");
    }

    return 0;
}
