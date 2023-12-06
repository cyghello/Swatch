#include "pctl_work_para.h"

/**
 * @brief   : 初始化工作标志
 * @param[At]
 * @param[in] pt_task_flag
 * @param[out]
 * @note
 */
void proc_ctl_init_work_flag_by_default (PT_TASK_STATUS_FLAG pt_task_flag)
{
	///< begin : work status flag
	pt_task_flag->cflag_work_pre_start = FLAG_DISABLE;
	pt_task_flag->cflag_work_start = FLAG_DISABLE;
	pt_task_flag->cflag_work_end = FLAG_DISABLE;
	pt_task_flag->cflag_work_excit_gpio = FLAG_DISABLE;
	pt_task_flag->cflag_work_acq = FLAG_DISABLE;
	pt_task_flag->cflag_work_acq_proc = FLAG_DISABLE;

	pt_task_flag->cflag_dev_config = FLAG_DISABLE;
	pt_task_flag->cflag_work_rx_proc = FLAG_DISABLE;
	pt_task_flag->cflag_work_updata = FLAG_DISABLE;

	pt_task_flag->cflag_led_dev_run = FLAG_DISABLE;
	pt_task_flag->cflag_led_dev_open = FLAG_DISABLE;
	pt_task_flag->cflag_led_dev_close = FLAG_DISABLE;
	// ///< end
}