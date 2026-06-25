#ifndef __DHT11_H__
#define __DHT11_H__
#include "main.h"
void Delay_10us();
void delay_request();
void Request();
void delay_ms(unsigned int ms);
unsigned char Response();
unsigned char Read_Byte();
void Read_DHT11();
#endif
