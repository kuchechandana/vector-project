//lcd8bit.h

sfr  LCD = 0x80;
sbit RS = P3^4;
sbit RW = P3^5;
sbit EN = P3^6;

void lcd_cmd(unsigned char cmd)
{
	LCD = cmd;
	RS = 0;
	RW = 0;
	EN = 1;
	delay_ms(2);
	EN = 0;
}

void lcd_data(unsigned char ch)
{
	LCD = ch;
	RS = 1;
	RW = 0;
	EN = 1;
	delay_ms(2);
	EN = 0;
}

void lcd_init()
{
	lcd_cmd(0x2);
	lcd_cmd(0x38);
	lcd_cmd(0xE);
	lcd_cmd(0x6);
	lcd_cmd(0x1);
}
	
void lcd_string(char *s)
{
	while(*s)
		lcd_data(*s++);
}

void lcd_day(unsigned char day)
{

 switch(day)
	{
	 case 1:lcd_string("SUN");
	 		break;
	 case 2:lcd_string("MON");
	 		break;
	 case 3:lcd_string("TUE");
	 		break;
	 case 4:lcd_string("WED");
	 		break;
	 case 5:lcd_string("THU");
	 		break;
	 case 6:lcd_string("FRI");
	 		break;
	 case 7:lcd_string("SAT");
	 		break;
	}
}


void lcd_integer(unsigned int temp)
{
lcd_data(temp/10+48);
lcd_data(temp%10+48);
}


void lcd_hex(unsigned int temp)
{
lcd_data(temp/16+48);
lcd_data(temp%16+48);
}

void lcd_integer12(unsigned int num)
{
unsigned char a[4]={0};
char i=0;
if(num<0)
{
	lcd_data('-');
	num = -num;
}
if(num ==0)
{
lcd_data('0');
return;
}
while(num)
{
a[i++]=num%10+48;
num=num/10;
}

while(--i>=0)
lcd_data(a[i]);

}