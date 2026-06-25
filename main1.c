#include "main.h"
bit user,user2;
unsigned char r1_gio, r1_phut, r1_ngay, r1_thang, r1_state;
unsigned char r2_gio, r2_phut, r2_ngay, r2_thang, r2_state;
unsigned char TOn1=20,TOff1=40,TMax1=45;
unsigned char TOn2=35,TOff2=25,TMax2=45;
 /**********************************************************************************/

/**********************************************************************************/
void delay(long time)
{
    while(time--)
    {
        TMOD &= 0xF0;    
        TMOD |= 0x01;    
        TH0 = 0xFC;     
        TL0 = 0x67; 
        TF0 = 0;         
        TR0 = 1;        
        
        while(TF0 == 0); 
        
        TR0 = 0;        
        TF0 = 0;        
    }
}
void hienthi_rtc(void)                                                          
{
	ghilenhLCD(0xc6);   
	hienthi_dulieu_rtc(docdulieu(0)); 
	ghilenhLCD(0xc3);  
	hienthi_dulieu_rtc(docdulieu(1)); 
	ghi_kytu(':');
	ghilenhLCD(0xc0);  
	hienthi_dulieu_rtc(docdulieu(2)); 
	ghi_kytu(':');
	ghilenhLCD(0x80); 
	ghi_chuoi(day[docdulieu(3)-1]);  
	ghi_kytu(',');
	ghilenhLCD(0x86); 
	hienthi_dulieu_rtc(docdulieu(4));
	ghi_kytu('-');  
	hienthi_dulieu_rtc(docdulieu(5));
	ghi_chuoi("-20");               
	hienthi_dulieu_rtc(docdulieu(6));
	dem_nhiet_do++;
    if(dem_nhiet_do > 20) 
    {
        Read_DHT11();
        dem_nhiet_do = 0;
    }
    
    
    ghilenhLCD(0xC9); 
    ghiso(I_Temp);
    ghi_kytu(0xDF); 
    ghi_kytu('C');
	ghiso(I_RH);
	ghi_kytu('%');
}

/**********************************************************************************/

 /**********************************************************************************/

unsigned char bcd_dec(unsigned char bcd)
{
	return((bcd/16)*10+(bcd%16));   
}

