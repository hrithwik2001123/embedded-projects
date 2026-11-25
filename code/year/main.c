#include <stdio.h>
#include <stdlib.h>

int main()
{
    int d,year,day,months;
    printf("enter a day");
     scanf("%d",&d);
    year=d/365;
    months=(d%365)/30;
    day=(d%365)%30;
    printf("year is %d\nday is %d\nday is %d",year,months,day);
    return 0;
}
