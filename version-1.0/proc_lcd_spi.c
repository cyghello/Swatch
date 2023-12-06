#include "proc_lcd_spi.h"
#include "pctl_lcd_pc_array.h"


void proc_lcd_battery_icon ()
{
	//pctl_lcd_set_rectangle (0, 10, 0, 25, WHITE);
//	pctl_lcd_set_rectangle(0, 10, 0, 4, WHITE);
//	pctl_lcd_set_rectangle(0, 10, 5, 6, BLACK);
//	pctl_lcd_set_rectangle(0, 10, 7, 10, WHITE);
//	pctl_lcd_set_rectangle(0, 10, 11, 12, BLACK);
//	pctl_lcd_set_rectangle(0, 10, 13, 16, WHITE);
//	pctl_lcd_set_rectangle(0, 10, 17, 18, BLACK);
//	pctl_lcd_set_rectangle(0, 10, 19, 22, WHITE);
//	pctl_lcd_set_rectangle(0, 10, 23, 24, BLACK);
//	pctl_lcd_write_char (112 ,10, 8, 16, character8_16[0]);
//	pctl_lcd_write_char (96 ,10, 8, 16, character8_16[0]);
//	pctl_lcd_write_char (80 ,10, 8, 16, character8_16[0]);
//	pctl_lcd_write_char (64 ,10, 16, 32, character16_32[1]);
//	pctl_lcd_write_char (48 ,10, 16, 32, character16_32[1]);
//	pctl_lcd_write_char (32 ,10, 16, 32, character16_32[1]);
	
	
	
}

uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}
/*
*		@breif : 打印ASCLL码对应的字符 才对
*/
void proc_lcd_print_asc (unsigned char start_x,unsigned char start_y,unsigned char font_wide,
														unsigned char font_high, uint32_t number, uint8_t length)
{
	uint8_t i;
	if ((font_high == 16) && (font_wide == 8))
	{
		//for (i = 0; i < length; i++)							
			pctl_lcd_write_char(start_x, start_y, font_wide, font_high, character8_16[number]);
		
	}
	else if ((font_high == 32) && (font_wide == 16))
	{
		//for (i = 0; i < length; i++)							
		//{
			pctl_lcd_write_char(start_x, start_y, font_wide, font_high, character16_32[number]);
		//}
	}
}

void proc_lcd_print_number (unsigned char start_x,unsigned char start_y,unsigned char font_wide,
														unsigned char font_high, uint32_t number, uint8_t length)
{
	//int temp_num;
//	int num_length = 0;
//	do
//	{
//		num_length++;
//	}while ((number/10));
	int asc_num;
	for (int i = 0; i < length; i++)
	{
			asc_num = number / OLED_Pow(10, length - i - 1) % 10;
			//asc_num = number / OLED_Pow(10, length - i - 1) % 10 + '0';
			proc_lcd_print_asc (start_x, start_y, font_wide, font_high, asc_num, length);
			start_x = start_x - font_wide;
	}
}

void proc_lcd_print_time()
{
		RTC_TimeTypeDef RTC_TimeStruct;
		RTC_DateTypeDef RTC_DateStruct;
		RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
		RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
		proc_lcd_print_number (112 ,10, 8, 16, RTC_TimeStruct.RTC_Hours, 2);
		proc_lcd_print_asc (96 ,10, 8, 16, 10, 2);
		proc_lcd_print_number (80 ,10, 8, 16, RTC_TimeStruct.RTC_Minutes, 2);
		proc_lcd_print_asc (64 ,10, 8, 16, 10, 2);
		proc_lcd_print_number (48 ,10, 8, 16, RTC_TimeStruct.RTC_Seconds, 2);
}