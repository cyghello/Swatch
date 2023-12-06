#include "drv_rcc.h"

void drv_rcc_gpio_enable()
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  //2023.05.01 PWM输出口
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  //2023.05.01 TIME4
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

//void drv_rcc_af_gpio_enable()
//{
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO);
//}