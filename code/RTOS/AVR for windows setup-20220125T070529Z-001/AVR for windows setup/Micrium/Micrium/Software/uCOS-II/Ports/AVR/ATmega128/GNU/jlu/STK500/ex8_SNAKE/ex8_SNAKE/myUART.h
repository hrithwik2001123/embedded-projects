/**********************************************************************

File-name: myUART.h
Target: ATMega128
Clock frequency: 16Mhz
Author: Saurabh Gandhi
Description: UART config, transmit, receive (assuming Fclk=16Mhz)

************************************************************************/

//UART configuration (UART 1 of ATMega128) Configure UART baud rate and other parameters
unsigned int UART_config(unsigned long int baudrate)
{
	int cnt;
	unsigned int UBRR_set=0, UBRR_low, UBRR_high;
	unsigned long int arr1[]={2400,4800,9600,14400,19200,28800,38400,57600,76800,115200};
	unsigned int arr2[]={415,207,103,68,51,34,25,16,12,8};
	
	UCSR1B = 0x18; //polled transmission, polled reception, 8-bits
	UCSR1C = 0x06; //1 stop bit, no parity
	
	for(cnt=0;cnt<10;cnt++)
	{
		if(arr1[cnt]==baudrate)
			UBRR_set=arr2[cnt];
	}
	UBRR_high=UBRR_set/256;
	UBRR_low=UBRR_set%256;
	
	UBRR1L=(unsigned char)UBRR_low;
	UBRR1H=(unsigned char)UBRR_high;
	return UBRR_low;
	
}

/* Transmit a character on hyperterminal */
void UART_Transmit_char( unsigned char data )
{
	UDR1=data;
	/* Wait for empty transmit buffer */
	while ((UCSR1A & 0x60)!=0x60);
}

/* Transmit a string on hyperterminal */
void UART_Transmit_string(unsigned char *str )
{
	while(*str){
		UART_Transmit_char(*str++);
		}
}

/* transmit a number (integer) on hyperterminal */
void UART_Transmit_num(unsigned char num)
{
	unsigned char num1,num2;
	num1=(num%10);
	num=num/10;
	num2=(num%10);
	num=num/10;
	if(num)
		UART_Transmit_char(num+'0');
	if(num || num2)
		UART_Transmit_char(num2+'0');
	UART_Transmit_char(num1+'0');
	/* Wait for empty transmit buffer */
	while ((UCSR1A & 0x60)!=0x60);
}

/* receive a character from hyperterminal */
unsigned char UART_Receive( void )
{
	/* Wait for data to be received */
	while ((UCSR1A & 0x80)!=0x80);
	/* Get and return received data from buffer */
    return UDR1;
}
