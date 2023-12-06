/*--------------------------------------------------
 * ·¢ËÍÖ¸Áî£¬Ï£ÍûµÃµ½»Ø¸´
 * *cmd 发送的命令
 * *ack 希望得到的回复
 * waittime 等待的时长
 * ·µ»ØÖµ ACK_SUCCESS£¬·¢ËÍ³É¹¦
 *        ACK_DEFEAT£¬·¢ËÍÊ§°Ü
---------------------------------------------------*/
u8 ESP_Send_Cmd(char *cmd, char *ack, u16 waittime )
{//其实这里也可以写成边长参数的，而且会极大的方便后面发送命令，不过博主是写完功能了才学会的边长参数，后面我会在我程序中修改
    USART_Send_String(ESP_USART, (u8 *)cmd);  //直接使用发送字符串函数
	  while(waittime-- )
		{
		    if(ESP_Check_Ack(ack) == ACK_SUCCESS)
				{
				   return ACK_SUCCESS;
				}
				delay_ms(10);  //每次等待10ms，所以waittime为20的时候，实际等待200ms
		}
	  return ACK_DEFEAT;
}


/*----------------------------------------------------
 * ·¢ËÍÊý¾Ý¸øwifiÄ£¿é£¬
 *  *data为要发送的数据*dataÎª·¢ËÍµÄÊý¾Ý
----------------------------------------------------*/
void ESP_Send_Data(u8 *data)
{
      char cmdbuf_temp[32];  //整合命令使用的临时数组
	  unsigned short len;    //发送数据的长度
	  len = sizeof(data);    
	  sprintf(cmdbuf_temp,"AT+CIPSEND=%d\r\n", len);//格式化的命令写入命令字符串中，就是把长度加上°Ñ¸ñÊ½»¯µÄÊý¾ÝÐ´ÈëÄ³¸ö×Ö·û´®ÖÐ
	
	  if(ESP_Send_Cmd(cmdbuf_temp, ">", 200) == ACK_SUCCESS)  //检测接收数据是否包含‘>’¼ì²é½ÓÊÕÊý¾ÝÊÇ·ñÎª¡°>¡±
		{
		    USART_Send_String(ESP_USART, data);			           //发送数据·¢ËÍÊý¾Ý
		}
}

