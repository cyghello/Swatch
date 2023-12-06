/**
* "drv_gpio.h" version 00.00
*/

#include "drv_gpio.h"

//GPIO_InitTypeDef GPIO_OUT;

void drv_init_gpio_in(GPIO_TypeDef* gpio_port,uint16_t gpio_pin)
{
	GPIO_InitTypeDef gpio_init_bit;
	
	gpio_init_bit.GPIO_Pin = gpio_pin;
	gpio_init_bit.GPIO_Mode = GPIO_Mode_IN;
	//gpio_init_bit.GPIO_OType = GPIO_OType_PP;
  gpio_init_bit.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_bit.GPIO_PuPd = GPIO_PuPd_NOPULL;		//
  GPIO_Init(gpio_port, &gpio_init_bit);
	
	//GPIO_SetBits(GPIOA, GPIO_Pin_4);
	//GPIO_ResetBits(GPIOA, GPIO_Pin_4);
}

void drv_init_gpio_out(GPIO_TypeDef* gpio_port,uint16_t gpio_pin)
{
	//GPIOx  GPIO_Pin_0
	GPIO_InitTypeDef gpio_init_bit;
	
	gpio_init_bit.GPIO_Pin = gpio_pin;
	gpio_init_bit.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_bit.GPIO_OType = GPIO_OType_PP;
  gpio_init_bit.GPIO_Speed = GPIO_Speed_50MHz;
  //gpio_init_bit.GPIO_PuPd = GPIO_PuPd_UP;		//
  GPIO_Init(gpio_port, &gpio_init_bit);
}
void drv_init_gpio_af(GPIO_TypeDef* gpio_port,uint16_t gpio_pin)
{
	GPIO_InitTypeDef gpio_init_bit;
	
	gpio_init_bit.GPIO_Pin = gpio_pin;
	gpio_init_bit.GPIO_Mode = GPIO_Mode_AF;
	gpio_init_bit.GPIO_OType = GPIO_OType_PP;
  gpio_init_bit.GPIO_Speed = GPIO_Speed_50MHz;
  //gpio_init_bit.GPIO_PuPd = GPIO_PuPd_DOWN;		//GPIO_Mode_AF
  GPIO_Init(gpio_port, &gpio_init_bit);
}
/*
*	@:ADC_IO
*/
void drv_init_gpio_an(GPIO_TypeDef* gpio_port,uint16_t gpio_pin)
{
  GPIO_InitTypeDef gpio_init_bit;
  /* ADC Channel 10 -> PC0
     ADC Channel 11 -> PC1
     ADC Channel 12 -> PC2
  */
  gpio_init_bit.GPIO_Pin = gpio_pin;
  gpio_init_bit.GPIO_Mode = GPIO_Mode_AN;
	gpio_init_bit.GPIO_Speed = GPIO_Speed_50MHz;
  gpio_init_bit.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(gpio_port, &gpio_init_bit);
}

void drv_init_af_gpio(GPIO_TypeDef* gpio_port,uint16_t GPIO_PinSource, uint8_t GPIO_AF)
{
	//GPIO_PinSourcex
	GPIO_PinAFConfig(gpio_port, GPIO_PinSource, GPIO_AF);
}

void drv_gpio_set (GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
{
	GPIO_SetBits(gpio_port, gpio_pin);
}

void drv_gpio_reset (GPIO_TypeDef* gpio_port, uint16_t gpio_pin)
{
	GPIO_ResetBits(gpio_port, gpio_pin);
}

/*
*  端口映射
*/
void drv_gpio_af_pwm_timer()
{
	
}