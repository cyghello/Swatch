#ifndef __PCTL_PWM_INTERFACE_H
#define __PCTL_PWM_INTERFACE_H

#include "stm32f4xx.h"
#include "drv_timer.h"
#include "drv_gpio.h"

void pctl_pwm_gpio_init (GPIO_TypeDef* gpio_port,uint16_t gpio_pin, uint16_t GPIO_PinSource, uint8_t GPIO_AF);
void pctl_pwm_tim_init ();

#endif