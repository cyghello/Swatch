#include "drv_usart.h"
#include "timer.h"
#include "drv_dma.h"
#include "stdarg.h"	//va_list
#include "stdio.h"  //vsprintf()
#include "string.h" //strlen()


//GPIO_InitTypeDef GPIO_USART;


void drv_init_usart_gpio()
{
	GPIO_InitTypeDef GPIO_USART;
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_USART.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_USART.GPIO_Mode = GPIO_Mode_AF;
	GPIO_USART.GPIO_OType = GPIO_OType_PP;
  GPIO_USART.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_USART.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_USART);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);
}

//void drv_init_usart2_gpio()
//{
//	GPIO_InitTypeDef GPIO_USART;
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//	GPIO_USART.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
//	GPIO_USART.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_USART.GPIO_OType = GPIO_OType_PP;
//  GPIO_USART.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_USART.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOA, &GPIO_USART);
//	
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART1);
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART1);
//}
void drv_init_usart()
{
	USART_InitTypeDef USART_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//USART_Mode_Rx | USART_Mode_Tx
	USART_Init(USART1,&USART_InitStructure);
	
	
	NVIC_InitTypeDef IRQ_Usart;
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断管理器容器大小
	IRQ_Usart.NVIC_IRQChannel = USART1_IRQn;
	IRQ_Usart.NVIC_IRQChannelCmd = ENABLE;
	IRQ_Usart.NVIC_IRQChannelPreemptionPriority = 0x01;
	IRQ_Usart.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&IRQ_Usart);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	//USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	
	
}
//void drv_init_usart2()
//{

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
//	USART_InitStructure.USART_BaudRate = 9600;
//  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//  USART_InitStructure.USART_StopBits = USART_StopBits_1;
//  USART_InitStructure.USART_Parity = USART_Parity_No;
//  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//USART_Mode_Rx | USART_Mode_Tx
//	USART_Init(USART2,&USART_InitStructure);
//	
//  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //中断管理器容器大小
//	IRQ_Usart.NVIC_IRQChannel = USART2_IRQn;
//	IRQ_Usart.NVIC_IRQChannelCmd = ENABLE;
//	IRQ_Usart.NVIC_IRQChannelPreemptionPriority = 0x01;
//	IRQ_Usart.NVIC_IRQChannelSubPriority = 0x02;
//	NVIC_Init(&IRQ_Usart);
//	USART_Cmd(USART2,ENABLE);
//	//USART_ITConfig(USART2,USART_IT_TXE,ENABLE);
//	
//}
/**
*  学习DMA存储数据(发送数据会了，接收不会)
*	 学习回调函数  
*/


static phandle_usart_call phandle_usart_rx_event = 0;
unsigned char global_usart_rx_data;
/* 
*  @ brief： drv_usart_rx_call_entry(void* phandle)
*  @        回调函数函数入口
*  @
*/
void drv_usart_rx_call_entry (phandle_usart_call phandle)
{
	phandle_usart_rx_event = phandle;
}

#define usart_max_rx_len  400
#define usart_max_tx_len  400

uint16_t res;
uint16_t USART_ESP_RX_BUF[usart_max_rx_len]; 			
uint16_t  USART_ESP_TX_BUF[usart_max_tx_len];
uint16_t USART_ESP_RX_STA=0; 
/* 
*  notes：当接收数据时就返回当前接收数据（2023.04.05）
*/
//void USART1_IRQHandler(void)
//{
//		if (USART_GetFlagStatus(USART1, USART_IT_RXNE) != RESET)
//		{
//			USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//			global_usart_rx_data = USART_ReceiveData(USART1);
//			phandle_usart_rx_event(&global_usart_rx_data);
//			//rx_data[pcount++] = USART_ReceiveData(USART1);
//		}
//}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{	 
		res = USART_ReceiveData(USART2);		 
		if((USART_ESP_RX_STA&(1<<15)) == 0)
		{ 
			if(USART_ESP_RX_STA < usart_max_rx_len)	
			{
				TIM_SetCounter(TIM7,0);         				
				if(USART_ESP_RX_STA == 0) 				
				{
					TIM_Cmd(TIM7, ENABLE);
				} 
				USART_ESP_RX_BUF[USART_ESP_RX_STA++] = res;	
			}
			else 
			{
				USART_ESP_RX_STA |= 1 << 15;			
			} 
		}
	}  	
	
}
//void print(uint16_t* temp)
//{
//	USART_SendData(USART1, *temp);
//}
//void print_usart2(uint16_t* temp)
//{
//	USART_SendData(USART2, *temp);
//}

