#include <stdio.h>
#include <stdlib.h>
void display()
{
  static int x=2;
  x=x+1;
  printf("x=%d\n",x);
}
int main()
{
    display();
    display();
    display();
    return 0;
}
