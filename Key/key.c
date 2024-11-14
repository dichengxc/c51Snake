#include "key.h"

u8 key_matrix_ranks_scan(){						//行列式扫描
	u8 key_value=0;
	Key_MM=0xf7;												//第一列为低电平
	if(Key_MM!=0xf7){										//有按下则变化
		delay_10us(300);												//消抖
		switch(Key_MM){
			case 0x77: key_value=1; break;	//第一行
			case 0xb7: key_value=5; break;	//第二行
			case 0xd7: key_value=9; break;	//第三行
			case 0xe7: key_value=13; break;	//第四行
		}
	}
	while(Key_MM!=0xf7);								//等待松开按键
	Key_MM=0xfb;
	if(Key_MM!=0xfb){
		delay_10us(300);
		switch(Key_MM){
			case 0x7b: key_value=2; break;
			case 0xbb: key_value=6; break;
			case 0xdb: key_value=10; break;
			case 0xeb: key_value=14; break;
		}
	}
	while(Key_MM!=0xfb);
	Key_MM=0xfd;
	if(Key_MM!=0xfd){
		delay_10us(300);
		switch(Key_MM){
			case 0x7d: key_value=3; break;
			case 0xbd: key_value=7; break;
			case 0xdd: key_value=11; break;
			case 0xed: key_value=15; break;
		}
	}
	while(Key_MM!=0xfd);
	Key_MM=0xfe;
	if(Key_MM!=0xfe){
		delay_10us(300);
		switch(Key_MM){
			case 0x7e: key_value=4; break;
			case 0xbe: key_value=8; break;
			case 0xde: key_value=12; break;
			case 0xee: key_value=16; break;
		}
	}
	while(Key_MM!=0xfe);
	return key_value;
}

u8 key_matrix_flip_scan(){							//线翻转式扫描
	u8 key=0;
	Key_MM=0x0f;													//所有行为低电平
	if(Key_MM!=0x0f){											//有按下则变化
		delay_10us(1000);
		Key_MM=0x0f;												//	消
	if(Key_MM!=0x0f){											//	抖
		switch(Key_MM){
			case 0x07: key=1; break;					//第一列
			case 0x0b: key=2; break;					//第二列
			case 0x0d: key=3; break;					//第三列
			case 0x0e: key=4; break;					//第四列
		}
		Key_MM=0xf0;												//所有列为低电平
		switch(Key_MM){
			case 0x70: key=key; break;				//第一行
			case 0xb0: key=key+4; break;			//第二行
			case 0xd0: key=key+8; break;			//第三行
			case 0xe0: key=key+12; break;			//第四行
		}
	}
	}
	return key;
}