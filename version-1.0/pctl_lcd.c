#include "pctl_lcd.h"
#include "pctl_spi.h"

void pctl_lcd_gpio_init ()
{
	drv_init_gpio_out(GPIOB, GPIO_Pin_0);		//lcd_reset
	drv_init_gpio_out(GPIOB, GPIO_Pin_1);		//lcd_cmd_data
	drv_init_gpio_out(GPIOB, GPIO_Pin_2);		//lcd_back_light
	
}

void pctl_lcd_reset ()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	for (int i = 0; i < 90000; i++);			//延时
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	for(int j = 0; j < 700000; j++);			//延时
	GPIO_SetBits(GPIOB, GPIO_Pin_0);
	for(int k = 0; k < 90000; k++);			//延时
	
}

void pctl_spi_to_lcd_write_data (uint8_t data)
{
	//GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	pctl_spi_write_start ();
	GPIO_SetBits(GPIOB, GPIO_Pin_1);//
	pctl_spi_write_byte (data);
	for (int i = 0; i < 100; i++);
	pctl_spi_write_stop ();
}

void pctl_spi_to_lcd_cmd (uint8_t data)
{
	//GPIO_SetBits(GPIOB, GPIO_Pin_1);
	GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	pctl_spi_write_start ();
	pctl_spi_write_byte (data);
	for (int i = 0; i < 100; i++);
	pctl_spi_write_stop ();
}
/*
* @：设置帧大小
*/
void pctl_lcd_set_frame_size (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end)
{
	pctl_spi_to_lcd_cmd (0x2A);	//列地址设置
	pctl_spi_to_lcd_write_data (x_start >> 8); //pctl_spi_to_lcd_write_data (x_start + 2);
	pctl_spi_to_lcd_write_data (x_start);
	pctl_spi_to_lcd_write_data (x_end >> 8);	//pctl_spi_to_lcd_write_data (x_end + 2);
	pctl_spi_to_lcd_write_data (x_end);
	
	pctl_spi_to_lcd_cmd (0x2B);	//行地址设置
	pctl_spi_to_lcd_write_data (y_start >> 8); //pctl_spi_to_lcd_write_data (y_start + 2);
	pctl_spi_to_lcd_write_data (y_start);
	pctl_spi_to_lcd_write_data (y_end >> 8);	//pctl_spi_to_lcd_write_data (y_end + 2);
	pctl_spi_to_lcd_write_data (y_end);
	
	pctl_spi_to_lcd_cmd (0x2C); //写入内存

}

/*
* @: 设置背景颜色 130 * 130
*/
void pctl_lcd_set_background (uint16_t color)
{
	uint8_t i, j;
	pctl_lcd_set_frame_size (0, 0xA0, 0, 0xA0);
	//pctl_spi_to_lcd_cmd (0x2C); //写入内存
	for (uint8_t i = 0; i < 160; i++)
	{
		for (uint8_t j = 0; j <160; j++)
		{
			pctl_spi_to_lcd_write_data (color >> 8);
			pctl_spi_to_lcd_write_data (color);
		}
	}
}

void pctl_lcd_set_scan_dir (uint8_t data)
{
	pctl_spi_to_lcd_cmd (0x36);	// 定义帧内存的读写扫描方向
	pctl_spi_to_lcd_write_data (data);
}

void pctl_lcd_set_color_format (uint8_t data)
{
	pctl_spi_to_lcd_cmd (0x3A);	// 定义通过MCU接口传输的RGB图片数据的格式
	pctl_spi_to_lcd_write_data (data);
}

