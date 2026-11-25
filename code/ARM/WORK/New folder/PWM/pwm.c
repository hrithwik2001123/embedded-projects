#include <lpc214x.h>


void pll ()
		{
				PLL0CON=0X01;
				PLL0CFG=0X24;
				PLL0FEED=0XAA;
				PLL0FEED=0X55;
		while(!(PLL0STAT&(1<<10)));
				PLL0CON=0X03;
				PLL0FEED=0XAA;
				PLL0FEED=0X55;
				VPBDIV=0X01;
		}

int main ()
			{
				  PINSEL1=(0<<11)|(1<<10);
					PWMPCR = (0<<5); //Select Single Edge PWM - 
					PWMPR = 59999; // 1 micro-second resolution
					PWMMR0 = 10; // 10ms period duration
					//PWMMR5 = 7; // 0.5ms - pulse duration i.e width (Brigtness level)
					PWMMCR = (1<<1); // Reset PWMTC on PWMMR0 match
					PWMLER=(1<<5)|(1<<0);
					PWMPCR = (1<<13); // enable PWM output
					PWMTCR = (1<<1) ; //Reset PWM TC & PR
					//Now , the final moment - enable everything
					PWMTCR = (1<<0) | (1<<3); // enable counters and PWM Mode
					PWMMR5=1;
					PWMLER = (1<<5); // update MR0 and MR4	
 					
					while(1);
			}
