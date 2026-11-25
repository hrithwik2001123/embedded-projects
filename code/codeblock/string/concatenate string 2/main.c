#include <stdio.h>

int main() {
    char s[50];
    char s1[40];
    int i, ls = 0, ls1 = 0,j;
    printf("Enter the first string  ");
    for(i = 0;; i++) {
        scanf("%c", &s[i]);
        if(s[i] == '\n') {
            break;
        }
        ls++;
    }
s[ls] = '\0';
    printf(" second string ");
    for(i = 0; ; i++) {
        scanf("%c", &s1[i]);
        if(s1[i] == '\n') {
            break;
        }
            ls1++;
    }
    s[ls] = '\0';
    for(i=ls,j=0;j<ls1;i++,j++)
    {
        s[i]=s1[j];
    }
    s[i] = '\0';
       printf("%s",s);
}