void pctl_lcd_set_point (uint16_t x, uint16_t y, uint16_t color)
{
	pctl_lcd_set_frame_size (x, x + 1, y, y + 1);
	pctl_spi_to_lcd_write_data (color >> 8);
	pctl_spi_to_lcd_write_data (color);
	
}
/*
*	@brief : print a character y * x : line * row
* @notes : print character what genenter by ... dir? scan? low or high? 
* @para  : because of pctl_lcd_set_point function , x exchange y; 
*				 : start_x ,start_y, font_wide, font_high, ch
*/
void pctl_lcd_write_char (unsigned char start_x,unsigned char start_y,
												unsigned char font_wide, unsigned char font_high, const unsigned char *ch)
{
	unsigned char ch_wide = 8;
	const unsigned char *temp_ad = ch;
//	unsigned char wide_ccter = 0;
	unsigned char high_surplus = 0;
//	unsigned char all_ccter = 0;
	unsigned char cpos_x = 0;
	unsigned char cpos_y = 0;
	unsigned char temp = 0;
//	all_ccter = (font_wide / 8) * font_high;
	high_surplus = font_wide / ch_wide;
	while ((high_surplus--) != 0)
	{
		cpos_x = start_x + (high_surplus * 8);
		cpos_y = start_y;
		for (int i = 0; i < font_high; i++)
		{
			temp = *temp_ad++; 
			for (int j = 0; j < ch_wide; j++)
			{
					if (temp & 0x80)
					pctl_lcd_set_point (cpos_y + i, cpos_x + j, RED);
					else 
					pctl_lcd_set_point (cpos_y + i, cpos_x + j, BLUE);
				temp <<= 1;
			}
		}
	}
}
/*
*	@brief : 显示图片
*/
void pctl_lcd_display_pic (uint16_t *ch)
{
	int len = 0;
	int wide = 0;
	int weight = 0;
	int temp_ad_num;
	int temp_ad_num_1;
	temp_ad_num = temp_ad_num_1 = 0;
	len = 46;
	wide = 64;
	uint16_t *temp_ad = ch;

	//const unsigned char *temp_ad_1 = ch;
	for (int i = 0; i < wide; i++)
	{
			for (int j = 0; j < len; j++)
			{
				pctl_lcd_set_point (i, j, temp_ad[temp_ad_num]);
				temp_ad_num++;
			}
//		if (i % 2 == 0)
//		{
//			for (int j = 0; j < len; j++)
//			{
//				pctl_lcd_set_point (i, j, temp_ad[temp_ad_num]);
////				pctl_lcd_set_frame_size (i , i + 1, j, j + 1);
////				pctl_spi_to_lcd_write_data (gimage_16[temp_ad_num] >> 8);
////				//temp_ad_num++;
////				pctl_spi_to_lcd_write_data (gimage_16[temp_ad_num]);
//				temp_ad_num++;
//			}
//			temp_ad_num_1 = temp_ad_num;
//		}
//		else if (i % 2 == 1)
//		{
//			//temp_ad_num_1 += 64;
//			for (int j = 0; j < len; j++)
//			{
//				pctl_lcd_set_point (i, j, temp_ad[temp_ad_num]);
////				pctl_lcd_set_frame_size (i , i + 1, j, j + 1);
////				pctl_spi_to_lcd_write_data (gimage_16[temp_ad_num_1] >> 8);
////				//temp_ad_num_1--;
////				//temp_ad_num++;
////				pctl_spi_to_lcd_write_data (gimage_16[temp_ad_num_1]);
//				//temp_ad_num_1--;
//				temp_ad_num++;
//			}
//		}

	}
}
void pctl_lcd_set_rectangle (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end, uint16_t color)
{
	uint8_t w, h;
	w = x_end - x_start;
	h = y_end - y_start;
	
	pctl_lcd_set_frame_size (x_start, x_end, y_start, y_end);
	
	for (uint8_t i = 0; i <= w; i++)
	{
		for (uint8_t j = 0; j < h; j++)
		{
			pctl_spi_to_lcd_write_data (color >> 8);
			pctl_spi_to_lcd_write_data (color);
		}
	}
	
}
/*
* @: 
*/
void pctl_lcd_dispgrayhor16 ()
{
	pctl_lcd_set_frame_size (0, 127, 0, 127);
	for (uint8_t i = 0; i < 128; i++)
	{
		for (uint8_t j = 0; j < 16; j++)
		{
			for (uint8_t k = 0; k < (128/16); k++)
			{
				pctl_spi_to_lcd_write_data (((j*2) <<3)|((j*4) >> 3));
				pctl_spi_to_lcd_write_data (((j*4) <<5)|(j*2));
			}
		}
	}
	
}

