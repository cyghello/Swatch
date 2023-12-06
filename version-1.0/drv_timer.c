#include "timer.h"


/*TIM1 PWM CH A8\A9\A10\A11---TIM1 PWM CHN B13\B14\B15\B11*/
//brief : all cycle = pwm time // dead time insertion 
//dead time // timer frequency :44M hz->22.72ns  1):2.905us(0xx) 2):5.811us(10x) 3):23.244us(110) 4):46.488(111)
//duty ratio : on/off time pulse = duty ratio * all cycle
//on/off time = on/off time - dead time
void drv_timer_pwm_init()
{
	
	TIM_TimeBaseInitTypeDef TIM1_Init;
	TIM_BDTRInitTypeDef  timer_deadtime;
	TIM_OCInitTypeDef timer_pwm;
	
	//NVIC_InitTypeDef IRQ_Tim2;
	
	TIM1_Init.TIM_Period = 0x226; //6E : 110				//1.外部输入脉冲检测 2.自动重装载寄存器 //cycle 700->400us 500->300us 
	TIM1_Init.TIM_Prescaler = 0x000A;
	TIM1_Init.TIM_ClockDivision = TIM_CKD_DIV1;			//没起作用？ 滤波器、死区
	TIM1_Init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM1_Init.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM1, &TIM1_Init);
	
	TIM_BDTRStructInit(&timer_deadtime);
	timer_deadtime.TIM_OSSRState = TIM_OSSRState_Disable;
	timer_deadtime.TIM_OSSIState = TIM_OSSIState_Disable;
	timer_deadtime.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	timer_deadtime.TIM_DeadTime = 0xAE; //死区时间  72:1us 172:3us 205:5us //b0 : 176->4us (6E:86: 134->3us AE : 1010 1110 ->5us)
	//timer_deadtime.TIM_Break = TIM_Break_Disable;                 //刹车功能使能
  //timer_deadtime.TIM_BreakPolarity = TIM_BreakPolarity_High;//刹车输入极性
  //timer_deadtime.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//自动输出使能
	
	TIM_BDTRConfig(TIM1,&timer_deadtime);
	
	timer_pwm.TIM_OCMode = TIM_OCMode_PWM1; //pwm1 & pwm2 out level are diferent TIM_OCMode_PWM1 : LOW AND LOW(now) \\TIM_OCMode_PWM2 :dead time//TIM_OCMode_Toggle : phase shift
	
	//timer_pwm.TIM_Pulse = 3000; // duty cycle
	timer_pwm.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	timer_pwm.TIM_OutputNState = TIM_OutputNState_Enable;
	timer_pwm.TIM_OCPolarity = TIM_OCPolarity_High;
	timer_pwm.TIM_OCNPolarity = TIM_OCNPolarity_High; //输出低  TIM_OCNPolarity_High TIM_OCNPolarity_Low
	timer_pwm.TIM_OCIdleState = TIM_OCIdleState_Reset;	//死区后输出状态
	timer_pwm.TIM_OCNIdleState = TIM_OCNIdleState_Reset;	//死区后互补端输出状态

	/*C1*/
	timer_pwm.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM1,&timer_pwm);
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable); //预装载器使能
	
	/*C2*/
	//timer_pwm.TIM_Pulse = 3000;
	timer_pwm.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OC2Init(TIM1,&timer_pwm);
	TIM_OC2PreloadConfig(TIM1,TIM_OCPreload_Disable); //预装载器使能
	/*C3*/
	//timer_pwm.TIM_Pulse = 3000;
	timer_pwm.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OC3Init(TIM1,&timer_pwm);
	TIM_OC3PreloadConfig(TIM1,TIM_OCPreload_Disable); //预装载器使能
	/*C4*/
	//timer_pwm.TIM_Pulse = 3000;
