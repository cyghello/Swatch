//定义一个全局变量用来指示是否接收到数据
//超过10ms没有收到数据认为接收结束，则ESP_RX_STATE增加1。即定时器中断就加1
u8 ESP_RX_STATE = 0;          //³õÊ¼»¯ÒÑ½ÓÊÕÊý¾ÝÎª0
//在头文件中声明外部变量，这样可以在其他C文件中调用
extern u8 ESP_RX_STATE;            //½ÓÊÕÍê³É×´Ì¬

//定时器TIM3中断优先级配置¶¨Ê±Æ÷TIM3ÖÐ¶ÏÓÅÏÈ¼¶ÅäÖÃ
void TIM3_NVIC_config(void)
{	
        NVIC_InitTypeDef NVIC_InitStructure;
    
	    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);           //ÉèÖÃ×éÓÅÏÈ¼¶
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           //ÉèÖÃ¶¨Ê±Æ÷3ÖÐ¶ÏÏß
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //ÉèÖÃÇÀÕ¼ÓÅÏÈ¼¶
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //ÉèÖÃ×ÓÓÅÏÈ¼¶2
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //Ê¹ÄÜIRQÖÐ¶Ï 
		NVIC_Init(&NVIC_InitStructure);
}

//定时器TIM3初始化，10ms¶¨Ê±Æ÷TIME3³õÊ¼»¯,10ms
void TIM3_init(void)
{
      TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;            //TIM3³õÊ¼»¯½á¹¹Ìå 
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	    //¿ªÆôÊ±ÖÓ
	  TIM_DeInit(TIM3);                                         //½«ÍâÉèTIM3¼Ä´æÆ÷ÖØÉèÎªÈ±Ê¡Öµ
	  
	  TIM_TimeBaseStructure.TIM_Period = (2000-1);                  //×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷Öµ
	  TIM_TimeBaseStructure.TIM_Prescaler =(3600-1);            //Ê±ÖÓÔ¤·ÖÆµÊý	
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    //²ÉÑù·ÖÆµ£¬Ê¹¼ÆÊ±Æ÷¹¤×÷ÆµÂÊÎª72MHz
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//ÏòÉÏ¼ÆÊýÄ£Ê½
	
	  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);             //ÅäÖÃ¶¨Ê±Æ÷
	
	  TIM3_NVIC_config();                                        //ÅäÖÃTIM3ÖÐ¶ÏÓÅÏÈ¼¶
	
	  TIM_ClearFlag(TIM3, TIM_FLAG_Update);                      //Çå³ý±êÖ¾Î»
	  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                 //ÖÐ¶ÏÅäÖÃ
//	  TIM_Cmd(TIM3, ENABLE);                                     //Ê¹ÄÜ¶¨Ê±Æ÷TIM3
}
//TIM3中断函数TIM3ÖÐ¶Ïº¯Êý
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)          //²úÉúÖÐ¶Ï
		{		   

			ESP_RX_STATE ++;             //超过10ms，数据接收完毕，计数+1 ³¬¹ý10ms£¬Êý¾Ý½ÓÊÕÍê±Ï£¬¼ÆÊý+1
        						
		}
  	TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);  //	Çå³ýÖÐ¶Ï±êÖ¾
		
		TIM_Cmd(TIM3, DISABLE);   //¹Ø±ÕTIM3
}
