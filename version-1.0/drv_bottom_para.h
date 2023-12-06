#ifndef __DRV_BOTTOM_PARA_H
#define __DRV_BOTTOM_PARA_H

/**/
#include "stm32f4xx.h"

typedef enum 
{
	FLAG_DISABLE = 0,
	FLAG_ENABLE
	
}type_flag_state;
	
struct event_state
{
	 unsigned char drv_flag;
};

typedef struct event_state event_state, *p_event_state;

#endif