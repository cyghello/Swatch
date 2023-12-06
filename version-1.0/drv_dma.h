#ifndef __DRV_DMA_H
#define __DRV_DMA_H

#include "stm32f4xx.h"

//void drv_uart_upload_by_dma(void *pc_buf_msg_tx, unsigned char clen);
void drv_dma2_init_tx(void);
void drv_dma2_init_rx(void);
void DMA2_Stream7_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);
void copy (uint8_t* pccc);


//void tx_buf_data_init(tx_buf_data *tx_data); //void *pc_buf_msg_tx
//void drv_uart_upload_by_dma(tx_buf_data *tx_data, unsigned char clen);//void *pc_buf_msg_tx
//static tx_buf_data rx_data;

#endif