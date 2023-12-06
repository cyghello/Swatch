#ifndef __PCTL_TRANS_H
#define __PCTL_TRANS_H

#include "ring_buf.h"
#include "drv_flag.h"
#include "drv_bottom_para.h"
#include "pctl_work_para.h"
#include "drv_usart.h"
/**/

#define D_LEN_MSG_DATA_MAX  20

static void opt_rx_buf_get_surpluse (unsigned short *ps_len_byte);
unsigned char pctl_opt_pkg_rx_get_msg (rx_buf_data* pt_pkg_rx, unsigned short *ps_len_byte_surpluse);
static unsigned char opt_rx_judge_scan_one_msg (unsigned short *ps_size);
static unsigned char opt_rx_buf_loc_msg_head_begin (unsigned short ssize_data, unsigned char chead0,
													unsigned char chead1);
static void opt_rx_get_one_package (unsigned char *pcbuf_data);
void ui_proc_task_rx_buf_by_uart (T_TASK_STATUS_FLAG* pt_task_flag, rx_buf_data* pt_pkg_rx);
#endif