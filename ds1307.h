#ifndef __DS1307_H__
#define __DS1307_H__
#include "main.h"
   void start_rtc(void);
   void stop_rtc(void);
	 void gui_rtc(unsigned char x);
	 unsigned char nhan_rtc(void);
	 char docdulieu(unsigned char diachi);
	 void ghi_dulieu_rtc(unsigned char diachi, unsigned char dulieu);
	 void ghivaoDS1307(void);
#endif