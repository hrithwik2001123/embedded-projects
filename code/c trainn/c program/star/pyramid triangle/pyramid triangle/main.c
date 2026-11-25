#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num;
    printf("how steps you want in star\n");
    scanf("%d",&num);
    for(int i=0;i<=num;i++){

        for(int sp=num-i;sp>=0;sp--){
                printf("  ");
        }
            for(int j=0;j<=i;j++){
                printf(" *  ");
            }
            printf("\n");
        }


printf("\n");
printf("\n");

    //second
    for(int i=0;i<=num;i++){
        for(int sp=num-i;sp>=0;sp--){
            printf(" ");

        }
        for(int j=0;j<=i;j++){
            printf("*");

        }
        printf("\n");
    }
printf("\n");
printf("\n");
    //third

     for(int i=0;i<=num;i++){
        for(int j=0;j<=i;j++){
            printf("*");
        }
        printf("\n");
     }
printf("\n");
printf("\n");
     //forth
     for(int i=0;i<=num;i++){
        for(int j=num-i;j>=0;j--){
            printf("*");

        }
        printf("\n");
     }

     ///five
     for(int i=0; i<=num;i++){
        for(int sp=num-i;sp>=0;sp--){
            printf("  ");
        }
        for(int j=0;j<=i;j++){
           printf(" *  ");
        }
        printf("\n");
     }
  for(int i=0; i<=num;i++){
        for(int sp=0;sp<=i;sp++){
              printf("  ");
        }
        for(int j=num-i;j>=0;j--){
            printf(" *  ");
        }
        printf("\n");
     }
     ///six


}

