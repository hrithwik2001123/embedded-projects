#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,i;
    printf ("ENTER A THE SIZE\n");
    scanf("%d",&n);
   int *ptr=(int*)malloc(n*sizeof(int));
   if(ptr==NULL)
   {
       printf("memory not allocated\n");
       exit (0);
   }
   for(i=0;i<n;i++)
   {
       scanf("%d",&ptr[i]);
   }
   for(i=0;i<n;i++)
   {
       printf("%d\n",ptr[i]);
   }
    free(ptr);
}
