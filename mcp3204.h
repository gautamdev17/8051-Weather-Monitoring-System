sbit _cs=P1^6;
sbit mosi=P1^4;
sbit miso=P1^5;
sbit clk=P1^3;
/* here since we dont have spi hardware included in 8051 mcu, we use bitbanging
by controlling it by software,so we dont choose over the 4 modes, the software control
is the mode
*/
float spi_adc_read(bit d1,bit d0)
{
	unsigned int adc_val = 0;
	char j;
	_cs=0;//initiating communication, _cs is active-low
	
	clk=0;mosi=1;clk=1;//when cs=0 and mosi=1, clk=1  it constitute a start bit
	
	clk=0;mosi=1;clk=1;//singled ended input mode
	clk=0;clk=1;//d2 is in don't care in MCP3204
	clk=0;mosi=d1;clk=1;//d1 bit
	clk=0;mosi=d0;clk=1;//d0 bit
	clk=0;clk=1;//sample
	clk=0;clk=1;//null bit
	
	/**read 12 bit digital code**/
	for(j=11;j>=0;j--)
	{
		clk=0;
		if(miso)
			adc_val|=(1<<j);
		clk=1;
		
		
	}
		
	_cs=1;//communication stop
	return((adc_val*5.0)/4096);
}
