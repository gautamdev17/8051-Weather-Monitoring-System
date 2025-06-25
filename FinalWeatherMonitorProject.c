#include <reg51.h>
#include <lcdheader.h>
#include <i2c.h>
#include <mcp3204.h>

void func(unsigned char bcd)/* we print bcd value given by rtc,i.e, for seconds, 
	0x51 from rtc is 51 seconds*/
{
	//lets say we wanna print 51
	lcd_data((bcd>>4)+'0');//first digit, 5
	lcd_data((bcd&(0x0f))+'0');//second digit, 1
}

void main()
{
	lcd_init();//initializing lcd
	while(1)
	{
		func(i2c_slave_read(0xd0,0x02));//0x02 address is for hours
		lcd_str(":");
		func(i2c_slave_read(0xd0,0x01));//0x01 address is for minutes
		lcd_str(":");
		func(i2c_slave_read(0xd0,0x00));//0x00 address is for seconds
		lcd_cmd(0xc0);// cursor is set to second line of lcd
		lcd_str("Temperature: ");
		float_val(spi_adc_read(0,0));
		delay(1000);
    lcd_cmd(0x80);// cursor is set back to first line of lcd
	}
}
