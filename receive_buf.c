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

