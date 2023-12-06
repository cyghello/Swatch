#include "drv_exti.h"
#include "drv_usart.h"

static phandle_exti_call phandle_device_exti_pin_state;
static event_state pin_event_state;
unsigned char gc_flag_key;
void drv_external_interrpt_init ()
{
	EXTI_InitTypeDef exti_interrput;
	
	exti_interrput.EXTI_Line = EXTI_Line0;
	exti_interrput.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_interrput.EXTI_Trigger = EXTI_Trigger_Falling;
	exti_interrput.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&exti_interrput);
}

void drv_event_exti_nvic_init ()
{
	NVIC_InitTypeDef type_nvic_irq;
	type_nvic_irq.NVIC_IRQChannel = EXTI0_IRQn;
	type_nvic_irq.NVIC_IRQChannelPreemptionPriority = 0x00;
	type_nvic_irq.NVIC_IRQChannelSubPriority = 0x00;
	type_nvic_irq.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&type_nvic_irq);
}

void drv_nvic_priorit_group_init ()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

void drv_exti_call_entry (phandle_exti_call phandle)
{
	phandle_device_exti_pin_state = phandle;
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetFlagStatus(EXTI_Line0) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
		judge_key_trigger (&gc_flag_key);
		phandle_device_exti_pin_state(&gc_flag_key);
	}
}

static void judge_key_trigger (unsigned char *pckey)
{
		//delay_1ms (1);  //延时1mS
		for (int i = 0; i < 100000; i++)
		;
		*pckey = FLAG_ENABLE;
}