//宏定义缓冲队列最大存储上限
#define ESP_BUF_SIZE   1024     //ESP»º³åÇø×î´óÈÝÁ¿

//循环对列结构体
typedef struct 
{
    unsigned char buf[ESP_BUF_SIZE];
	unsigned short int length;
    unsigned short int fornt;               //ESP¶ÓÁÐÍ·Ö¸Õë
    unsigned short int rear;               //ESP¶ÓÁÐÎ²Ö¸Õë
}ESP_BufTypeDef;                     //¶¨ÒåESPÑ­»·¶ÓÁÐ»º³åÇø½á¹¹Ìå

//声明一个队列缓冲区，作为全局变量
ESP_BufTypeDef ESP_RX_BUF;      //Wifi´®¿Ú½ÓÊÕ»º³åÇø
//在头文件中声明外部变量，这样可以在其他C文件中调用
extern ESP_BufTypeDef ESP_RX_BUF;      //Wifi´®¿Ú½ÓÊÕ»º³åÇø
//接收缓冲区初始化ESP½ÓÊÕ»º³åÇø³õÊ¼»¯
void ESP_Rxbuf_Init(void)
{
	  int i ;
	  memset(ESP_RX_BUF.buf,0,sizeof(ESP_RX_BUF.buf));   //使用memset（）函数需要包含头文件<string.h>
//	for(i=0;i< ESP_BUF_SIZE; i++)
//	  {
//	      ESP_RX_BUF.buf[i] = 0;
//	  }
      ESP_RX_BUF.fornt = 0;
	  ESP_RX_BUF.length = 0;
	  ESP_RX_BUF.rear = 0;
	
	  ESP_RX_STATE = 0;          //ÔÊÐí½ÓÊÕÊý¾Ý
}

//读取ESP队列的数据¶ÁÈ¡espÊý¾Ý½ÓÊÕ¶ÓÁÐµÄÊý¾Ý
u8 ESP_Read_Quene_Data(ESP_BufTypeDef* Rx_buf)
{
    u8 read_data_temp;
	if(Rx_buf->length == 0)    //没有数据
	{
	    read_data_temp = 0;
	}
	else
	{
	    read_data_temp = Rx_buf->buf[Rx_buf->fornt];  //读出头指针所指的数据
		Rx_buf->fornt = (Rx_buf->fornt + 1) % ESP_BUF_SIZE;//头指针增加
		Rx_buf->length --;  //数据长度减少
	}
	return read_data_temp;  //返回读取的结果
}

/*-----------------------------------------
 *串口发送字符串函数´®¿Ú·¢ËÍ×Ö·û´®º¯Êý
 * USARTx Ö¸¶¨·¢ËÍµÄ´®¿Ú
 * *DataÖ¸¶¨´ý·¢ËÍµÄ×Ö·û´®
 * 发送遇到字符串结束符‘\0’结束·¢ËÍÓöµ½×Ö·û´®½áÊø·û'\0'½áÊø
-----------------------------------------*/
//这个函数讲真写的不是太好，有更好的大家可以修改
void USART_Send_String(USART_TypeDef* USARTx, u8 *Data, ...)
{//使用变长参数，具体实现原理可百度
	  //·ÖÅäÄÚ´æ
		 va_list valist;
	  //ÎªÊäÈëµÄ²ÎÊý³õÊ¼»¯
	   va_start(valist, Data);
	
    while(*Data != '\0')
		{
		    USART_SendData(USARTx, *Data);
			  while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); //µÈ´ý´®¿Ú·¢ËÍÍêÊý¾Ý
			  Data++;
		}
		
		//ÇåÀíÎªvalist±£ÁôµÄÄÚ´æ
		va_end(valist);
}

//讲真这是非常失败的函数，但是可以实现
//宏定义返回值
#define ACK_SUCCESS   1
#define ACK_DEFEAT    0

u8 ESP_Check_Ack(char *string)         //¼ì²éÏàÓ¦»Ø¸´ÐÅºÅ
{
      char *str_temp;               //被检测的字符串的临时变量
	  u8 data_temp;
	  u8 rx_buff_temp[150]={0};     //临时存放接收到的数据ÁÙÊ±´æ´¢½ÓÊÕµ½µÄÊý¾Ý
	  u8 pt_temp = 0;               //rx_buff_temp的下标rx_buff_tempµÄÏÂ±ê
	  u8 length_temp = 0;   //临时数组的当前长度
		
	  str_temp = string;
	  
	  if(ESP_RX_STATE > 0)    //Èç¹û½ÓÊÕÊý¾Ý½áÊø
		{
			//»ñÈ¡ÊÕµ½µÄ»Ø¸´ ÖÁÁÙÊ±Êý×é£¬±ãÓÚÅÐ¶Ï		
		    do
			  {
				  if(length_temp < 150)
				  {
				      data_temp = ESP_Read_Quene_Data(&ESP_RX_BUF);//从缓冲区读取一个值到数组
			          rx_buff_temp[pt_temp] = data_temp;
				      pt_temp ++;  //下标向后移动一位

			          length_temp ++;
			       }
				  else 
					    break;  //³¬³ö´æ´¢ÉÏÏÞ£¬Ã»ÓÐÊÕµ½¡®\0¡¯Ôò»áËÀÑ­»·£¬Ìø³öµ±Ç°Ñ­»·
		  	}
			  while(data_temp != '\0');
			
        ESP_RX_STATE --; //读取完一个字符串，接收区计数减一¶ÁÈ¡ÍêÒ»¸ö½ÓÊÕµÄ×Ö·û´®£¬¼ÆÊý-1									    
		}	
		//ÅÐ¶ÏÊÇ·ñ·ûºÏÆÚÍûÐÅºÅ
		if(strstr((const char *)rx_buff_temp, (const char *)str_temp ) != NULL)  //检测到有想要的回复，就能得到不为空的地址
				
			   return ACK_SUCCESS;   //返回成功Èç¹û·µ»ØµØÖ·²»Îª¿Õ£¬·µ»ØÓÐÐ§			
		else
			   return ACK_DEFEAT;    //如果没有，就是失败·ñÔò£¬·µ»ØÊ§°Ü
}