//	timer_pwm.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
//	TIM_OC4Init(TIM1,&timer_pwm);
//	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable); //预装载器使能
	
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
	
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);//使能PWM外围输出  
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
}
#define pwm_lengthA1 200
#define pwm_lengthB1 200
#define pwm_lengthA2 pwm_lengthA1/4
#define pwm_lengthB2 pwm_lengthB1/4
static int pwm_indexA = 0;
static int pwm_indexB = 0;
static int A_flag = 1;
static int B_flag = 0;
//static int pwm_listA[pwm_lengthA1] = {1117,1152,1186,1221,1255,1289,1323,1357,1390,1423,1456,1489,1521,1553,1584,1615,1645,
//1675,1704,1733,1760,1788,1814,1840,1866,1890,1914,1936,1958,1980,2000,2019,2038,
//2055,2072,2088,2103,2116,2129,2141,2151,2161,2170,2177,2184,2189,2193,2197,2199,
//2200,2200,2199,2197,2193,2189,2184,2177,2170,2161,2151,2141,2129,2116,2103,2088,
//2072,2055,2038,2019,2000,1980,1958,1936,1914,1890,1866,1840,1814,1788,1760,1733,
//1704,1675,1645,1615,1584,1553,1521,1489,1456,1423,1390,1357,1323,1289,1255,1221,
//1186,1152,1117,1083,1048,1014,979,945,911,877,843,810,777,744,711,679,
//647,616,585,555,525,496,467,440,412,386,360,334,310,286,264,242,
//220,200,181,162,145,128,112,97,84,71,59,49,39,30,23,16,
//11,7,3,1,0,0,1,3,7,11,16,23,30,39,49,59,
//71,84,97,112,128,145,162,181,200,220,242,264,286,310,334,360,
//386,412,440,467,496,525,555,585,616,647,679,711,744,777,810,843,
//877,911,945,979,1014,1048,1083,};
//static int pwm_listB[pwm_lengthB1] = {2200,2199,2197,2193,2189,2184,2177,2170,2161,2151,2141,2129,2116,2103,2088,2072,2055,
//2038,2019,2000,1980,1958,1936,1914,1890,1866,1840,1814,1788,1760,1733,1704,1675,
//1645,1615,1584,1553,1521,1489,1456,1423,1390,1357,1323,1289,1255,1221,1186,1152,
//1117,1083,1048,1014,979,945,911,877,843,810,777,744,711,679,647,616,
//585,555,525,496,467,440,412,386,360,334,310,286,264,242,220,200,
//181,162,145,128,112,97,84,71,59,49,39,30,23,16,11,7,
//3,1,0,0,1,3,7,11,16,23,30,39,49,59,71,84,
//97,112,128,145,162,181,200,220,242,264,286,310,334,360,386,412,
//440,467,496,525,555,585,616,647,679,711,744,777,810,843,877,911,
//945,979,1014,1048,1083,1117,1152,1186,1221,1255,1289,1323,1357,1390,1423,1456,
//1489,1521,1553,1584,1615,1645,1675,1704,1733,1760,1788,1814,1840,1866,1890,1914,
//1936,1958,1980,2000,2019,2038,2055,2072,2088,2103,2116,2129,2141,2151,2161,2170,
//2177,2184,2189,2193,2197,2199,2200,};
//static int pwm_listA[pwm_lengthA1] = {1152,1257,1359,1460,1557,1650,1738,1820,1896,1965,2025,2078,2121,2155,2180,2195,2200,
//2195,2180,2155,2121,2078,2025,1965,1896,1820,1738,1650,1557,1460,1359,1257,1152,
//1048,943,841,740,643,550,462,380,304,235,175,122,79,45,20,5,
//0,5,20,45,79,122,175,235,304,380,462,550,643,740,841,943,
//1048,};
//static int pwm_listB[pwm_lengthB1] = {2199,2189,2169,2140,2101,2053,1996,1931,1859,1780,1695,1604,1509,1410,1308,1205,1100,
//995,892,790,691,596,505,420,341,269,204,147,99,60,31,11,1,
//1,11,31,60,99,147,204,269,341,420,505,596,691,790,892,995,
//1100,1205,1308,1410,1509,1604,1695,1780,1859,1931,1996,2053,2101,2140,2169,2189,
//2199,};
//static int pwm_listA[40] = {1186,1357,1521,1675,1814,1936,2038,2116,2170,2197,2197,2170,2116,2038,1936,1814,1675,
//1521,1357,1186,1014,843,679,525,386,264,162,84,30,3,3,30,84,162,264,386,525,679,843,1014,};
//static int pwm_listB[40] = {2197,2170,2116,2038,1936,1814,1675,1521,1357,1186,1014,843,679,525,386,264,162,
//84,30,3,3,30,84,162,264,386,525,679,843,1014,1186,1357,1521,1675,1814,1936,2038,2116,2170,2197,};
//int pwm_count = 0;
/*------------- 载波 5k-----------*/
//static int pwm_listA[pwm_lengthA1] = {448,465,482,498,515,531,547,563,579,595,610,626,640,655,670,684,697,
//711,724,736,748,760,771,782,792,802,811,820,828,835,842,849,855,
//860,865,869,872,875,877,879,880,880,880,879,877,875,872,869,865,
//860,855,849,842,835,828,820,811,802,792,782,771,760,748,736,724,
//711,697,684,670,655,640,626,610,595,579,563,547,531,515,498,482,
//465,448,432,415,398,382,365,349,333,317,301,285,270,254,240,225,
//210,196,183,169,156,144,132,120,109,98,88,78,69,60,52,45,
//38,31,25,20,15,11,8,5,3,1,0,0,0,1,3,5,
//8,11,15,20,25,31,38,45,52,60,69,78,88,98,109,120,
//132,144,156,169,183,196,210,225,240,254,270,285,301,317,333,349,
//365,382,398,415,432,};
//static int pwm_listB[pwm_lengthB1] = {880,879,878,876,874,871,867,862,857,852,846,839,832,824,815,806,797,
//787,776,765,754,742,730,717,704,690,677,662,648,633,618,603,587,
//571,555,539,523,506,490,473,457,440,423,407,390,374,357,341,325,
//309,293,277,262,247,232,218,203,190,176,163,150,138,126,115,104,
//93,83,74,65,56,48,41,34,28,23,18,13,9,6,4,2,
//1,0,0,1,2,4,6,9,13,18,23,28,34,41,48,56,
//65,74,83,93,104,115,126,138,150,163,176,190,203,218,232,247,
//262,277,293,309,325,341,357,374,390,407,423,440,457,473,490,506,
//523,539,555,571,587,603,618,633,648,662,677,690,704,717,730,742,
//754,765,776,787,797,806,815,824,832,839,846,852,857,862,867,871,
//874,876,878,879,880,};
/*------------- 载波 8k-----------*/
static int pwm_listA[pwm_lengthA1] = {279,288,297,305,314,322,331,339,348,356,364,372,380,388,396,404,411,
419,426,433,440,447,454,460,466,472,478,484,490,495,500,505,509,
514,518,522,526,529,532,535,538,540,542,544,546,547,548,549,550,
550,550,550,549,548,547,546,544,542,540,538,535,532,529,526,522,
518,514,509,505,500,495,490,484,478,472,466,460,454,447,440,433,
426,419,411,404,396,388,380,372,364,356,348,339,331,322,314,305,
297,288,279,271,262,253,245,236,228,219,211,202,194,186,178,170,
162,154,146,139,131,124,117,110,103,96,90,84,78,72,66,60,
55,50,45,41,36,32,28,24,21,18,15,12,10,8,6,4,
3,2,1,0,0,0,0,1,2,3,4,6,8,10,12,15,
18,21,24,28,32,36,41,45,50,55,60,66,72,78,84,90,
96,103,110,117,124,131,139,146,154,162,170,178,186,194,202,211,
219,228,236,245,253,262,271,};
static int pwm_listB[pwm_lengthB1] = {550,550,549,548,547,546,544,542,540,538,535,532,529,526,522,518,514,
509,505,500,495,490,484,478,472,466,460,454,447,440,433,426,419,
411,404,396,388,380,372,364,356,348,339,331,322,314,305,297,288,
279,271,262,253,245,236,228,219,211,202,194,186,178,170,162,154,
146,139,131,124,117,110,103,96,90,84,78,72,66,60,55,50,
45,41,36,32,28,24,21,18,15,12,10,8,6,4,3,2,
1,0,0,0,0,1,2,3,4,6,8,10,12,15,18,21,
24,28,32,36,41,45,50,55,60,66,72,78,84,90,96,103,
110,117,124,131,139,146,154,162,170,178,186,194,202,211,219,228,
236,245,253,262,271,279,288,297,305,314,322,331,339,348,356,364,
372,380,388,396,404,411,419,426,433,440,447,454,460,466,472,478,
484,490,495,500,505,509,514,518,522,526,529,532,535,538,540,542,
544,546,547,548,549,550,550,};
void TIM1_UP_TIM10_IRQHandler()
{
	
	//TIM_SetCompare1(TIM1, 1100);
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		if (A_flag)
		{
			if (pwm_indexA > pwm_lengthA1)
			{
				A_flag = 0;
				pwm_indexA = 0;
			}
			TIM_SetCompare2(TIM1, pwm_listA[pwm_indexA]);
			if (pwm_indexA < pwm_lengthA2)
			{
				B_flag = 1;
				TIM_SetCompare3(TIM1, 0);
			}
			pwm_indexA++;
		}
		if (B_flag)
		{
			if (pwm_indexB > pwm_lengthA1)
			{
				B_flag = 0;
				pwm_indexB = 0;
			}
			TIM_SetCompare3(TIM1, pwm_listB[pwm_indexB]);
			if (pwm_indexB < pwm_lengthB2)
			{
				A_flag = 1;
				TIM_SetCompare2(TIM1, 0);
			}
			pwm_indexB++;
		}
		//if (pwm_index == 15)
		//pwm_index = 0;
		//TIM_SetCompare2(TIM1, pwm_listA[pwm_index]);
		//TIM_SetCompare3(TIM1, pwm_list[pwm_index]);
		//pwm_index++;
	}
