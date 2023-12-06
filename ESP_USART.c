//宏定义
//ÍøÂç´®¿ÚÊ±ÖÓ
#define ESP_RCC       RCC_APB1Periph_USART2

//ÍøÂç´®¿Ú·¢ËÍ¶Ë¿Ú
#define ESP_TX_PIN    GPIO_Pin_2    //PA2
#define ESP_TX_GPIO   GPIOA

//ÍøÂç´®¿Ú½ÓÊÕ¶Ë¿Ú
#define ESP_RX_PIN    GPIO_Pin_3   //PA3
#define ESP_RX_GPIO   GPIOA

#define ESP_USART     USART2

//wifi串口初始化 wifi´®¿Ú³õÊ¼»¯
void ESP_Usart_Config(void)
{
	  GPIO_InitTypeDef  GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);                    //¿ªÆôGPIOAÊ±ÖÓ
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);                     //¿ªÆô¶Ë¿Ú¸´ÓÃÊ±ÖÓ
	
    RCC_APB1PeriphClockCmd(ESP_RCC, ENABLE);                                 //¿ªÆôesp´®¿ÚÊ±ÖÓ

	  USART_DeInit(ESP_USART);																								//¸´Î»esp´®¿Ú
	
//发送端口		·¢ËÍ¶Ë¿Ú
	  GPIO_InitStructure.GPIO_Pin = ESP_TX_PIN;																				//PA2
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;																	//¸´ÓÃÍÆÍìÊä³ö
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(ESP_TX_GPIO, &GPIO_InitStructure);
	
//接收端口		½ÓÊÕ¶Ë¿Ú
	  GPIO_InitStructure.GPIO_Pin = ESP_RX_PIN;																		  	//PA3
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;														//¸´ÓÃ¸¡¿ÕÊäÈë	
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(ESP_RX_GPIO, &GPIO_InitStructure);	
		
	  //ÅäÖÃ´®¿ÚÄ£Ê½  
		USART_DeInit(ESP_USART);
	  USART_InitStructure.USART_BaudRate = 115200;																			//ÉèÖÃ²¨ÌØÂÊÎª115200bps
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;												//Êý¾ÝÎ»Îª8Î»
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;														//Í£Ö¹Î»1Î»
	  USART_InitStructure.USART_Parity = USART_Parity_No;																//ÎÞÐ£ÑéÎ»
	  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;										//·¢ËÍ¡¢½ÓÊÕÄ£Ê½´ò¿ª
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//ÎÞÓ²¼þ¿ØÖÆÁ÷¿Ø
	
	  USART_Init(ESP_USART, &USART_InitStructure);																		//´«ËÍÅäÖÃ²ÎÊý
	
	  USART_ClearFlag(ESP_USART, USART_FLAG_CTS);																			//Çå³ý·¢ËÍÍê³É±êÖ¾Î»
    USART_Cmd(ESP_USART, ENABLE);																										//Ê¹ÄÜ´®¿Ú1	  	
	
	  USART_ITConfig(ESP_USART, USART_IT_RXNE, ENABLE);																//¿ªÆô½ÓÊÕÖÐ¶Ï £¨1×Ö½ÚÒ»´ÎÖÐ¶Ï£©
//		USART_ITConfig(ESP_USART, USART_IT_IDLE, ENABLE);																//¿ªÆô¿ÕÏÐÖÐ¶Ï£¨8×Ö½ÚÒ»´ÎÖÐ¶Ï£©
		
		
    //ÉèÖÃNVIC
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	  
	  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;																	//ÉèÖÃ´®¿Ú2ÖÐ¶Ï
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0;													//ÇÀÕ¼ÓÅÏÈ¼¶
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;																//×ÓÓÅÏÈ¼¶Îª1
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;																		//Ê¹ÄÜ
	  NVIC_Init(&NVIC_InitStructure);		

    printf("## ESP_usart_config_over ##\r\n");
}
