#include "drv_rtc.h"

void RTC_Config(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);

  /* LSI used as RTC source clock */
  /* The RTC Clock may varies due to LSI frequency dispersion. */   
  /* Enable the LSI OSC */ 
  RCC_LSICmd(ENABLE);

  /* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
   
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();

	RTC_InitTypeDef RTC_InitStructure;
  /* Calendar Configuration with LSI supposed at 32KHz */
  RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
  RTC_InitStructure.RTC_SynchPrediv  = 0xFF; /* (32KHz / 128) - 1 = 0xFF*/
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);  

  /* EXTI configuration *******************************************************/
//  EXTI_ClearITPendingBit(EXTI_Line22);
//  EXTI_InitStructure.EXTI_Line = EXTI_Line22;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure);
  
//	NVIC_InitTypeDef   NVIC_InitStructure;
//  /* Enable the RTC Wakeup Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);  

//  /* Configure the RTC WakeUp Clock source: CK_SPRE (1Hz) */
//  RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
//  RTC_SetWakeUpCounter(0x00);

//  /* Enable the RTC Wakeup Interrupt */
//  RTC_ITConfig(RTC_IT_WUT, ENABLE);
//  
//  /* Enable Wakeup Counter */
//  RTC_WakeUpCmd(ENABLE);
	
}

void RTC_AlarmConfig(void)
{
//  EXTI_InitTypeDef EXTI_InitStructure;
//  RTC_AlarmTypeDef RTC_AlarmStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
//  
////  /* EXTI configuration */
////  EXTI_ClearITPendingBit(EXTI_Line17);
////  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
////  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
////  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
////  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
////  EXTI_Init(&EXTI_InitStructure);
//  
//  /* Enable the RTC Alarm Interrupt */
//  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
//  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStructure);
// 
//  /* Set the alarm A Masks */
//  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_All;
//  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
//  RTC_AlarmStructure.RTC_AlarmDateWeekDay = RTC_Weekday_Monday;
//  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours = 0x0;
//  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes =0x0;
//  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds =0x0;
//  RTC_SetAlarm(RTC_Format_BIN, RTC_Alarm_A, &RTC_AlarmStructure);
//  
//  /* Set alarm A sub seconds and enable SubSec Alarm : generate 8 interrupts per Second */
//  RTC_AlarmSubSecondConfig(RTC_Alarm_A, 0xFF, RTC_AlarmSubSecondMask_All);

//  /* Enable alarm A interrupt */
//  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
}

//void RTC_TimeAndDate_Show(void)
//{
//   uint8_t Rtctmp=0;
//   char LCDTemp[100];
//   RTC_TimeTypeDef RTC_TimeStructure;
//   RTC_DateTypeDef RTC_DateStructure;

//   while (1) {
//      // 获取日历
//      HAL_RTC_GetTime(&Rtc_Handle, &RTC_TimeStructure, RTC_FORMAT_BIN);
//      HAL_RTC_GetDate(&Rtc_Handle, &RTC_DateStructure, RTC_FORMAT_BIN);

//      // 每秒打印一次
//      if (Rtctmp != RTC_TimeStructure.Seconds) {

//            // 打印日期
//      printf("The Date :  Y:20%0.2d - M:%0.2d - D:%0.2d - W:%0.2d\r\n",
//                  RTC_DateStructure.Year,
//                  RTC_DateStructure.Month,
//                  RTC_DateStructure.Date,
//                  RTC_DateStructure.WeekDay);

//            //液晶显示日期
//            //先把要显示的数据用sprintf函数转换为字符串，然后才能用液晶显示函数显示
//   sprintf(LCDTemp,"The Date :  Y:20%0.2d - M:%0.2d - D:%0.2d - W:%0.2d",
//                  RTC_DateStructure.Year,
//                  RTC_DateStructure.Month,
//                  RTC_DateStructure.Date,
//                  RTC_DateStructure.WeekDay);

//            LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);
//            LCD_DisplayStringLine_EN_CH(8,(uint8_t *)LCDTemp);

//            // 打印时间
//            printf("The Time :  %0.2d:%0.2d:%0.2d \r\n\r\n",
//                  RTC_TimeStructure.Hours,
//                  RTC_TimeStructure.Minutes,
//                  RTC_TimeStructure.Seconds);

//            //液晶显示时间
//            sprintf(LCDTemp,"The Time :  %0.2d:%0.2d:%0.2d",
//                  RTC_TimeStructure.Hours,
//                  RTC_TimeStructure.Minutes,
//                  RTC_TimeStructure.Seconds);

//            LCD_DisplayStringLine_EN_CH(10,(uint8_t *)LCDTemp);

//            (void)RTC->DR;
//      }
//      Rtctmp = RTC_TimeStructure.Seconds;
//   }
//}