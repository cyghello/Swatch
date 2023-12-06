///*
// * @Date         : 2023-04-09 21:31:15
// * @LastEditTime : 2023-04-18 02:21:30
// * @Description  : 
// * @FilePath     : \USER\pctl_trans.c
// * @Author       : ak999
// * ---------------------- ------------------------
// */
//#include "pctl_trans.h"

///**
// * @brief   : 从环形缓冲区中获取长度
// * @param[out] ps_len_byte
// * @note
// */
//static void opt_rx_buf_get_surpluse (unsigned short *ps_len_byte)
//{
//	*ps_len_byte = pctl_ctl_rx_rgbuf_get_size_byte ();  //获取环形缓冲区剩余长度
//}

///**
// * @brief 若剩余长度满足装载完整报文，则判断是否有完整报文。若有则从缓冲区中取出合适的报文。
// * @param[out] pt_pkg_rx
// * @param[in][out] ps_len_byte_surpluse
// * @return cflag 是否有完整报文
// * @note
// */
//unsigned char pctl_opt_pkg_rx_get_msg (rx_buf_data* pt_pkg_rx, unsigned short *ps_len_byte_surpluse)
//{
//	unsigned char crtn_flag;

//	//printf ("@DEBUG pctl_opt_pkg_rx_get_msg() > D_LEN_MSG_DATA_MAX \r\n");
//	if (opt_rx_judge_scan_one_msg (ps_len_byte_surpluse))  //是否有完整报文存在
//	{
//		
//		opt_rx_get_one_package ((unsigned char*) (pt_pkg_rx));  //取出报文
//		opt_rx_buf_get_surpluse (ps_len_byte_surpluse);  //获取缓冲区报文长度
//		crtn_flag = FLAG_ENABLE;
//	}
//	else
//	{
//		crtn_flag = FLAG_DISABLE;
//	}
//	return crtn_flag;
//}
///**
// * @brief   : 判断环形缓冲区是否存在完整的报文
// * (1) 若获得报文头，
// * (2) 若仅获得报文起始，但是剩余内容不够报文头长度，应当等待下次；
// * (3) 若全部内容没有报文头，应当给出标志，等待下次处理
// * @param[in] ps_size: 处理长度
// * @param[out] ps_size : 剩余长度
// * @return 是否有效
// * @note
// */
//static unsigned char opt_rx_judge_scan_one_msg (unsigned short *ps_size)
//{
//	static unsigned char clength;
//	if (opt_rx_buf_loc_msg_head_begin (*ps_size, D_MSG_RX_HEAD_0, D_MSG_RX_HEAD_1))  //如果有报文头
//	{
//		///< begin: 判断是否存在完整报文，如果有
//		clength = pctl_ctl_rx_rgbuf_get_size_byte ();  //获取环形缓冲区剩余长度
//		if (clength < D_LEN_MSG_DATA_MAX - 2)  //报文头的0x55AA已经被读出
//			return FLAG_DISABLE;  //没有完整报文存在
//		else
//			return FLAG_ENABLE;
//		///< end
//	}
//	else
//	{
//		clength = pctl_ctl_rx_rgbuf_get_size_byte ();  //获取环形缓冲区剩余长度
//		return FLAG_DISABLE;  //没有报文头
//	}
//}
///**
// * @brief   : 从环形缓冲区中定位报文头起始位置。确认是head后，退出
// (1) 首先必须获取接收长度
// (2) 0x55AA
// * @param[in] csize_data, 处理数据长度
// * @param[out]
// * @return 是否有报文头存在
// * @note
// */
//static unsigned char opt_rx_buf_loc_msg_head_begin (unsigned short ssize_data, unsigned char chead0,
//													unsigned char chead1)
//{
//	unsigned char ctmp;
//	unsigned char cbuf_tmp[20];
//	for (ctmp = 0; ctmp < ssize_data - 1; ctmp++)
//	{
//		//opt_rgbuf_rd_byte(&(gst_rx_data.cbuf_rx[0])); //读取2个字节
//		pctl_ctl_rx_rgbuf_rd_data (&(cbuf_tmp[0]), 2);

