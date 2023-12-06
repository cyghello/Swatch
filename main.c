#define wifi_information  "AT+CWJAP_DEF=\"wifi名称\",\"wifi密码\"\r\n"
#define tcp_information "AT+CIPSTART=\"TCP\",\"TCP地址\",端口号\r\n" 


 if(ESP_Send_Cmd("AT\r\n","OK",20) == ACK_DEFEAT) //测试一下AT命令
 {
      delay_ms(50);
	  ESP_Send_Cmd("+++","",0);    //ÍË³öÍ¸´«Ä£Ê½
	  delay_ms(50);
 }
 
 ESP_Send_Cmd("AT+CWMODE=1\r\n","OK",20);//设置成Station模式
 //一定要重启！！！
 ESP_Send_Cmd("AT+RST\r\n","ready",20);
 delay_ms(1000);   //一般1s就可以，也可以设置时间长一些
 ESP_Rxbuf_Init(); //往往启动是时候模块会发版本信息，清空一下

 printf("Connecting to Wifi.\r\n");
 if(ESP_Send_Cmd("AT+CWJAP_DEF?\r\n","No AP",50) == ACK_SUCCESS)   //返回没有连接AP·µ»ØÃ»ÓÐÁ¬½ÓAP
 {
     for(count_up = 0; count_up < 5; count_up ++ )       //Ñ­»·Á¬½Ó5´Î
     {
         if(ESP_Send_Cmd(wifi_information, "WIFI GOT IP", 600) == ACK_SUCCESS)    //如果连接成功Èç¹ûÁ¬½Ó³É¹¦
         {
              printf("Have conntected.\r\n");
              break;
         }else 
		 {
              printf("Rejoin Wifi.\r\n");
		 }
     }
 }
 //此处可以添加如果重连5次都失败的处理方法
 
    /*有时候遇到部分8266在链接TCP后不能进行单路链接设置*/
  ESP_Send_Cmd("AT+CIPMUX=0\r\n","OK",15);      //单路连接模式
  ESP_Send_Cmd(tcp_information, "CONNECT", 50); //连接到TCP
     //这里其实就可以使用发送数据函数ESP_Send_Data开始发数据了
     //ESP_Send_Data("Hllow word!\n")

  ESP_Send_Cmd("AT+CIPMODE=1\r\n","OK",20)；    //进去透传模式
  ESP_Send_Cmd("AT+CIPSEND\r\n","OK",20)；      //进入透传模式
//透传模式直接使用串口发送函数即可
  USART_Send_String(USART2, "Anything!");    

