#ifndef __DRV_EXTI_H
#define __DRV_EXTI_H

/**/
#include "stm32f4xx.h"
#include "drv_bottom_para.h"
typedef void (*phandle_exti_call)(unsigned char* pin_state);



void drv_external_interrpt_init ();
void drv_event_exti_nvic_init ();
void drv_nvic_priorit_group_init ();
void drv_exti_call_entry (phandle_exti_call phandle);
void EXTI0_IRQHandler(void);
static void judge_key_trigger (unsigned char *pckey);


#endif