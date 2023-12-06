#ifndef __PCTL_EXTI_ENENT_H
#define __PCTL_EXTI_ENENT_H

//#include "stm32f4xx.h"

#include "drv_gpio.h"
#include "drv_exti.h"
#include "drv_bottom_para.h"

void pctl_exti_gpio_init();
void pctl_exti_key_on (unsigned char* flag);
unsigned char pctl_event_pin_state_rd(event_state* t_event_state);

#endif