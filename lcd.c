#include "lcd.h"
void busy()
{
	D7=1;
	rs=0;
	rw=1;
	while(D7!=0)
	{
		en=0;
		en=1;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void ghilenhLCD(unsigned char x)
{
	busy();
	congLCD=x;  
	rs=0; 
	rw=0; 
	en=1;  
	en=0;   
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void khoitaoLCD(void)
{
	ghilenhLCD(0X38);       
	ghilenhLCD(0X0C);       
	ghilenhLCD(0X01);       
	ghilenhLCD(0X06);       
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void ghi_kytu(unsigned char value)
{
	busy();
	congLCD=value;
	rs=1;
	rw=0;
	en=1;
	en=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void ghi_chuoi(unsigned char *string)
{
	unsigned char i;
	for(i=0;string[i]!='\0';i++)
		ghi_kytu(string[i]);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void ghiso(unsigned char a)
{
	unsigned char i;
	if(a > 99) a = 99;
	
	i=a/10;
	ghi_chuoi(rtc[i]);
	i=a%10;
	ghi_chuoi(rtc[i]);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void hienthi_dulieu_rtc(unsigned char x)
{
	unsigned char temp;
	temp = x/16;
	ghi_chuoi(rtc[temp]);
	temp = x%16;
	ghi_chuoi(rtc[temp]);
}