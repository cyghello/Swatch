#include "pctl_spi.h"

void pctl_spi_gpio_init ()
{
	drv_init_gpio_out(GPIOA, GPIO_Pin_4);
	drv_init_gpio_af(GPIOA, GPIO_Pin_5);
	drv_init_gpio_af(GPIOA, GPIO_Pin_6);
	drv_init_gpio_af(GPIOA, GPIO_Pin_7);  //
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}


void pctl_spi_cfg_init ()
{
	drv_spi1_init ();
}

uint8_t pctl_spi_write_byte (uint8_t data)
{
	uint8_t relay = 0;
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE == RESET))
	{
		relay++;
		if (relay > 200) return 0;
	}
	SPI_I2S_SendData (SPI1, data);
//	relay = 0;
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
//	{
//		relay++;
//		if(relay > 200) return 0;
//	}
//	return SPI_I2S_ReceiveData(SPI1);
}

void pctl_spi_write_start ()
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	//GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

void pctl_spi_write_stop ()
{
	//GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
}

//void pctl_spi_to_lcd_write_data ()
//{
//	
//	
//}
