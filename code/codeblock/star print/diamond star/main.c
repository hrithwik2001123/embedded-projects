
#include <stdio.h>
int main()
{
	int n,space = n - 1;
	printf("enter a how much row ");
scanf("%d",&n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < space; j++)
			printf(" ");
		for (int j = 0; j <= i; j++)
			printf("* ");

		printf("\n");
		space--;
	}
	space = 1;
	for (int i = n; i > 0; i--)
	{
		for (int j = 0; j < space; j++)
			printf(" ");
		for (int j = 0; j < i; j++)
			printf("* ");

		printf("\n");
		space++;
	}

}


