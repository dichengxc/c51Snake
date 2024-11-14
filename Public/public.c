#include"public.h"

void delay_10us(u16 x){
	while(--x);
}
void delay_1ms(u16 x){
	u16 i=0,j=0;
	for(i=x;i>0;i--)
		for(j=110;i>0;j--);
}