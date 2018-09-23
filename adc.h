/* adc.h */

sbit clk	=	P1^0;
sbit dout	= 	P1^1;
sbit din	=	P1^2;
sbit cs		= 	P1^3;

unsigned int read_adc0(void)
{
 	unsigned int temp=0;
	char i;
	cs=0;						   	//start communication

	clk=0; din=1; clk=1;		   	//start bit 
	clk=0; din=1; clk=1;			//single ended mode

	clk=0; din=1; clk=1;			// d2 is don't care

	clk=0; din=0; clk=1;			//d1 
	clk=0; din=0; clk=1;			//d0 and start sampling

	clk=0; din=1; clk=1;			// tsmaple
	clk=0; din=1; clk=1;			// null bit

	for(i=11; i>=0; i--)			// 12 bit data reading
	{
		clk=0;
		
		if(dout==1)
		temp = temp | (1<<i);

		clk=1;
	}

	cs=1;							// stop communication
									
	return temp;					// returning the data

}
 unsigned int read_adc2(void)
{
 	unsigned int temp=0;
	char i;
	cs=0;						   	//start communication

	clk=0; din=1; clk=1;		   	//start bit 
	clk=0; din=1; clk=1;			//single ended mode

	clk=0; din=1; clk=1;			// d2 is don't care

	clk=0; din=1; clk=1;			//d1 
	clk=0; din=0; clk=1;			//d0 and start sampling

	clk=0; din=1; clk=1;			// tsmaple
	clk=0; din=1; clk=1;			// null bit

	for(i=11; i>=0; i--)			// 12 bit data reading
	{
		clk=0;
		
		if(dout==1)
		temp = temp | (1<<i);

		clk=1;
	}

	cs=1;							// stop communication
									
	return temp;					// returning the data

}

unsigned int hex_dec(unsigned int temp)
{
	unsigned int value=0;
	char i;
	 
	for(i=11;i>=0;i--)
	if(temp & (1<<i))
	value= value +	(1<<i);

	return value;
}
