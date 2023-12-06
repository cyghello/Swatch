#ifndef __DRV_USART_H
#define __DRV_USART_H

#include "stm32f4xx.h"

typedef void (*phandle_usart_call)(unsigned char* cmessage);
void drv_usart_rx_call_entry (phandle_usart_call phandle);
void drv_init_usart_gpio();
void drv_init_usart2_gpio();
void drv_init_usart();
void drv_init_usart2();
void print(uint16_t* temp);
void print_usart2(uint16_t *temp);

static uint8_t ucount = 0;
static uint8_t Rx_flag = 0;

static char rx_data[100];

struct buffer_usart{
	char rx_data[200];
};
typedef struct buffer_usart buffer_usart;

uint8_t esp8266_send_cmd(char* cmd, char* ack, uint16_t waittime);
uint8_t* esp8266_check_cmd(char* str);
#endif