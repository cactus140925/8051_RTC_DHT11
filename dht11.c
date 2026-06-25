#include "dht11.h"
unsigned int dem_nhiet_do = 0;
unsigned char I_RH, D_RH, I_Temp, D_Temp, CheckSum;
bit dht_ready = 0;
void Delay_10us() {
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
    _nop_(); _nop_(); _nop_(); _nop_(); _nop_();
}
void delay_request() {
    unsigned int i;
    for(i=0; i<12000; i++); 
}
void delay_ms(unsigned int ms) { 
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 114; j++); 
}
void Request() { 
    DHT11 = 0;
    delay_ms(20); 
    DHT11 = 1; 
}

unsigned char Response() {
    unsigned int timeout = 0;
    while (DHT11 == 1) { if (++timeout > 2000) return 0; } timeout = 0; 
    while (DHT11 == 0) { if (++timeout > 2000) return 0; } timeout = 0;
    while (DHT11 == 1) { if (++timeout > 2000) return 0; } 
    return 1;
}
unsigned char Read_Byte() {
    unsigned char i, dat = 0;
    unsigned int timeout;
    for (i = 0; i < 8; i++) {
        timeout = 0;
        while (DHT11 == 0) { if (++timeout > 2000) return 0; } 
        Delay_10us(); Delay_10us(); Delay_10us(); Delay_10us();
        if (DHT11 == 1) {
            dat |= (1 << (7 - i));
            timeout = 0;
            while (DHT11 == 1) { if (++timeout > 2000) return 0; } 
        }
    }
    return dat;
}
void Read_DHT11() {
    unsigned char tong_byte;
    EA = 0;	
    Request();
    if (Response()) {
        I_RH = Read_Byte(); 
        D_RH = Read_Byte(); 
        I_Temp = Read_Byte(); 
        D_Temp = Read_Byte(); 
        CheckSum = Read_Byte();
        
       
        tong_byte = I_RH + D_RH + I_Temp + D_Temp;
        
      
        if (tong_byte == CheckSum) {
            dht_ready = 1; 
        } else {
            
            dht_ready = 0; 
        }
    } else {
        dht_ready = 0; 
        I_Temp = 0; 
        D_Temp = 0;
    }
		EA = 1;
}