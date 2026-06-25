#include "ds1307.h"
unsigned char *rtc[]={"0","1","2","3","4","5","6","7","8","9"};
unsigned char *day[]={"CNhat","Thu 2","Thu 3","Thu 4","Thu 5","Thu 6","Thu 7"};
unsigned char giatrikhoitao_rtc[9];
void start_rtc(void) 
{                
	scl=1;
	sda=1;  
	_nop_();
	_nop_();
	sda=0;
	scl=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void stop_rtc(void)             
{               
	sda=0;
	scl=1;
	_nop_();
	_nop_();
	sda=1;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void gui_rtc(unsigned char x)
{   
	unsigned char i;    
	for(i=0;i<8;i++)
	{
		sda=(x&0x80)? 1:0;  
		scl=1;                      
	   _nop_();
	   _nop_();           
		scl=0;
		x<<=1;              
	}
	sda = 1;
	scl=1;             
	_nop_();
	_nop_();
	scl=0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
unsigned char nhan_rtc(void)
{   
	unsigned char Data=0,i; 
	sda = 1;  
	for(i=0;i<8;i++) 
	{
		scl=1; 
		Data<<=1;
		if(sda) Data|=1; 
		scl=0;
    }   
	sda=1;  
	scl=1; 
	_nop_();
	scl=0;
	_nop_();
	return Data;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
char docdulieu(unsigned char diachi)
{       
	unsigned char Data;
	start_rtc();
	gui_rtc(0xd0);
	gui_rtc(diachi);
	start_rtc();
	gui_rtc(0xd1); 
	Data=nhan_rtc();    
	stop_rtc();
	return Data;
}

void ghi_dulieu_rtc(unsigned char diachi, unsigned char dulieu)
{
	start_rtc();
	gui_rtc(0xd0);
	gui_rtc(diachi);
	gui_rtc(dulieu);
	stop_rtc();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void ghivaoDS1307(void)
{
	unsigned char t;
	for(t=0;t<9;t++)
	{
		start_rtc();
		gui_rtc(0xd0);
		gui_rtc(t);
		gui_rtc(giatrikhoitao_rtc[t]);
		stop_rtc();
	}
}