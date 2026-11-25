#include <stdio.h>
#include <stdlib.h>
void add(int a, int b)
 {
     printf("%d", a + b);
      }
void dif(int a, int b)
 {
     printf("%d", a - b);
      }
void display(void(*fptr)(int ,int )){
    int a=5,b=6;
    (*fptr)(a,b);
    }
int main()
{


    display(dif);
}
