#ifndef _LIGHT_H
#define _LIGHT_H

#include "public.h"

#define LEDDZ_COLP P0

sbit rCLK=P3^5;
sbit SRCLK=P3^6;
sbit SER=P3^4;

void hc595_write_data(u8 dat);

void leddz_light(u8 LED_dz_row[]);


#endif