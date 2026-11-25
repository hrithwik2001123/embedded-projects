#include <stdio.h>

int main() {
    char s[50];
    char s1[10];
    int i, ls = 0, ls1 = 0;
    printf("Enter the first string (max 40 characters): ");
    for(i = 0; i < 40; i++) {
        scanf("%c", &s[i]);
        if(s[i] == '\n') {
            break;
        }
        ls++;
    }
    s[ls] = '\0';
    printf(" second string (max 10 characters): ");
    for(i = 0; i < 10; i++) {
        scanf("%c", &s1[i]);
        if(s1[i] == '\n') {
            break;
        }
        ls1++;
    }
    s1[ls1] = '\0';
    for(i = ls; i >= 0; i--) {
        s[i + ls1] = s[i];
    }
    for(i = 0; i < ls1; i++) {
        s[i] = s1[i];
    }
    printf("Modified string: ");
    for(i = 0; i < ls + ls1; i++) {
        printf("%c", s[i]);
    }
    printf("\n");

    return 0;
}
