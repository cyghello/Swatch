#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f4xx.h"

static int SetTime;

struct para{
	uint8_t	tx_count;
	uint8_t tx_flag;
	
};
typedef struct para  para, *ppara;

void tim5_init();
void tim2_init();
void delay_ms(int Ptime);
void TIM5_IRQHandler(void);
void TIM2_IRQHandler(void);



#endif