/*
* @: 
*/
void pctl_dispframe ()
{
	pctl_lcd_set_frame_size (0, 127, 0, 127);
	pctl_spi_to_lcd_write_data (0xF8);
	pctl_spi_to_lcd_write_data (0x00);
	
	for (uint8_t i = 0; i < 126; i++)
	{
		pctl_spi_to_lcd_write_data (0xFF);
		pctl_spi_to_lcd_write_data (0xFF);
	}
	
	pctl_spi_to_lcd_write_data (0x00);
	pctl_spi_to_lcd_write_data (0x1F);
	
	for (uint8_t j = 0; j < 126; j++)
	{
		pctl_spi_to_lcd_write_data (0xF8);
		pctl_spi_to_lcd_write_data (0x00);
		for (uint8_t k = 0; k < 126; k++)
		{
			pctl_spi_to_lcd_write_data (0x00);
			pctl_spi_to_lcd_write_data (0x00);
		}
		pctl_spi_to_lcd_write_data (0x00);
		pctl_spi_to_lcd_write_data (0x1F);
	}
	pctl_spi_to_lcd_write_data (0xF8);
	pctl_spi_to_lcd_write_data (0x00);
	
	for (uint8_t l = 0; l < 126; l++)
	{
		pctl_spi_to_lcd_write_data (0xFF);
		pctl_spi_to_lcd_write_data (0xFF);
	}
	pctl_spi_to_lcd_write_data (0x00);
	pctl_spi_to_lcd_write_data (0x1F);
}

/*
* @: 
*/
void pctl_dispband ()
{
	uint16_t color[] = {0x001F, 0x07E0, 0xF800, 0x07FF, 0xF81F, 0xFFE0, 0x0000, 0xFFFF};
	pctl_spi_to_lcd_cmd (0x36);
	pctl_spi_to_lcd_write_data  (0x08);
	
	pctl_lcd_set_frame_size (0, 127, 0, 127);
	
	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < (128/8); j++)
		{
			for (uint8_t k = 0; k < 128; k++)
			{
				pctl_spi_to_lcd_write_data (color[i] >> 8);
				pctl_spi_to_lcd_write_data (color[i]);
			}
		}
	}
}

/*
* @: 
*/
void pctl_disppic (uint16_t x, uint16_t y,uint16_t w, uint16_t h, const unsigned char *p)
{
	unsigned char pic_h, pic_l;
	pctl_lcd_set_frame_size (x, x + w -1, y, y + h - 1);
	
	for (uint8_t i = 0; i < h; i++)
	{
		for (uint8_t j = 0; j < w; j++)
		{
			pic_l = (*p);
			pic_h = (*(p + 1));
			pctl_spi_to_lcd_write_data (pic_h);
			pctl_spi_to_lcd_write_data (pic_l);
			p = p + 2;
		}
	}
}

