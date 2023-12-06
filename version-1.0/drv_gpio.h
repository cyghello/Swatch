#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

/**/
#include "stm32f4xx.h"

void drv_init_gpio_in(GPIO_TypeDef* gpio_port,uint16_t gpio_pin);
void drv_init_gpio_out(GPIO_TypeDef* gpio_port,uint16_t gpio_pin);
void drv_init_gpio_af(GPIO_TypeDef* gpio_port,uint16_t gpio_pin);
void drv_init_gpio_an(GPIO_TypeDef* gpio_port,uint16_t gpio_pin);
void drv_gpio_set (GPIO_TypeDef* gpio_port, uint16_t gpio_pin);
void drv_gpio_reset (GPIO_TypeDef* gpio_port, uint16_t gpio_pin);
void drv_init_af_gpio(GPIO_TypeDef* gpio_port,uint16_t GPIO_PinSource, uint8_t GPIO_AF);

#endif