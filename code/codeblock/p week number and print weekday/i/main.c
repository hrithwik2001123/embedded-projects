#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a;
    printf("enter the a number its in a week 1to7");
    scanf("%d",&a);
    if(a==1){
        printf("sun");

    }
    else if(a==2) {
            printf("mon");

    }
    else if(a==3) {
            printf("tue");

    }
    else if(a==4) {
            printf("web");

    }
    else if(a==5) {
            printf("thu");

    }
    else if(a==6) {
            printf("fri");

    }
    else if(a==7) {
            printf("sat");

    }
    else{
        printf("error");
    }
}
