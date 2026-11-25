#include <stdio.h>
#include <stdlib.h>
int main()
{
int n;
    printf("enter much times");
    scanf("%d",&n);
    display(n);

}
void display(int n)
{
    if(n==5)
    {
        return;
    }
    printf("hello\n");
    display(n-1);
}
