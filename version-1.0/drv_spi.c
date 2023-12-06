#include "drv_spi.h"

void drv_spi1_init ()
{
	SPI_InitTypeDef  SPI_InitStructure;
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx; //双向 全双工 1线发送
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // 主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;  //空闲状态为低
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //串行同步时钟的第一个跳变沿 数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //cs由soft 内部ssi位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; // 波特率预分频值
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //指定数据传输从MSB开始还是LSB开始
	SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC值计算的多项式

	SPI_Init(SPI1,&SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
	
}