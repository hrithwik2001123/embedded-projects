#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    float b;
    char c;
    printf("enter a different value like char float and int ");
    scanf(" %c%f%d",&a,&b,&c);
    printf("char is %d\n",sizeof(c));
    printf("float is %d\n",sizeof(b));
    printf("int is %d\n",sizeof(a));
    return 0;
}
