#ifndef __MAIN_H
#define __MAIN_H	 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "can.h" 
#include "can_uart.h"

typedef struct 
{
	u8 data[8];
	u8 count;
}cansend_buf;

void Peripheral(void);

#endif

