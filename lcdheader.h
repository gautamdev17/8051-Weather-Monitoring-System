#include"delayheader.h"
#define lcd_d P2
#include <math.h>
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char *);
void float_val(float,int);
void lcd_num(int n);
void delay(int);


void lcd_init(void)
{
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0c);
	lcd_cmd(0x38);
	lcd_cmd(0x80);
	
}


void lcd_cmd(unsigned char c)
{
	lcd_d=c;
	rs=0;
	rw=0;
	en=1;
	delay(2);
	en=0;
}
	
void lcd_data(unsigned char c)
{
	lcd_d=c;
	rs=1;
	rw=0;
	en=1;
	delay(2);
	en=0;
	
}

void lcd_str(unsigned char *d)
{
	while(*d)
		lcd_data(*d++);
}

void float_val(float f,int p)// function to print floating point numbers with precision 'p'
{
	float temp;
	int n;
	n=f;
	lcd_num(n);
	lcd_data('.');
	temp=(f-n)*pow(10,p);
	n=temp;
	lcd_num(n);
	
}



void lcd_num(int n)
{
	int arr[5],i=0;
	if(n==0)
		lcd_data('0');
	else
	{
		if(n<0)
		{
			lcd_data('-');
			n=-n;
		}
		
		while(n>0)
		{
			arr[i++]=n%10;
			n=n/10;
		}
		
		for(--i;i>=0;i--)
		lcd_data(arr[i]+48);
		
		
	}
	
}
