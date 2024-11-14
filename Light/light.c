#include "light.h"

u8 LED_dz_col[8]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};

void hc595_write_data(u8 dat){
	u8 i=0;
	for(i=0;i<8;i++){
		SER=dat>>7;
		dat=dat<<1;
		SRCLK=0;
		delay_10us(1);
		SRCLK=1;
		delay_10us(1);
	}
	rCLK=1;
	delay_10us(1);
	rCLK=0;
}

void leddz_light(u8 LED_dz_row[]){
	u8 i=0;
	for(i=0;i<8;i++){
		LEDDZ_COLP=LED_dz_col[i];
		hc595_write_data(LED_dz_row[i]);
		delay_10us(100);
		hc595_write_data(0x00);
	}
}