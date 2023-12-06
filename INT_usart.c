//串口接收中断函数´®¿Ú½ÓÊÕÖÐ¶Ïº¯Êý	
void USART2_IRQHandler(void)
{
  	u8 rev_byte;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)			//ÅÐ¶Ï¶È¼Ä´æÆ÷ÊÇ·ñÎª·Ç¿Õ
	 {
	    rev_byte = USART_ReceiveData(USART2);     //接收数据½ÓÊÕÊý¾Ý
										                                         
		if(ESP_RX_BUF.length <= ESP_BUF_SIZE) //如果数据没有溢出Èç¹ûÊý¾ÝÃ»ÓÐÒç³ö
		 {									 
		    ESP_RX_BUF.buf[ESP_RX_BUF.rear] = rev_byte;			//将数据存入缓冲区尾部½«Êý¾Ý´æÈëBUFF»º³åÇøÎ²²¿
	        ESP_RX_BUF.length ++;                           //缓冲区长度增加»º³åÇø³¤¶ÈÔö¼Ó
			ESP_RX_BUF.rear = (ESP_RX_BUF.rear + 1) % ESP_BUF_SIZE;  //尾指针+1，防止溢出，实现循环队列·ÀÖ¹Òç³ö
		 }		
		 //这里的TIM3其实可以用宏定义，这样可以方便更改使用的定时器
            TIM_SetCounter(TIM3,0);                         //定时器清空¼ÆÊýÆ÷Çå¿Õ
			TIM_Cmd(TIM3,ENABLE);                           //使能定时器Ê¹ÄÜ¶¨Ê±Æ÷	 
	  }
			
	  USART_ClearITPendingBit(USART2, USART_IT_RXNE);						//清除标志Çå³ý±êÖ¾
}	
————————————————
版权声明：本文为CSDN博主「qq_一串随机码」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_40329772/article/details/102701535
