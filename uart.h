//uart.h

void uart_init()
{
	SCON = 0x50;
	TMOD = 	0x20;
	TH1 = TL1 = 253;
	TR1 = 1;
}

void uart_tx(unsigned char byte)
{
	SBUF = byte;
	while(TI==0);
	TI = 0;
}

unsigned char uart_rx()
{
	while(RI==0);
	RI=0;
	return SBUF;
}
void uart_string(char *s)
{
	while(*s)
	uart_tx(*s++);
}

void uart_integer12(unsigned int num)
{
unsigned char a[4]={0};
char i=0;
if(num<0)
{
	uart_tx('-');
	num = -num;
}
if(num ==0)
{
uart_tx('0');
return;
}

while(num)
{
a[i++]=num%10+48;
num=num/10;
}

while(--i>=0)
uart_tx(a[i]);

}

void uart_day(unsigned char day)
{

 switch(day)
	{
	 case 1:uart_string("SUN");
	 		break;
	 case 2:uart_string("MON");
	 		break;
	 case 3:uart_string("TUE");
	 		break;
	 case 4:uart_string("WED");
	 		break;
	 case 5:uart_string("THUR");
	 		break;
	 case 6:uart_string("FRI");
	 		break;
	 case 7:uart_string("SAT");
	 		break;
	}
}