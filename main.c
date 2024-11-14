#include"public.h"
#include"key.h"
#include"light.h"
#include <stdlib.h>

#define LEDS P2

u8 LED_dz_row[8]={0};
u8 Map[8][8]={0};
u8 heady,headx;
u8 speed=10;
u8 foodlight=1;
u8 sta;

void CreatFood() {
	u8 x,y;
	do{
		x=rand()%8;
		y=rand()%8;
	}while(Map[y][x]!=0);
	Map[y][x]=127;
}

void Initsnake() {
	u8 i;
	sta=4;
	heady=1,headx=4;
	for(i=0;i<4;i++){
		Map[heady][headx-i]=4-i;
	}
	CreatFood();
}

void PrintSnake() {
	u8 i,j,sum;
	for(i=0;i<8;i++){
		sum=0;
		for(j=0;j<8;j++){
			sum=sum*2;
			if((Map[j][i]>0&&Map[j][i]<127)||(Map[j][i]==127&&foodlight))
				sum+=1;
		}
		LED_dz_row[i]=sum;
	}
	foodlight=!foodlight;
}

void MoveSnake(){
	u8 x,y,i,j;
	switch(sta){
		case 1:x=headx;y=(heady-1+8)%8;break;
		case 2:x=headx;y=(heady+1+8)%8;break;
		case 3:x=(headx-1+8)%8;y=heady;break;
		case 4:x=(headx+1+8)%8;y=heady;break;
	}
	if(Map[y][x]==127){
		Map[y][x]=Map[heady][headx]+1;
		headx=x;
		heady=y;
		CreatFood();
	}else if(Map[y][x]==0){
		Map[y][x]=Map[heady][headx]+1;
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				if(Map[i][j]!=0&&Map[i][j]!=127){
					Map[i][j]--;
				}
			}
		}
		headx=x;
		heady=y;
	}else sta=0;
	PrintSnake();
}

void time0_init(){
	TMOD|=0x01;					//选择定时器0模式，工作方式1
	TH0=0xFC;						//给定时器赋初值
	TL0=0x66;
	ET0=1;							//打开定时器0中断允许
	EA=1;								//打开总中断
	TR0=1;							//打开定时器
}

void speeddisplay(){
	if(speed<=5)
		P2=0xff;
	else if(speed<=10)
		P2=0xfe;
	else if(speed<=15)
		P2=0xfc;
	else if(speed<=20)
		P2=0xf8;
	else if(speed<=25)
		P2=0xf0;
	else if(speed<=30)
		P2=0xe0;
	else if(speed<=35)
		P2=0xc0;
	else if(speed<=40)
		P2=0x80;
	else P2=0x00;
}

void main(){
	u8 key;
	P2=0xfc;
	Initsnake();
	PrintSnake();
	time0_init();
	while(1){
		key=key_matrix_flip_scan();
		if(key==10)sta=1;
		else if(key==13)sta=3;
		else if(key==14)sta=2;
		else if(key==15)sta=4;
		else if(key==9){
			if(speed>1)
				speed--;}
		else if(key==11){
			if(speed<50)
				speed++;}
		leddz_light(LED_dz_row);
	}
}

void time0() interrupt 1{
	static u16 i=0;
	TH0=0xFC;					//重新赋值
	TL0=0x66;
	i+=speed;
	speeddisplay();
	if(i>5000){
		i=0;
		MoveSnake();
	}
}