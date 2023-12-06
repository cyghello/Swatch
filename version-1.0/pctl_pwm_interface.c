#include "pctl_pwm_interface.h"

void pctl_pwm_gpio_init(GPIO_TypeDef* gpio_port,uint16_t gpio_pin, uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
	drv_init_gpio_af(gpio_port, gpio_pin);
	drv_init_af_gpio(gpio_port, GPIO_PinSource, GPIO_AF);
	
}

void pctl_pwm_tim_init ()
{
	drv_timer_pwm_init();
	
}