#include<lpc214x.h>
#define PCLK 60000000 //peripheral clock frequency
						int i;
						char ch;
					const	char *message ="enter your name:";// Fixed pointer declaration
void PLL_in()
				{
						  PLL0CON = 0x01;    // Enable PLL
							PLL0CFG = 0x24;   // Set multiplier and divider values
							PLL0FEED = 0xAA;  // Feed sequence
							PLL0FEED = 0x55;
							while (!(PLL0STAT & (1 << 10)));  // Wait for PLL lock
							PLL0CON = 0x03;   // Connect PLL
							PLL0FEED = 0xAA; // Feed sequence
							PLL0FEED = 0x55;
							VPBDIV = 0x01;  // Set PCLK = CCLK
				}
				
uart_in(unsigned int baudrate)
				{
						unsigned int DL;  //configure p0.0and p0.1 as TXD0 and RXD0
						PINSEL0=0X05 ;     //ENABLE DLAB ,SET 8-BIT WORD LENGTH
						U0LCR=0X83;
						DL=(PCLK/(16*baudrate));
						U0DLM=DL>>8;   //SET HIGH BYTE OF DIVISOR 
						U0DLL=DL&0XFF; //SET LOW BYTE OF DIVISOR
						U0LCR=0X03;    //DISABLE DLAB
				}
				
char rec()
				{
						while(!(U0LSR&(1<<0))); // WAIY until data is available
						return U0RBR;           //return received character
						
				}
void trasmitter( const char *c)// Fixed function signature to match usage
				{
					while(*c)
						{
					while(!(U0LSR&(1<<5)));// Wait until THR is empty
            U0THR=*c++; // Transmit character
				   for(i=0;i<10000;i++); // Small delay
					
				    }
			  }
				
int main ()
				{
						PLL_in();
						uart_in(9600);
					trasmitter(message);
				while(1)
				{
					
						ch=rec();
					trasmitter(&ch); //  received character sending 
						
				}
			}
			