unsigned char dec_bcd(unsigned char dec)
{
	return((dec/10)*16+(dec%10));
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
void caidat_rtc()
{
	unsigned char giay,phut,gio,thu,ngay,thang,nam;
	
	
	delay(300); 
	
	
	gio = bcd_dec(docdulieu(2) & 0x3f);
	if(gio > 23)
	{
		delay(20); 
		gio = bcd_dec(docdulieu(2) & 0x3f); 
		if(gio > 23) gio = 0;
	}


	phut = bcd_dec(docdulieu(1));
	if(phut > 59)
	{
		delay(20);
		phut = bcd_dec(docdulieu(1));
		if(phut > 59) phut = 0;
	}

	giay = bcd_dec(docdulieu(0) & 0x7f);
	if(giay > 59)
	{
		delay(20);
		giay = bcd_dec(docdulieu(0) & 0x7f);
		if(giay > 59) giay = 0;
	}


	ngay = bcd_dec(docdulieu(4));
	if(ngay > 31 || ngay == 0)
	{
		delay(20);
		ngay = bcd_dec(docdulieu(4));
		if(ngay > 31 || ngay == 0) ngay = 1;
	}

	thang = bcd_dec(docdulieu(5));
	if(thang > 12 || thang == 0)
	{
		delay(20);
		thang = bcd_dec(docdulieu(5));
		if(thang > 12 || thang == 0) thang = 1;
	}


	nam = bcd_dec(docdulieu(6));
	if(nam > 99)
	{
		delay(20);
		nam = bcd_dec(docdulieu(6));
		if(nam > 99) nam = 24;
	}
	

	thu = bcd_dec(docdulieu(3));
	if(thu > 7 || thu == 0) thu = 1;

	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

	ghilenhLCD(1);
	ghi_chuoi("CHINH");
	ghi_chuoi(" GIO :");
	ghilenhLCD(0x0e);
	ghilenhLCD(0xc4);
	ghiso(gio);
	ghi_kytu(':');
	ghiso(phut);
	ghi_kytu(':');
	ghiso(giay);
	ghilenhLCD(0xC5);
	
	while(menu==0); 
	delay(200);      
	
    caidatgio:while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0)
	{
		gio++;
		if(gio >= 24) gio=0; 
		ghilenhLCD(0xC4);
		ghiso(gio);
		ghilenhLCD(0xC5);
		delay(500);
		goto caidatgio; 
	}
	if(giam==0)
	{
		gio--;
		if(gio == 0xFF) gio=23; 
		ghilenhLCD(0xC4);
		ghiso(gio);
		ghilenhLCD(0xC5);
		delay(500);
		goto caidatgio;
	}
	while(menu==0); 
	delay(200);      
	
	ghilenhLCD(0xC8);
    caidatphut: while(tang!=0 && giam!=0 && menu!=0);
    if(tang==0)
    {
		phut++;
		if(phut >= 60) phut=0; 
		ghilenhLCD(0xC7);
		ghiso(phut);
		ghilenhLCD(0x10);
		delay(500);
		goto caidatphut;
	}
	if(giam==0)
	{
		phut--;
		if(phut == 0xFF) phut=59;
		ghilenhLCD(0xC7);
		ghiso(phut);
		ghilenhLCD(0x10);
		delay(500);
		goto caidatphut;
	}
	while(menu==0); 
	delay(200);      
	
	ghilenhLCD(0xCB);
    caidatgiay: while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0)
	{
		giay++;
		if(giay >= 60) giay=0; // 
		ghilenhLCD(0xCA);
		ghiso(giay);
		ghilenhLCD(0xCB);
		delay(500);
		goto caidatgiay; 
	}
	if(giam==0)
	{
		giay--;
		if(giay == 0xFF) giay=59;
		ghilenhLCD(0xCA);
		ghiso(giay);
		ghilenhLCD(0xCB);
		delay(500);
		goto caidatgiay;
	}

 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	// CAI DAT NGAY - THANG - NAM 
	
	while(menu==0); 
	delay(200);      
	
	ghilenhLCD(1);
	ghi_chuoi("CHINH NGAY :");
	ghilenhLCD(0xc4);
	ghiso(ngay);
	ghi_kytu('-');
	ghiso(thang);
	ghi_chuoi("-20");
	ghiso(nam);
	///////////////////////////////////////////////////
	ghilenhLCD(0xc5);
    caidatngay:while (tang!=0 && giam!=0 && menu!=0);
	if(tang==0)
	{
		ngay++;
		
		if(ngay >= 32)  ngay=1; 
		ghilenhLCD(0xC4);
		ghiso(ngay);
		ghilenhLCD(0x10);
		delay(300);
		goto caidatngay;
	}

	if(giam==0)
	{
		ngay--;
		if(ngay == 0) ngay=31;
		ghilenhLCD(0xC4);
		ghiso(ngay);
		ghilenhLCD(0x10);
		delay(300);
		goto caidatngay;
	}
	while(menu==0); 
	delay(200);      
	
	ghilenhLCD(0xC8);
    caidatthang:while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0)
	{
		thang++;
		if(thang >= 13) thang=1; 
		ghilenhLCD(0xC7);
		ghiso(thang);
		ghilenhLCD(0x10);
		delay(300);
		goto caidatthang;
	}
	if(giam==0)
	{
		thang--;
		if(thang == 0) thang=12;
		ghilenhLCD(0xC7);
		ghiso(thang);
		ghilenhLCD(0x10);
		delay(300);
		goto caidatthang;
	}
	while(menu==0); 
	delay(200);      
	
	ghilenhLCD(0xCD);
    caidatnam:while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0)
	{
		nam++;
		if(nam >= 100) nam=0; 
		ghilenhLCD(0xCC);
		ghiso(nam);
		ghilenhLCD(0xCD);
		delay(300);
		goto caidatnam;
	}

	if(giam==0)
	{
		nam--;
		if(nam == 0xFF) nam=99;
		ghilenhLCD(0xCC);
		ghiso(nam);
		ghilenhLCD(0xCD);
		delay(300);
		goto caidatnam; 
	}


 //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    // CAI DAT THU 
	while(menu==0); 
	delay(200);      
	
	ghilenhLCD(1);
	ghi_chuoi("CHINH THU :");
	ghilenhLCD(0xc4);
	ghi_chuoi(day[thu-1]);
    caidatthu:while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0)
	{   
		thu++;
		if(thu >= 8) thu=1; 
		ghilenhLCD(0xC4);
		ghi_chuoi(day[thu-1]);
		delay(300);
		goto caidatthu;
	}
	
	if(giam==0)
	{   
		thu--;
		if(thu == 0) thu=7;
		ghilenhLCD(0xC4);
		ghi_chuoi(day[thu-1]);
		delay(300);
		goto caidatthu;
	}

	while(menu==0); 
	delay(200);      
	
	ghilenhLCD(1);      
	ghilenhLCD(0x0C); 
	
	//day tgian vào rtc
	giatrikhoitao_rtc[0] = dec_bcd(giay);
	giatrikhoitao_rtc[1] = dec_bcd(phut);
	giatrikhoitao_rtc[2] = dec_bcd(gio);
	giatrikhoitao_rtc[3] = dec_bcd(thu);
	giatrikhoitao_rtc[4] = dec_bcd(ngay);
	giatrikhoitao_rtc[5] = dec_bcd(thang);
	giatrikhoitao_rtc[6] = dec_bcd(nam);
	giatrikhoitao_rtc[7] = 0x00;
	giatrikhoitao_rtc[8] = 'c';  

	ghivaoDS1307();
	ghilenhLCD(1);
}

