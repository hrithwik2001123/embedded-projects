#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,j,sp;
  for(i=0;i<6;i++)
  {
    for(sp=0;sp<=6-i;sp++)
    {
        printf("  ");
    }
      for(j=1;j<=i;j++)
      {
          printf(" * ");
      }
      printf("\n");
  }
    return 0;
}
