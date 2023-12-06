#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H

/**/
#include "stm32f4xx.h"

void drv_timer_pwm_init();
void drv_pwm_ccr_value_write (uint8_t channel, uint32_t ccr_value);
void drv_hc_sr04_timer_init ();
void TIM4_IRQHandler(void);
int get_tim_count ();
uint32_t getechotimer();

#endif