//	pwm_NUM++;
	//TIM_SetCompare4(TIM1, 1100);
//	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)	
// 	{		
//		pwm_index++;
//		if(pwm_index>35)
//		{
//			pwm_index=0;
//			pwm_count++;
//			if(pwm_count>3)pwm_count=0;
//			
//			if(pwm_count==0)TIM1->CCER=0x2ABB;
//			if(pwm_count==1)TIM1->CCER=0x2BBA;
//			if(pwm_count==2)TIM1->CCER=0x3BAA;
//			if(pwm_count==3)TIM1->CCER=0x3AAB;
//				
//		}
//		TIM1->CCR1 = indexWave[pwm_index];	
//		TIM1->CCR2 = indexWave[pwm_index];	
//		TIM1->CCR3 = indexWave[pwm_index];	
//		TIM1->CCR4 = indexWave[pwm_index];
		
		TIM_ClearITPendingBit (TIM1, TIM_IT_Update);	
//	}
}

void drv_pwm_ccr_value_write (uint8_t channel, uint32_t ccr_value)
{
	if (channel == 1)
	TIM_SetCompare1(TIM1, ccr_value);
	if (channel == 2)
	TIM_SetCompare2(TIM1, ccr_value);
	if (channel == 3)
	TIM_SetCompare3(TIM1, ccr_value);
	if (channel == 4)
	TIM_SetCompare4(TIM1, ccr_value);
}

