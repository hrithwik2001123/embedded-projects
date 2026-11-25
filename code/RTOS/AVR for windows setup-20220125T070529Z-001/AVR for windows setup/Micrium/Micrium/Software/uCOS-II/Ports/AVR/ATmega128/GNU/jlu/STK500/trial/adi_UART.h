 /* Receive string : argument is the string name (pointer).  */
 void uart_init(void);
char rx_char(void);
void tx_char(char data);
void rx_strng( char *strptr );
void tx_num( int data );

 char rx_char(void)
  {
  	//wait until recieve flag is '0'
  	while(1)
  	{
  		if(UCSR1A &(1<<7))
  		break;
  	}
  	return UDR1;
   }
 void rx_strng( char *strptr )
    {	
    	int i=0;
    	while(1)
    	{
    		*strptr = rx_char() ;
    		if(*strptr == 0x0d )
    			break;
    		strptr++;
    		i++;
    	}
       *strptr='\0';	
      
     }
     
 /* Transmit string : argument is the string name (pointer).  */
 
    void tx_strng( char *strptr)
  {
  	while(*strptr != '\0')
  	{
  		tx_char(*strptr);
  		strptr++;
  	}
  }
  
 /* receive character : returns UDRn  */
 
 
   
 /* Transmit character : Argument is the character to be transmitted.  */
 
   void tx_char(char data)
  {
  	//wait till UDR is empty
  	while(1)
  	{
  		if(UCSR1A &(1<<5))
  		break;
  	}
  	UDR1 = data;
  }
  
 /* UART initialization code for 9600 baud, 8 data bits, 1 stop bit, no parity.  */
 
  	void uart_init(void)
  {
  //set the baud rate
  //8 data bits, no parity, 9600 baud rate
  	UBRR1L = 103;
  	UBRR1H = 0;
  	UCSR1A = 0x00;
  	UCSR1B = 0x18;
  	UCSR1C = 0x06;
  }
  
  /* Transmit decimal number : argument is the number to be transmitted.  */
    void tx_num( int data )
   {
   		int i,rem[10]={0},num1;
   		 num1 = data;
   		  for(i=0;num1>0;i++)
   		{
   			rem[i] = num1 % 10;
   		//	a = rem[i] + 48 ;
   		//	transmit(a);
  	   		num1=num1/10;
   		 }
   		 i--;
   		 while(i>=0)
   		 {
   		  tx_char(rem[i]+48);
   		     		  i--;
   		  }
   }
   
   /* Receive decimal number : returns the decimal number received. */
      unsigned int rx_num(void)
   {  		
   		unsigned int num[10]={0},temp=1,number=0;
   		volatile int i,j,k,m;
	  i=0;
	  while((num[i-1]+48) != 0x0d)
	  {
	  	num[i] = (rx_char()-48) ;
	  	i++;
	  }
	  i=i-2;	k=i;	m=i;
 	for(j=0;j<=m;j++)
		{
		temp = 1;
		  for(i=(k-1);i>=0;i--)
		  {
		  	temp = temp * 10 ;
		  }
		  number += temp *num[j] ;
		  k--;
		}
     	return number ;
    }
    
