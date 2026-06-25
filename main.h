#ifndef __MAIN_H__
#define __MAIN_H__

#include <AT89X51.H>
#include <INTRINS.H>
#include "port.h"
#include "lcd.h"
#include "ds1307.h"
#include "dht11.h"


extern unsigned char *rtc[];
extern unsigned char *day[];
extern unsigned char giatrikhoitao_rtc[9];
extern unsigned int dem_nhiet_do;
extern unsigned char I_RH, D_RH, I_Temp, D_Temp, CheckSum; 
extern bit dht_ready;

#endif