//==================================================================================//
void caidat_baothuc(unsigned char add, char* str)
{
	//doc bao thuc rtc
	unsigned char gio,phut,ngay,thang,state;
	delay(200);
	gio   = bcd_dec(docdulieu(add));
	phut  = bcd_dec(docdulieu(add+1));
	ngay  = bcd_dec(docdulieu(add+2));
	thang = bcd_dec(docdulieu(add+3));
	state = bcd_dec(docdulieu(add+4)); 
	if(gio > 23) gio = 0;
	if(phut > 59)phut = 0;
	if(ngay > 31) ngay = 0; 
	if(thang > 12) thang = 0; 
    if(state> 1) state = 0; 
	ghilenhLCD(1);
	ghi_chuoi(str);
	ghilenhLCD(0xC0); 
	ghiso(ngay); ghi_kytu('/'); ghiso(thang);
	ghi_kytu(' ');
	ghiso(gio); ghi_kytu(':'); ghiso(phut); ghi_chuoi("D:");
	ghiso(state);

    ghilenhLCD(0x0E); 
	ghilenhLCD(0xC7); 
	while(menu==0); 
	delay(200);
	
	caidat_r1_gio: while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0) {
		gio++; if(gio >= 24) gio=0; 
		ghilenhLCD(0xC6); ghiso(gio); ghilenhLCD(0xC7);
		delay(300); goto caidat_r1_gio;
	}
	if(giam==0) {
		gio--; if(gio == 0xFF) gio=23;
		ghilenhLCD(0xC6); ghiso(gio); ghilenhLCD(0xC7);
		delay(300); goto caidat_r1_gio;
	}

	
	while(menu==0); 
	delay(200);     
	
	ghilenhLCD(0xCA); 
	caidat_r1_phut: while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0) {
		phut++; if(phut >= 60) phut=0; 
		ghilenhLCD(0xC9); ghiso(phut); ghilenhLCD(0xCA);
		delay(300); goto caidat_r1_phut;
	}
	if(giam==0) {
		phut--; if(phut == 0xFF) phut=59;
		ghilenhLCD(0xC9); ghiso(phut); ghilenhLCD(0xCA);
		delay(300); goto caidat_r1_phut;
	}

	// CAI DAT NGAY BAO THUC
	while(menu==0); 
	delay(200);     
	
	ghilenhLCD(0xC1); // dia chi thanh ghi ngay
	caidat_r1_ngay: while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0) {
		ngay++; 
		if(ngay >= 32) ngay=0; 
		ghilenhLCD(0xC0); ghiso(ngay); ghilenhLCD(0xC1);
		delay(300); goto caidat_r1_ngay;
	}
	if(giam==0) {
		ngay--; 
		if(ngay == 0xFF) ngay=31;
		ghilenhLCD(0xC0); ghiso(ngay); ghilenhLCD(0xC1);
		delay(300); goto caidat_r1_ngay;
	}

	// CAI DAT THANG BAO THUC
	while(menu==0); 
	delay(200);     
	
	ghilenhLCD(0xC4); // dia chi thanh ghi thang
	caidat_r1_thang: while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0) {
		thang++; 
		if(thang >= 13) thang=0; 
		ghilenhLCD(0xC3); ghiso(thang); ghilenhLCD(0xC4);
		delay(300); goto caidat_r1_thang;
	}
	if(giam==0) {
		thang--; 
		if(thang == 0xFF) thang=12;
		ghilenhLCD(0xC3); ghiso(thang); ghilenhLCD(0xC4);
		delay(300); goto caidat_r1_thang;
	}
	while(menu==0); 
	delay(200);     
	
	ghilenhLCD(0xCD); // dia chi thanh ghi trang thai
	caidat_r1_state: while(tang!=0 && giam!=0 && menu!=0);
	if(tang==0) {
		state=!state; 
		ghilenhLCD(0xCD); ghiso(state); ghilenhLCD(0xCE);
		delay(300); goto caidat_r1_state;
	}
	if(giam==0) {
		state=!state; 
		ghilenhLCD(0xCD); ghiso(state); ghilenhLCD(0xCE);
		delay(300); goto caidat_r1_state;
	}
	while(menu==0); 
	delay(200);     
    ghilenhLCD(0x0C); 
	// save bao thuc vao ds1307
	ghi_dulieu_rtc(add, dec_bcd(gio));
	ghi_dulieu_rtc(add+1, dec_bcd(phut));
	ghi_dulieu_rtc(add+2, dec_bcd(ngay));
	ghi_dulieu_rtc(add+3, dec_bcd(thang));
	ghi_dulieu_rtc(add+4, dec_bcd(state));
	ghilenhLCD(1); 
}
/**********************************************************************************/
void kiemtra_rtc(void)
{
	unsigned char temp;
	unsigned char retry = 50; 
	bit flag_ok = 0;

	while(retry--)
	{
		start_rtc();
		gui_rtc(0xd0);
		gui_rtc(0x08);
		start_rtc();
		gui_rtc(0xd1);
		temp=nhan_rtc();
		stop_rtc();
		
		if(temp == 'c') 	
		{
			flag_ok = 1;
			break; 
		}
		delay(10); 
	}

	if(flag_ok == 0)   
	{              
		giatrikhoitao_rtc[0]=0x50;
		giatrikhoitao_rtc[1]=0x59;
		giatrikhoitao_rtc[2]=0x09;
		giatrikhoitao_rtc[3]=0x04;
		giatrikhoitao_rtc[4]=0x04;
		giatrikhoitao_rtc[5]=0x05;
		giatrikhoitao_rtc[6]=0x11;
		giatrikhoitao_rtc[7]=0x00;
		giatrikhoitao_rtc[8]='c';
		ghivaoDS1307();
		
// gtri mac dinh
		ghi_dulieu_rtc(0x09, dec_bcd(0)); 
		ghi_dulieu_rtc(0x0A, dec_bcd(0)); 
		ghi_dulieu_rtc(0x0B, dec_bcd(0)); 
		ghi_dulieu_rtc(0x0C, dec_bcd(0)); 
		ghi_dulieu_rtc(0x0D, dec_bcd(0)); 
		ghi_dulieu_rtc(0x0E, dec_bcd(0)); 
		ghi_dulieu_rtc(0x0F, dec_bcd(0)); 
		ghi_dulieu_rtc(0x10, dec_bcd(0)); 
		ghi_dulieu_rtc(0x11, dec_bcd(0)); 
        ghi_dulieu_rtc(0x12, dec_bcd(0));
	    ghi_dulieu_rtc(0x13, TOn1);
		ghi_dulieu_rtc(0x14, TOff1);
		ghi_dulieu_rtc(0x15, TMax1);
		ghi_dulieu_rtc(0x16, TOn2);
		ghi_dulieu_rtc(0x17, TOff2);
	    ghi_dulieu_rtc(0x18, TMax2);
	}

    r1_gio   = bcd_dec(docdulieu(0x09)); 
    r1_phut  = bcd_dec(docdulieu(0x0A)); 
    r1_ngay  = bcd_dec(docdulieu(0x0B)); 
    r1_thang = bcd_dec(docdulieu(0x0C)); 
    r1_state = bcd_dec(docdulieu(0x0D)); 

   
    r2_gio   = bcd_dec(docdulieu(0x0E)); 
    r2_phut  = bcd_dec(docdulieu(0x0F)); 
    r2_ngay  = bcd_dec(docdulieu(0x10)); 
    r2_thang = bcd_dec(docdulieu(0x11)); 
    r2_state = bcd_dec(docdulieu(0x12));
	
	if(r1_gio>23) r1_gio=0;
	if(r1_phut>60) r1_phut=0;
	 if(r1_ngay>32) r1_ngay=0;
	if(r1_thang>12) r1_thang=0;
	if(r1_state>1) r1_state=0;
	if(r2_gio>23) r2_gio=0;
	if(r2_phut>60) r2_phut=0;
	if(r2_ngay>32) r2_ngay=0;
	if(r2_thang>12) r2_thang=0;
	if(r2_state>1) r2_state=0;
}                         
void  doccacdulieu(void){   int i;
                            for(i=0;i<=6;i++){docdulieu(i);}   }

