#include "drv_dma.h"
#include "drv_usart.h"
#include <string.h>
#include <stdio.h>

//#include "ring_buf.h"
static uint8_t rData1[50] = { 0x98, 0x97,0x96, 0x95, 0x94, 0x12, 0x13, 0x14,};

void drv_dma2_init_tx(void)
{
	DMA_InitTypeDef DMA_Periph;
	NVIC_InitTypeDef IRQ_DMA;
	//USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_Periph.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	DMA_Periph.DMA_Memory0BaseAddr = (uint32_t)rData1;		//
	DMA_Periph.DMA_BufferSize = 10;
	DMA_Periph.DMA_Priority = DMA_Priority_VeryHigh; //level
	DMA_Periph.DMA_Channel = DMA_Channel_4;
	DMA_Periph.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_Periph.DMA_Mode = DMA_Mode_Normal; //DMA_Mode_Normal //DMA_Mode_Circular
	DMA_Periph.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //Memory
	DMA_Periph.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word; //Peripheral
	DMA_Periph.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Periph.DMA_MemoryInc = DMA_MemoryInc_Enable;  //DMA_memory_incremented_mode
	
	DMA_Periph.DMA_FIFOMode = DMA_FIFOMode_Disable;  //INC_periph
	DMA_Periph.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_Periph.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_Periph.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA2_Stream7, &DMA_Periph);
	
	IRQ_DMA.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	IRQ_DMA.NVIC_IRQChannelCmd = ENABLE;
	IRQ_DMA.NVIC_IRQChannelPreemptionPriority = 0x00;
	IRQ_DMA.NVIC_IRQChannelSubPriority = 0x01;
	
	NVIC_Init(&IRQ_DMA);

	DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);
	//DMA_Cmd(DMA2_Stream7, ENABLE);
	//DMA_Cmd(DMA2_Stream5, ENABLE);
}
void drv_dma2_init_rx(void)
{
	DMA_InitTypeDef DMA_Periph;
	NVIC_InitTypeDef IRQ_DMA;
	//USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	
	DMA_Periph.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	DMA_Periph.DMA_Memory0BaseAddr = (uint32_t)rData1;		//
	DMA_Periph.DMA_BufferSize = 16;
	DMA_Periph.DMA_Priority = DMA_Priority_VeryHigh; //level
	DMA_Periph.DMA_Channel = DMA_Channel_4;
	DMA_Periph.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_Periph.DMA_Mode = DMA_Mode_Circular; //DMA_Mode_Normal //DMA_Mode_Circular
	DMA_Periph.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //Memory
	DMA_Periph.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //Peripheral
	DMA_Periph.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Periph.DMA_MemoryInc = DMA_MemoryInc_Enable;  //DMA_memory_incremented_mode
	
	DMA_Periph.DMA_FIFOMode = DMA_FIFOMode_Disable;  //INC_periph
	DMA_Periph.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_Periph.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_Periph.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA2_Stream5, &DMA_Periph);
	
	IRQ_DMA.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	IRQ_DMA.NVIC_IRQChannelCmd = ENABLE;
	IRQ_DMA.NVIC_IRQChannelPreemptionPriority = 0x00;
	IRQ_DMA.NVIC_IRQChannelSubPriority = 0x00;
	
	NVIC_Init(&IRQ_DMA);

	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);
	DMA_Cmd(DMA2_Stream5, ENABLE);
}

void DMA2_Stream7_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF7) != RESET)
	{
		DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF7);
	}
}

void DMA2_Stream5_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA2_Stream7, DMA_FLAG_TCIF5) != RESET)
	{
		DMA_ClearFlag(DMA2_Stream5, DMA_FLAG_TCIF5);
		
	}
}
void copy (uint8_t* pccc)
{
	memcpy(pccc, &rData1, sizeof(rData1));
	//print_usart2((uint8_t*) sizeof(&rData1[0]));
	for (int i = 0; i < 10000000; i++);
}
//void tx_buf_data_init(tx_buf_data *tx_data) //void *pc_buf_msg_tx
//	{
//	//ptx_data = &tx_data;
//	tx_data->head0 = 0x99;
//	tx_data->head1 = 0xAA;
//	tx_data->flag = 0x23;
//	tx_data->device = 0x06;
//	tx_data->work_state = 0x07;
//	tx_data->reserve[0] = 0xBB;
//	tx_data->reserve[1] = 0xCC;
//	}

//	void drv_uart_upload_by_dma(tx_buf_data *tx_data, unsigned char clen)//void *pc_buf_msg_tx
//	{
//	memcpy (&(rData[0]), tx_data, clen);
//	}
