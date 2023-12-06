#ifndef __PCTL_SPI_H
#define __PCTL_SPI_H

#include "stm32f4xx.h"
#include "drv_spi.h"
#include "drv_gpio.h"

void pctl_spi_gpio_init ();
void pctl_spi_cfg_init ();
uint8_t pctl_spi_write_byte (uint8_t data);
void pctl_spi_write_start ();
void pctl_spi_write_stop ();

#endif