//////////////////////////////////////////////////////////////////////////////
bit check_r1, check_r2;
bit co=0;
void caidatco() interrupt 0     //ngat ngoai 0 thi co =1
{
	co=1;
}
void autorelay()
{
    if(dht_ready == 1)
    {
        // --- LOGIC CHO RELAY 1 (ÐÈN/SU?I) ---
        if(I_Temp > TMax1) 
        {
            R1 = 1; check_r1 = 0; user = 0;
        }
        else if(user == 0) 
        {
            if(I_Temp < TOn1) 
            {
                if(check_r1 == 0) { R1 = 0; check_r1 = 1; buzzer = 1; delay(100); buzzer = 0; }
            } 
            else if(I_Temp > TOff1) 
            {
                R1 = 1; check_r1 = 0;
							
            }
        }

      
        if(I_Temp > TMax2) 
        {
            R2 = 0; check_r2 = 1; user2 = 0;
        }
        else if(user2 == 0) 
        {
            if(I_Temp > TOn2) 
            {
                if(check_r2 == 0) { R2 = 0; check_r2 = 1; buzzer = 1; delay(100); buzzer = 0; }
            }
            else if(I_Temp < TOff2) 
            {
                R2 = 1; check_r2 = 0;
            }
        }
    }
}
void setting(unsigned char add)
{
	TOn1=docdulieu(add);
	TOff1=docdulieu(add+1);
	TMax1=docdulieu(add+2);
	TOn2=docdulieu(add+3);
	TOff2=docdulieu(add+4);
	TMax2=docdulieu(add+5);
	ghilenhLCD(1);
	ghilenhLCD(0x80);
	ghi_chuoi("DEN:  ");
	ghiso(TOn1);ghi_kytu(':');ghiso(TOff1);ghi_kytu(':');ghiso(TMax1);
	ghilenhLCD(0xC0);
	ghi_chuoi("QUAT: ");
	ghiso(TOn2);ghi_kytu(':');ghiso(TOff2);ghi_kytu(':');ghiso(TMax2);
	while(menu==0);
	delay(200);
	ghilenhLCD(0x0E);
	ghilenhLCD(0x87);
	caidat_Ton1: while(tang!=0&&giam!=0&&menu!=0);
	delay(20);
	if(tang==0)
	{
		TOn1++;
		if(TOn1>100) TOn1=0;
		ghilenhLCD(0x86);ghiso(TOn1);ghilenhLCD(0x87);
        delay(200); goto caidat_Ton1;
	}
	if(giam==0)
	{
		TOn1--;
		if(TOn1<=0) TOn1=100;
		ghilenhLCD(0x86);ghiso(TOn1);ghilenhLCD(0x87);
		delay(200);
		goto caidat_Ton1;
	}
	while(menu==0);
	delay(200);
	ghilenhLCD(0x8A);
	caidat_Toff1: while(tang!=0&&giam!=0&&menu!=0);
	delay(20);
	if(tang==0)
	{
		TOff1++;
		if(TOff1>100) TOff1=0;
		ghilenhLCD(0x89);ghiso(TOff1);ghilenhLCD(0x8A);
        delay(200); goto caidat_Toff1;
	}
	if(giam==0)
	{
		TOff1--;
		if(TOff1<=0) TOff1=60;
		ghilenhLCD(0x89);ghiso(TOff1);ghilenhLCD(0x8A);
		delay(200);
		goto caidat_Toff1;
	}
	while(menu==0);
	delay(200);
		ghilenhLCD(0x8D);
	caidat_TMax1: while(tang!=0&&giam!=0&&menu!=0);
	delay(20);
	if(tang==0)
	{
		TMax1++;
		if(TMax1>100) TMax1=0;
		ghilenhLCD(0x8C);ghiso(TMax1);ghilenhLCD(0x8D);
        delay(200); goto caidat_TMax1;
	}
	if(giam==0)
	{
		TMax1--;
		if(TMax1<=0) TMax1=100;
		ghilenhLCD(0x8C);ghiso(TMax1);ghilenhLCD(0x8D);
		
		delay(200); goto caidat_TMax1;
	}
	while(menu==0);
	delay(200);
	ghilenhLCD(0xC7);
	caidat_Ton2: while(tang!=0&&giam!=0&&menu!=0);
	delay(20);

	if(tang==0)
	{
		TOn2++;
		if(TOn2>100) TOn2=0;
		ghilenhLCD(0xC6);ghiso(TOn2);ghilenhLCD(0xC7);
        delay(200); goto caidat_Ton2;
	}
	if(giam==0)
	{
		TOn2--;
		if(TOn2<=0) TOn2=100;
		ghilenhLCD(0xC6);ghiso(TOn2);ghilenhLCD(0xC7);
		
		delay(200);goto caidat_Ton2;
	}
	while(menu==0);
	delay(200);
	ghilenhLCD(0xCA);
	caidat_Toff2: while(tang!=0&&giam!=0&&menu!=0);
	delay(20);

	if(tang==0)
	{
		TOff2++;
		if(TOff2>100) TOff2=100;
		ghilenhLCD(0xC9);ghiso(TOff2);ghilenhLCD(0xCA);
        delay(200); goto caidat_Toff2;
	}
	if(giam==0)
	{
		TOff2--;
		if(TOff2<=0) TOff2=100;
		ghilenhLCD(0xC9);ghiso(TOff2);ghilenhLCD(0xCA);
		delay(200); goto caidat_Toff2;
	}
	while(menu==0);
	delay(200);
	ghilenhLCD(0xCD);
	caidat_TMax2: while(tang!=0&&giam!=0&&menu!=0);
	delay(20);
	if(tang==0)
	{
		TMax2++;
		if(TMax2>100) TMax2=0;
		ghilenhLCD(0xCC);ghiso(TMax2);ghilenhLCD(0xCD);
        delay(200); goto caidat_TMax2;
	}
	if(giam==0)
	{
		TMax2--;
		if(TMax2<=0) TMax2=100;
		ghilenhLCD(0xCC);ghiso(TMax2);ghilenhLCD(0xCD);
		delay(200);goto caidat_TMax2;
	}
	while(menu==0);
	delay(200);
	ghilenhLCD(1);
	ghilenhLCD(0x0C);
    ghi_dulieu_rtc(add,TOn1);
	ghi_dulieu_rtc(add+1,TOff1);
	ghi_dulieu_rtc(add+2,TMax1);
	ghi_dulieu_rtc(add+3,TOn2);
	ghi_dulieu_rtc(add+4,TOff2);
	ghi_dulieu_rtc(add+5,TMax2);
    ghilenhLCD(1);
}
void main()
{   
	unsigned char c_giay, c_phut, c_gio, c_ngay, c_thang;
	unsigned char i; 
	delay(200); 
	sda = 1; 
	for(i=0; i<9; i++) 
	{
		scl = 0;
		delay(2); 
		scl = 1;
		delay(2);
	}
	scl = 0;
	
	// Khoi tao coi chip
	buzzer = 0; 
    R1=1;R2=1;
	check_r1=0;check_r2=0;
	khoitaoLCD();
	ghilenhLCD(1);
    ghilenhLCD(0x80);
	ghilenhLCD(0xc0);
	ghi_chuoi("----VOLTAGE----");
	delay(1500);
	ghilenhLCD(1);
	
	kiemtra_rtc(); 
	
	IE=0x81;
	doccacdulieu();
	
	while(1)
	{   
		doccacdulieu();
		hienthi_rtc();
		delay(200);
		c_giay = bcd_dec(docdulieu(0) & 0x7f);
		c_phut = bcd_dec(docdulieu(1));
		c_gio  = bcd_dec(docdulieu(2) & 0x3f);
		c_ngay = bcd_dec(docdulieu(4));
		c_thang = bcd_dec(docdulieu(5));
        
		if(c_gio == r1_gio && c_phut == r1_phut)
        {
            bit baothuc_r1 = 0;
            
            if(r1_thang == 0 && r1_ngay == 0) 
            {
                baothuc_r1 = 1;
            }
            else if(r1_thang == 0) 
            {
                if(r1_ngay == c_ngay) baothuc_r1 = 1;
            }
            else if(r1_ngay == 0) 
            {
                if(c_thang == r1_thang) baothuc_r1 = 1;
            }
            else // 
            {
                if(c_ngay == r1_ngay && c_thang == r1_thang) baothuc_r1 = 1;
            }

           
            if(baothuc_r1 == 1 && c_giay == 0 && r1_state == 1)
            {
                ghilenhLCD(0x01);
                ghilenhLCD(0x80);
                ghi_chuoi("!!! BAT RELAY 1 !!!");
                
                R1 = 0;         
                check_r1 = 1;    
                user = 1;        
                buzzer = 1;
				        delay(100);
				        buzzer =0;
                delay(1000);     
            }
        }
        
        // ----------------- CHECK BAO THUC RELAY 2 -----------------
        if(c_gio == r2_gio && c_phut == r2_phut)
        {
            bit baothuc_r2 = 0;
            
            if(r2_thang == 0 && r2_ngay == 0) 
            {
                baothuc_r2 = 1;
            }
            else if(r2_thang == 0) 
            {
                if(r2_ngay == c_ngay) baothuc_r2 = 1;
            }
            else if(r2_ngay == 0) 
            {
                if(c_thang == r2_thang) baothuc_r2 = 1;
            }
            else 
            {
                if(c_ngay == r2_ngay && c_thang == r2_thang) baothuc_r2 = 1;
            }

            if(baothuc_r2 == 1 && c_giay == 0 && r2_state == 1)
            {
                ghilenhLCD(0x01);
                ghilenhLCD(0x80);
                ghi_chuoi("!!! BAT RELAY 2 !!!");
                
                R2 = 0;
                check_r2 = 1;
                user2 = 1;      
                buzzer = 1;
				        delay(100);
				        buzzer =0;
                delay(1000); 
            }
        }
		if(co==1)  
		{ 
			buzzer = 1; delay(100); buzzer = 0;
			caidat_rtc();
			co=0;   
		}
		
		if(tang==0&&giam==0)
		{
			delay(1000); 
			if(tang==0&&giam==0) 
			{
				while(giam==0&giam==0);
				buzzer = 1; delay(100); buzzer = 0;
				caidat_baothuc(0x09,"Cai RELAY 1");
				caidat_baothuc(0x0E,"CAI RELAY 2");
					kiemtra_rtc(); 
				co = 0; 
			}
		}
		if(BTN_SET == 0) 
{
    delay(20);
    if(BTN_SET == 0)
    {
        buzzer = 1; delay(100); buzzer = 0;
        setting(0x13); 
        co = 0;   
        ghilenhLCD(1);
        while(BTN_SET == 0); 
    }
}
		 if(BTN1==0)
		{
			delay(50);
			while(BTN1==0);
			if(check_r1==0)
			{
				R1=0;
				check_r1=1;
				user=0;
				buzzer = 1;
				delay(100);
				buzzer =0;
			}else{
				R1=1;
				check_r1=0;
				if(I_Temp<TOn1)
				{
					user=1;
				}
			}
               
			
		}
		
		 if(BTN2==0)
		{
			delay(50);
			while(BTN2==0);
			if(check_r2==0)
			{
				R2=0;
				check_r2=1;
				user2=0;
				buzzer = 1;
				delay(100);
				buzzer =0;
			}else{
				R2=1;
				check_r2=0;
				if(I_Temp>TOn2)
				{
					user2=1;
				}
			}
               
			
		}
	   autorelay();
	   
	}
}