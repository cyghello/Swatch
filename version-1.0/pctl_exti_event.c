#include "pctl_exti_event.h"

static event_state t_event_state;
static unsigned char local_pin_state = FLAG_DISABLE;
void pctl_exti_gpio_init()
{
	drv_init_gpio_in(GPIOA, GPIO_Pin_0);
	drv_init_af_gpio(GPIOA, GPIO_PinSource0, GPIO_AF_EVENTOUT);
	
}

void pctl_exti_key_on (unsigned char* flag)
{
	if (*flag == FLAG_ENABLE)
	{
		local_pin_state = FLAG_ENABLE;
	}
}

unsigned char pctl_event_pin_state_rd(event_state* t_event_state)
{
	t_event_state->drv_flag = local_pin_state;
}