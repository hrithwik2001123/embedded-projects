# include <lpc17xx.h>
	int i;
int main()
{
	
	LPC_PINCON->PINSEL0=0X00000000;
	LPC_GPIO0->FIODIR=0XFFFFFFFF;
	while(1){
		LPC_GPIO0->FIOSET=0XFFFFFFFF;
		for(i=0;i<=1000;i++);
		LPC_GPIO0->FIOCLR=0XFFFFFFFF;
			for(i=0;i<=1000;i++);
	}
}