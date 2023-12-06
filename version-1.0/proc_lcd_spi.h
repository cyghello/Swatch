#ifndef __PROC_LCD_SPI_H
#define __PROC_LCD_SPI_H

#include "pctl_lcd.h"
#include "pctl_spi.h"


void proc_lcd_battery_icon ();
uint32_t OLED_Pow(uint32_t X, uint32_t Y);
void proc_lcd_print_asc (unsigned char start_x,unsigned char start_y,unsigned char font_wide,
														unsigned char font_high, uint32_t number, uint8_t length);
void proc_lcd_print_number (unsigned char start_x,unsigned char start_y,unsigned char font_wide,
														unsigned char font_high, uint32_t number, uint8_t length);
#endif