/*
* @: 
*/
void pctl_lcd_cfg ()
{
	pctl_lcd_reset ();
	pctl_spi_to_lcd_cmd (0x01);  //关闭睡眠模式
	for (int j = 0; j < 10000000; j++);
	pctl_spi_to_lcd_cmd (0x11);  //关闭睡眠模式
	for (int i = 0; i < 100000000; i++);
	
	pctl_spi_to_lcd_cmd(0xB1);  //设置全色正常模式的帧频
	pctl_spi_to_lcd_write_data(0x01);
	pctl_spi_to_lcd_write_data(0x2C);
	pctl_spi_to_lcd_write_data(0x2D);
	
	pctl_spi_to_lcd_cmd(0xB2);  //设置空闲模式的帧频
	pctl_spi_to_lcd_write_data(0x01);
	pctl_spi_to_lcd_write_data(0x2C);
	pctl_spi_to_lcd_write_data(0x2D);
	
	pctl_spi_to_lcd_cmd(0xB3);  //设置部分模式/全色的帧频率
	pctl_spi_to_lcd_write_data(0x01);
	pctl_spi_to_lcd_write_data(0x2C);
	pctl_spi_to_lcd_write_data(0x2D);
	pctl_spi_to_lcd_write_data(0x01);
	pctl_spi_to_lcd_write_data(0x2C);
	pctl_spi_to_lcd_write_data(0x2D);
	
	//===============inversion of control=============
	pctl_spi_to_lcd_cmd(0xB4);  //反转模式控制
	pctl_spi_to_lcd_write_data(0x07);		//0x03 、0x07

	//===============power set========================
	pctl_spi_to_lcd_cmd(0xC0);	//设置AVDD、MODE、VRHP、VRHN
	pctl_spi_to_lcd_write_data(0xA2);
	pctl_spi_to_lcd_write_data(0x02);
	pctl_spi_to_lcd_write_data(0x84);
		
	pctl_spi_to_lcd_cmd(0xC1);	//设置VGH与VGL的供电功率
	pctl_spi_to_lcd_write_data(0xC5);

	pctl_spi_to_lcd_cmd(0xC2);	//设置正常模式/全色模式下的运放的电流
	pctl_spi_to_lcd_write_data(0x0A);  //0x0A 、0x0D
	pctl_spi_to_lcd_write_data(0x00);
	
	pctl_spi_to_lcd_cmd(0xC3);	//设置空闲模式/八色模式下的运放的电流
	pctl_spi_to_lcd_write_data(0x8A);  //0x8A 、0x8D
	pctl_spi_to_lcd_write_data(0x2A);
	
	pctl_spi_to_lcd_cmd(0xC4);	//设置部分模式/全色模式下的运放的电流
	pctl_spi_to_lcd_write_data(0x8A);  //0x8A 、0x8D
	pctl_spi_to_lcd_write_data(0xEE);

	//===============vcom set=========================
	pctl_spi_to_lcd_cmd(0xC5);	//设置VCOM电压电平以减少闪烁问题
	pctl_spi_to_lcd_write_data(0x0E);  //0x0E 、0x03
	
//	pctl_spi_to_lcd_cmd(0x36); //MX, MY, RGB mode 
//  pctl_spi_to_lcd_write_data(0x0C); 
	//===============color format set=================
	pctl_lcd_set_color_format(0x05);  //rgb 16位真彩色
	
	//===============scanning direction set===========
	pctl_lcd_set_scan_dir(0x08);			//√√√√√√ 58
	
	//===============gamma sequence set===============
	pctl_spi_to_lcd_cmd(0xE0);	//Gamma ‘+’ Polarity Correction Characteristics Setting
	pctl_spi_to_lcd_write_data(0x12);
	pctl_spi_to_lcd_write_data(0x1C);
	pctl_spi_to_lcd_write_data(0x10);
	pctl_spi_to_lcd_write_data(0x18);
	pctl_spi_to_lcd_write_data(0x33);
	pctl_spi_to_lcd_write_data(0x2C);
	pctl_spi_to_lcd_write_data(0x25);
	pctl_spi_to_lcd_write_data(0x28);
	pctl_spi_to_lcd_write_data(0x28);
	pctl_spi_to_lcd_write_data(0x27);
	pctl_spi_to_lcd_write_data(0x2F);
	pctl_spi_to_lcd_write_data(0x3C);
	pctl_spi_to_lcd_write_data(0x00);
	pctl_spi_to_lcd_write_data(0x03);
	pctl_spi_to_lcd_write_data(0x03);
	pctl_spi_to_lcd_write_data(0x10);

	pctl_spi_to_lcd_cmd(0xE1);	//Gamma ‘+’ Polarity Correction Characteristics Setting
	pctl_spi_to_lcd_write_data(0x12);
	pctl_spi_to_lcd_write_data(0x1C);
	pctl_spi_to_lcd_write_data(0x10);
	pctl_spi_to_lcd_write_data(0x18);
	pctl_spi_to_lcd_write_data(0x2D);
	pctl_spi_to_lcd_write_data(0x28);
	pctl_spi_to_lcd_write_data(0x23);
	pctl_spi_to_lcd_write_data(0x28);
	pctl_spi_to_lcd_write_data(0x28);
	pctl_spi_to_lcd_write_data(0x26);
	pctl_spi_to_lcd_write_data(0x2F);
	pctl_spi_to_lcd_write_data(0x3B);
	pctl_spi_to_lcd_write_data(0x00);
	pctl_spi_to_lcd_write_data(0x03);
	pctl_spi_to_lcd_write_data(0x03);
	pctl_spi_to_lcd_write_data(0x10);

	//===============partial area set=================
	pctl_spi_to_lcd_cmd(0x30);   //部分模式的显示区域设置          
	pctl_spi_to_lcd_write_data(0x00);             
	pctl_spi_to_lcd_write_data(0x00);             
	pctl_spi_to_lcd_write_data(0x00);             
	pctl_spi_to_lcd_write_data(0x80);
	
	////
	pctl_spi_to_lcd_write_data(0x3A); //65k mode 
  pctl_spi_to_lcd_write_data(0x05);
	
	//===============partial mode on==================
	pctl_spi_to_lcd_cmd(0x12);	//打开Partial模式

	//===============display on=======================
	pctl_spi_to_lcd_cmd(0x29);	//开启显示，帧内存的输出被启用
	for(int k = 0; k < 9000000; k++);			//延时
	
}
