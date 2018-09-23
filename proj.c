#include<reg51.h>
#include"delay.h"
#include"uart.h"
#include"lcd8bit.h" 
#include"i2c.h"
#include"i2c_device.h"
#include"adc.h"

void main()
{
	unsigned char temp,temp1,day,date,month,year;
	unsigned int temp2=0,value=0;

	lcd_init();
	
	uart_init();
													//setting RTC time 11:59:55

	i2c_device_write(0xD0,0x00,0x55);				//set seconds
	i2c_device_write(0xD0,0x01,0x59);				//set minutes
	i2c_device_write(0xD0,0x02,0x71);				//set hours
	i2c_device_write(0xD0,0x03,0x07);				//set day
	i2c_device_write(0xD0,0x04,0x31);				//set date
	i2c_device_write(0xD0,0x05,0x03);				//set month
	i2c_device_write(0xD0,0x06,0x08);				//set year



	while(1)
	{
		temp = uart_rx();
		if(temp == '1')
		{
		temp1=i2c_device_read(0xD0,0x02);				//read hour
		uart_string("\n\r");							//to display time on the same place
		uart_tx((temp1&0x1f)/16+48);
		uart_tx((temp1&0x1f)%16+48);
		uart_tx(':');
		lcd_cmd(0x80);									//to display time on the same place
		lcd_data((temp1&0x1f)/16+48);
		lcd_data((temp1&0x1f)%16+48);
		lcd_data(':');

		temp=i2c_device_read(0xD0,0x01);				//read min
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
		uart_tx(':');
		lcd_hex(temp);
		lcd_data(':');


		temp=i2c_device_read(0xD0,0x00);				//read hour
		uart_tx(temp/16+48);
		uart_tx(temp%16+48);
		lcd_hex(temp);

		lcd_data(' ');
		uart_tx(' ');
		
		if(temp1&(1<<5))
		{
			uart_string("PM");
			lcd_string("PM");
		}
		else
		{	
			uart_string("AM");
			lcd_string("AM");
		}
	
		day=i2c_device_read(0xD0,0x03);	 				//read day
		uart_tx(' ');
		uart_day(day);
		
		lcd_data(' ');
		lcd_day(day);

		date=i2c_device_read(0xD0,0x04);	   		//read date
		uart_tx(' ');		   	
		uart_tx(date/16+48);						  	
		uart_tx(date%16+48);
	
		month=i2c_device_read(0xD0,0x05);				//read month
		uart_tx('/');
		uart_tx(month/16+48);
		uart_tx(month%16+48);
	
		year=i2c_device_read(0xD0,0x06);			  	//read year
		uart_tx('/');
		uart_tx(year/16+48);
		uart_tx(year%16+48);

	   /*read the data from ch0 (potentiometer) */

		lcd_cmd(0xC0);
		uart_string("\n\r");
		temp2=read_adc0();
		value=hex_dec(temp2);
		lcd_string("CH0:");
		lcd_integer12(value);
		uart_string("CH0:");
		uart_integer12(value);
	

		/*read the data from ch2 (LDR) */

		temp2=read_adc2();
		value=hex_dec(temp2);
		lcd_string("CH2:");
		lcd_integer12(value);
		uart_string("CH2:");
		uart_integer12(value);

		delay_ms(1000);

		}	
	}

}