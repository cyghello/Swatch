#include "timer.h"

static para apara;
/*
*	优先级：0x00 01;
*/
void tim5_init()
{
		TIM_TimeBaseInitTypeDef TIM5_Init;
		NVIC_InitTypeDef IRQ_TIM5;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
		TIM5_Init.TIM_Period = 0x2328;				//1.外部输入脉冲检测 2.自动重装载寄存器 
		TIM5_Init.TIM_Prescaler = 0x000A;			// 10000D   100M/10000D/10 = 1000
		TIM5_Init.TIM_ClockDivision = TIM_CKD_DIV1;			//没起作用？ 滤波器、死区
		TIM5_Init.TIM_CounterMode = TIM_CounterMode_Up;
		TIM5_Init.TIM_RepetitionCounter = 0x00;
		TIM_TimeBaseInit(TIM5, &TIM5_Init);
		//TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);			//定时器中断
		
		IRQ_TIM5.NVIC_IRQChannel = TIM5_IRQn;
		IRQ_TIM5.NVIC_IRQChannelCmd = ENABLE;
		IRQ_TIM5.NVIC_IRQChannelPreemptionPriority = 0x01;
		IRQ_TIM5.NVIC_IRQChannelSubPriority = 0x02;
		NVIC_Init(&IRQ_TIM5);
		TIM_Cmd(TIM5, ENABLE);
}
/*
* 0x2328 000A 目前测试为8秒
* 优先级：0x01 02;
*/

void tim2_init()
{
	TIM_TimeBaseInitTypeDef TIM2_Init;
	NVIC_InitTypeDef IRQ_Tim2;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM2_Init.TIM_Period = 0x2328;				//1.外部输入脉冲检测 2.自动重装载寄存器 
	TIM2_Init.TIM_Prescaler = 0x000A;
	TIM2_Init.TIM_ClockDivision = TIM_CKD_DIV1;			//没起作用？ 滤波器、死区
	TIM2_Init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM2_Init.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM2, &TIM2_Init);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
		
	IRQ_Tim2.NVIC_IRQChannel = TIM2_IRQn;
	IRQ_Tim2.NVIC_IRQChannelCmd = ENABLE;
	IRQ_Tim2.NVIC_IRQChannelPreemptionPriority = 0x01;
	IRQ_Tim2.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&IRQ_Tim2);
	TIM_Cmd(TIM2, ENABLE);
}

void delay_ms(int Ptime)
{
	SetTime = Ptime;
	while(SetTime);
}

void TIM5_IRQHandler(void)
{
//	USART_SendData(USART1,0x11);
//	for (int i = 0; i < 10000000;i++)
//	;
//	USART_SendData(USART1,TIM_GetFlagStatus(TIM5, TIM_FLAG_Update));
//	for (int i = 0; i < 10000000;i++)
//	;
//	USART_SendData(USART1,apara.tx_flag);
//	for (int i = 0; i < 10000000;i++)
	if (apara.tx_flag == 1)
	{
		apara.tx_flag = 0;
		TIM_ITConfig(TIM5, TIM_IT_Update, DISABLE);
	}
	if (TIM_GetFlagStatus(TIM5, TIM_FLAG_Update) == SET  && apara.tx_flag == 0)
	{
		TIM_ClearITPendingBit(TIM5, TIM_FLAG_Update);
//			USART_SendData(USART1,TIM_GetFlagStatus(TIM5, TIM_FLAG_Update));
//	for (int i = 0; i < 10000000;i++)
//	;
		apara.tx_count++;
		if (apara.tx_count == 2)
		{
			apara.tx_count = 0;
			apara.tx_flag = 1;
			//TIM_ITConfig(TIM5, TIM_IT_Update, DISABLE);
		}
//							USART_SendData(USART1,apara.tx_count);
//	for (int i = 0; i < 10000000;i++)
//		appara->tx_count++;
//		USART_SendData(USART1,apara.tx_count);
			
	}
	
//		if (flag == 0 && SetTime == 0) 
//		{
//			flag = 1;
//		}
//			
	
}
/*
* 定时延时 ms级
* 
*/
void TIM2_IRQHandler(void)
{
		if (TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
		if (SetTime != 0)
			SetTime--;
	}
}
