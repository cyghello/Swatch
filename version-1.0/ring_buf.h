#ifndef __RING_BUF_H
#define __RING_BUF_H

#include "stm32f4xx.h"
#include <string.h>
#include <stdio.h>

#define D_SIZE_RX_RING_BUFFER             400
static uint32_t rData[100] = { 0x98, 0x97,0x96, 0x95, 0x94, 0, 0x12, 0x13, 0x14, 0x93 };	//32位

struct ring_buf_data{
	unsigned char cring_buf[D_SIZE_RX_RING_BUFFER];
	unsigned short loc_head;
	unsigned short loc_tail;
	unsigned short size_data;
	//unsigned char flag;	//	调试标志

};

typedef struct ring_buf_data ring_buf_data, *pring_buf_data;

struct tx_buf_data
{
	unsigned char chead0;  //0
	unsigned char chead1;  //1
	unsigned char cflag_msg;  //2
	unsigned char cdev_id0;
	unsigned char cdev_id1;
	unsigned char cdev_id2;
	unsigned char csta_work;  //
	unsigned short sdata_temper;  //7,8
	unsigned short swarn_high;   //9,10
	unsigned short swarn_low;  //11, 12
	unsigned char csta_warn;  //13
	unsigned char rvl[6];  //
} __attribute__ ((packed));
typedef struct tx_buf_data tx_buf_data, *ptx_buf_data; 

struct rx_buf_data{
	uint8_t head0;
	uint8_t head1;
	uint8_t flag;
	uint8_t device;
	uint8_t work_state;
	uint8_t reserve[15];
	//uint32_t tail;
}__attribute__ ((packed));

typedef struct rx_buf_data rx_buf_data, *prx_buf_data; 

void pctl_ctl_rx_rgbuf_param_init (void);
void pctl_ctl_rx_rgbuf_wt_byte (unsigned char *pcdata);
unsigned char pctl_ctl_rx_rgbuf_rd_byte (unsigned char *pcrtn_data);
unsigned short pctl_ctl_rx_rgbuf_rd_data (unsigned char *pcdata, unsigned short ssize);
unsigned short pctl_ctl_rx_rgbuf_get_size_byte (void);
void pctl_ctl_rx_rgbuf_reset_buf (void);
void on_rx_uart_data_wt_buf (unsigned char *pcdata);
#endif