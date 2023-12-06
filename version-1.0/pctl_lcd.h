#ifndef __PCTL_LCD_H
#define __PCTL_LCD_H

#include "stm32f4xx.h"
//#include "drv_spi.h"
#include "drv_gpio.h"


void pctl_lcd_gpio_init ();
void pctl_lcd_reset ();
void pctl_spi_to_lcd_write_data (uint8_t data);
void pctl_spi_to_lcd_cmd (uint8_t data);
void pctl_lcd_set_frame_size (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end);
void pctl_lcd_set_background (uint16_t color);
void pctl_lcd_set_scan_dir (uint8_t data);
void pctl_lcd_set_color_format (uint8_t data);
void pctl_lcd_set_point (uint16_t x, uint16_t y, uint16_t color);
void pctl_lcd_write_char (unsigned char start_x,unsigned char start_y,
												unsigned char font_wide, unsigned char font_high, const unsigned char *ch);
void pctl_lcd_display_pic (uint16_t *ch);
void pctl_lcd_set_rectangle (uint16_t x_start, uint16_t x_end, uint16_t y_start, uint16_t y_end, uint16_t color);
void pctl_lcd_dispgrayhor16 ();
void pctl_dispframe ();
void pctl_dispband ();
void pctl_disppic (uint16_t x, uint16_t y,uint16_t w, uint16_t h, const unsigned char *p);
void pctl_lcd_cfg ();

#define PINK 0xD2F5
#define BLUE 0X03bD
#define RED 0xF882
#define YELLOW 0xFFE0
#define WHITE 0xffff
#define BLACK 0x0000

//#define LCD_NOP			0x00	//空命令
//#define LCD_SWRESET		0x01	//软件复位，在睡眠和显示模式下，重置软件后需等待120ms后方可执行下一条指令
//#define LCD_RDDID		0x04	//读取LCD的制造商ID（8位）、驱动版本ID（最高位为1，7位）、驱动程序ID（8位）
//#define LCD_RDDST		0x09	//读取显示屏所有状态参数
//#define LCD_RDDPM		0x0A	//读取显示屏能量模式
//#define LCD_RDDMADCTL	0x0B	//读取显示屏MADCTL
//#define LCD_RDDCOLMOD	0x0C	//读取显示屏像素定义
//#define LCD_RDDIM		0x0D	//读取显示屏图片模式
//#define LCD_RDDSM		0x0E	//读取显示屏单信号模式
//#define LCD_RDDSDR		0x0F	//读取显示屏自我诊断结果
//#define LCD_SLPIN		0x10	//进入最小功耗模式
//#define LCD_SLPOUT 		0x11	//关闭睡眠模式
//#define LCD_PTLON		0x12	//打开Partial模式
//#define LCD_NORON		0x13	//恢复到正常模式
//#define LCD_INVOFF		0x20	//显示反转模式中恢复
//#define LCD_INVON		0x21	//进入反向显示模式
//#define LCD_GAMSET		0x26	//当前显示选择所需的伽马曲线
//#define LCD_DISPOFF		0x28	//关闭显示，帧内存的输出被禁用
//#define LCD_DISPON		0x29	//开启显示，帧内存的输出被启用
//#define LCD_CASET		0x2A	//列地址设置，每个值代表帧内存中的一列
//#define LCD_RASET		0x2B	//行地址设置，每个值代表帧内存中的一列
//#define LCD_RAMWR		0x2C	//写入内存
//#define LCD_RGBSET		0x2D	//颜色模式设置
//#define LCD_RAMRD		0x2E	//读取内存
//#define LCD_PTLAR		0x30	//部分模式的显示区域设置
//#define LCD_SCRLAR		0x33	//定义垂直滚动区域的显示
//#define LCD_TEOFF		0x34	//关闭(Active Low) TE信号线的撕裂效应输出信号
//#define LCD_TEON		0x35	//打开TE信号线的撕裂效果输出信号
//#define LCD_MADCTL		0x36	//定义帧内存的读写扫描方向
//#define LCD_VSCSAD		0x37	//设置垂直滚动起始地址，此命令与垂直滚动定义(33h)一起使用
//#define LCD_IDMOFF		0x38	//关闭空闲模式
//#define LCD_IDMON		0x39	//开启空闲模式
//#define LCD_COLMOD		0x3A	//定义通过MCU接口传输的RGB图片数据的格式
//#define LCD_FRMCTR1		0xB1	//设置全色正常模式的帧频
//#define LCD_FRMCTR2 	0xB2	//设置空闲模式的帧频
//#define LCD_FRMCTR3 	0xB3	//设置部分模式/全色的帧频率
//#define LCD_INVCRT 		0xB4	//反转模式控制
//#define LCD_PWCTR1 		0xC0	//设置AVDD、MODE、VRHP、VRHN
//#define LCD_PWCTR2 		0xC1	//设置VGH与VGL的供电功率
//#define LCD_PWCTR3 		0xC2	//设置正常模式/全色模式下的运放的电流
//#define LCD_PWCTR4 		0xC3	//设置空闲模式/八色模式下的运放的电流
//#define LCD_PWCTR5 		0xC4	//设置部分模式/全色模式下的运放的电流
//#define LCD_VMCTR1 		0xC5	//设置VCOM电压电平以减少闪烁问题
//#define LCD_VMOFCTR		0xC7	//VCOM偏移控制，在使用命令0xC7之前，命令0xD9的位VMF_EN必须启用(设置为1)
//#define LCD_WRID2		0xD1	//写入LCD模块版本的7位数据，保存到NVM
//#define LCD_WRID3		0xD2	//写入项目代码模块的8位数据，保存到NVM
//#define LCD_NVFCTR1		0xD9	//NVM状态控制
//#define LCD_RDID1		0xDA	//读字节返回8位LCD模块的制造商ID
//#define LCD_RDID2		0xDB	//读字节返回8位LCD模块/驱动程序版本ID
//#define LCD_RDID3		0xDC	//读字节返回8位LCD模块/驱动ID
//#define LCD_NVFCTR2		0xDE	//NVM读取命令
//#define LCD_NVFCTR3		0xDF	//NVM写取命令
//#define LCD_GMCTRP1		0xE0	//Gamma ‘+’ Polarity Correction Characteristics Setting
//#define LCD_GMCTRN1		0xE1	//Gamma ‘+’ Polarity Correction Characteristics Setting
//#define LCD_GCV			0xFC	//自动调节门泵时钟，节省功耗

#endif