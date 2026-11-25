#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a,i,o,u,A;
    printf("enter a character");
    scanf("%c",&A);
    switch(A){
case 'a': printf("a is vowel");
        break;
case 'i': printf("i is vowel");
        break;
case 'o': printf("o is vowel");
        break;
case 'u': printf("u is vowel");
        break;
default: printf(" alphabet");
         break;

    }
    return 0;
}
