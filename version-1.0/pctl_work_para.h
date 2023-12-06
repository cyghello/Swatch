#ifndef __PCTL_WORK_PARA_H
#define __PCTL_WORK_PARA_H

/**/
#include "drv_bottom_para.h"

struct tag_task_status
{
	//unsigned char cflag_dev_open;
	unsigned char cflag_work_pre_start;  //
	unsigned char cflag_work_start;     //
	unsigned char cflag_work_excit_gpio;  //
	unsigned char cflag_work_acq;  //
	unsigned char cflag_work_acq_proc;  //
	unsigned char cflag_work_updata;  //
	unsigned char cflag_work_end;     //

	unsigned char cflag_work_rx_proc;  //

	unsigned char cflag_dev_config;  //

	unsigned char cflag_led_dev_open;  //
	unsigned char cflag_led_dev_close;  //
	unsigned char cflag_led_dev_run;   //
};
typedef struct tag_task_status T_TASK_STATUS_FLAG, *PT_TASK_STATUS_FLAG;


void proc_ctl_init_work_flag_by_default (PT_TASK_STATUS_FLAG pt_task_flag);

#endif