void drv_hc_sr04_timer_init ()
{
	TIM_TimeBaseInitTypeDef TIM4_Init;
	
	TIM4_Init.TIM_Period = 0x03DE;				//1.外部输入脉冲检测 2.自动重装载寄存器 
	TIM4_Init.TIM_Prescaler = 0x0004;		//分频系数 + 1
	TIM4_Init.TIM_ClockDivision = TIM_CKD_DIV1;			//没起作用？ 滤波器、死区  分频
	TIM4_Init.TIM_CounterMode = TIM_CounterMode_Up;
	TIM4_Init.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(TIM4, &TIM4_Init);
	
	 NVIC_InitTypeDef NVIC_InitStructure;
   //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;    
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       
   NVIC_Init(&NVIC_InitStructure);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update); 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); 
	TIM_Cmd(TIM4,DISABLE);
}
static uint16_t tim_count = 0;

void TIM4_IRQHandler(void)
{
		if (TIM_GetFlagStatus(TIM4, TIM_FLAG_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);	
			tim_count++;
	}
}

int get_tim_count ()
{
	int a = 0;
	a = tim_count;
	if (a >= 10)
	{		
		tim_count = 0;
		return 1;
	}
	else return 0;
	
}
uint32_t getechotimer()
{
	uint32_t t = 0;
	t = tim_count *1000;
	t += TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4,0);
	tim_count = 0;
	//TIM4->CNT = 0; 
	for (int i = 0; i < 1000000; i++);
	return t;
}