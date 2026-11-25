#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a,i,b=0,c=0,d=0,e=0,f=0,u=0,w=0,q=0,r=0,t=0,num;
    printf("enter a number input for count ");
    scanf("%d",&a);
    for(i=0;i<a;i++)
    {
        scanf("%d",&num);
        switch(num)
        {
            case 0:b++;
                   break;
            case 1:c++;
                   break;
            case 2:d++;
                   break;
            case 3:e++;
                   break;
            case 4:f++;
                   break;
            case 5:u++;
                   break;
            case 6:w++;
                   break;
            case 7:q++;
                   break;
            case 8:r++;
                   break;
            case 9:t++;
                   break;
            default:printf("more than 9 is invalide or alaphabet");
                           break;
        }

    }
    printf("\n0=%d\n1=%d\n2=%d\n3=%d\n4=%d\n5=%d\n6=%d\n7=%d\n8=%d\n9=%d",b,c,d,e,f,u,w,q,r,t);
    return 0;
}