//		if ((cbuf_tmp[0] == chead0) && (cbuf_tmp[1] == chead1))
//		{
//			return FLAG_ENABLE;
//		}
//		else
//		{
//			return FLAG_DISABLE;
//		}
//	}
//	return FLAG_DISABLE;
//}
///**
// * @brief   : 环形缓冲取出完整报文（除去头两个字节）
// * 由于最前两个字节已经被读出，故本次读出报文长度应当为全长-2。
// * @param[out] pcbuf_data : 取出的数据
// * @return 环形s缓冲区剩余长度
// * @note
// */
////static unsigned short opt_rx_get_one_package (unsigned char *pcbuf_data)
//static void opt_rx_get_one_package (unsigned char *pcbuf_data)
//{
//	//printf ("@DEBUG opt_rx_get_one_package()  \n");
//	pctl_ctl_rx_rgbuf_rd_data (pcbuf_data + 2, D_LEN_MSG_DATA_MAX - 2);

//	//return pctl_ctl_rx_rgbuf_get_size_byte ();
//}


//void ui_proc_task_rx_buf_by_uart (T_TASK_STATUS_FLAG* pt_task_flag, rx_buf_data* pt_pkg_rx)
//{
//	unsigned short slen_byte_surpluse = 100;
//	unsigned char cflag;

//	opt_rx_buf_get_surpluse (&slen_byte_surpluse);
//	print_usart2(&slen_byte_surpluse);
//	for (int i = 0; i < 1000000;i++);
//	if ((slen_byte_surpluse) >= D_LEN_MSG_DATA_MAX)
//	{
//		//printf ("@DEBUG ui_proc_task_rx_buf_by_uart(0): slen_byte_surpluse = %d \n", slen_byte_surpluse);
//		cflag = pctl_opt_pkg_rx_get_msg (pt_pkg_rx, &slen_byte_surpluse);
//		//printf ("@DEBUG ui_proc_task_rx_buf_by_uart(1): slen_byte_surpluse = %d \n", slen_byte_surpluse);
//		opt_rx_buf_get_surpluse (&slen_byte_surpluse);
//		if (cflag == FLAG_ENABLE)
//		{
//			//pctl_opt_rx_uncode_entrance (pt_pkg_rx, pt_pkg_tx, pt_task_flag);  //解码
//			for (int k = 0; k < 20; k++)
//			{
//				if (k == 1)
//				{
//					print_usart2((uint16_t*)&pt_pkg_rx->head0);
//					for (int l = 0; l < 10000000;l++);
//				}
//								if (k == 2)
//				{
//					print_usart2((uint16_t*)&pt_pkg_rx->head1);
//					for (int t = 0; t < 10000000;t++);
//				}
//								if (k == 3)
//				{
//					print_usart2((uint16_t*)&pt_pkg_rx->flag);
//					for (int y = 0; y < 10000000;y++);
//				}
//								if (k == 4)
//				{
//					print_usart2((uint16_t*)&pt_pkg_rx->device);
//					for (int u = 0; u < 10000000;u++);
//				}
//								if (k == 5)
//				{
//					print_usart2((uint16_t*)&pt_pkg_rx->work_state);
//					for (int p = 0; p < 10000000;p++);
//				}

//			}
//				
//		}
//	}
//	print_usart2((uint16_t*)&cflag);
//	for (int j = 0; j < 1000000;j++);
//	pt_task_flag->cflag_work_rx_proc = FLAG_DISABLE;
//}
///**/
////void pctl_rx_buf_message_read()
////{
////	unsigned char head0;
////	unsigned char head1;
////	head0 = 0x99;
////	head1 = 0x14;
////	/*读取报文头，暂定：两个*/
////	unsigned char head_buf[20];
////	unsigned char head_flag;
////	for (unsigned char chead = 0; chead < 2; chead++)
////	{
////		pctl_ctl_rx_rgbuf_rd_data (&(head_buf[0]), 2);
////		if (head_buf[0] == head0 && head_buf[1] == head1)
////		{
////			head_flag = 1;
////		}
////		else
////		{
////			head_flag = 0;
////		}
////	}
////	
////}