void proc_printf(char* fmt,...)
{
	
	uint16_t temp; 
	va_list ap; 
	va_start(ap, fmt);
	vsprintf((char*)USART_ESP_TX_BUF,fmt,ap);
	va_end(ap);
	temp = strlen((const char*)USART_ESP_TX_BUF);		
	for(uint16_t i = 0; i < temp; i++)						
	{
	  //while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET)
		//{
			USART_SendData(USART2,USART_ESP_TX_BUF[i]); 
		//}
	}
}


void esp8266_start_trans(void)
{
	
	esp8266_send_cmd("AT+CWMODE=2","OK",50);//设置为AP模式
 
	esp8266_send_cmd("AT+RST","ready",20);//重启
	
	delay_ms(1000);       
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	esp8266_send_cmd("AT+CWSAP=\"ESP8266\",\"12345678\",1,4","OK",200);//设置WiFi名称、密码，模式
	esp8266_send_cmd("AT+CIPMUX=1","OK",20);//进入透传模式
	esp8266_send_cmd("AT+CIPSERVER=1,8080","OK",200);//设置端口8080
	esp8266_send_cmd("AT+CIPSEND","OK",50);//开始发送数据
}
 
//退出透传模式
u8 esp8266_quit_trans(void)
{
	u8 result=1;
	proc_printf("+++");
	delay_ms(1000);					
	result=esp8266_send_cmd("AT","OK",20);
	if(result)
		printf("quit_trans failed!");
	else
		printf("quit_trans success!");
	return result;
}
 
//发送指令，返回0发送成功，1则失败
uint8_t esp8266_send_cmd(char* cmd, char* ack, uint16_t waittime)
{
	u8 res=0; 
	USART_ESP_RX_STA=0;
	proc_printf("%s\r\n",cmd);	
	if(ack && waittime)		
	{
		while(--waittime)	
		{
			delay_ms(10);
			if(USART_ESP_RX_STA&0X8000)
			{
				if(esp8266_check_cmd(ack))
				{
					printf("ack:%s\r\n",(u8*)ack);
				
					break;
				}
					USART_ESP_RX_STA=0;
			} 
		}
		if(waittime==0) res = 1; 
	}
	return res;
} 
 
 
//检测是否应答指令
uint8_t* esp8266_check_cmd(char* str)
{
	char *strx=0;
	if(USART_ESP_RX_STA&0X8000)		
	{ 
		USART_ESP_RX_BUF[USART_ESP_RX_STA&0X7FFF]=0;
		strx=strstr((const char*)USART_ESP_RX_BUF,(const char*)str);
	} 
	return (uint8_t*)strx;
}
 
 
//向ESP8266发送指令（数据）的函数，暂时用不到，可以自己斟酌加上
//u8* esp8266_send_data(u8 *cmd,u16 waittime)
//{
 
//	char temp[5];
//	char *ack=temp;
//	USART3_RX_STA=0;
//	u3_printf("%s",cmd);	
//		LCD_ShowString(30,130,200,16,16,cmd);	
//	if(waittime)		
//	{
//		while(--waittime)	
//		{
//			delay_ms(10);
//			if(USART3_RX_STA&0X8000)
//			{
//				USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;
//				ack=(char*)USART3_RX_BUF;
//				printf("ack:%s\r\n",(u8*)ack);
//			LCD_ShowString(30,190,200,16,16,(u8*)ack);	
//				USART3_RX_STA=0;
//				break;
//			} 
//		}
//	}
//	return (u8*)ack;
//}