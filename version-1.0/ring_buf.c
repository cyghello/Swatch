#include "ring_buf.h"
#include "drv_usart.h"

static ring_buf_data buf_data;
void pctl_ctl_rx_rgbuf_param_init (void)
{
	memset (&buf_data, 0, sizeof(buf_data));
	//buf_data.sset_rx_buf = D_SIZE_RX_RING_BUFFER;
	buf_data.loc_head = 0;
	buf_data.loc_tail = 0;
	buf_data.size_data = 0;

	//buf_data.cflag_msg_start = FLAG_DISABLE;
	//buf_data.cflag_msg_head  = FLAG_DISABLE;
}
/**
*
*/
void pctl_ctl_rx_rgbuf_wt_byte (unsigned char *pcdata)
{
	//printf ("@DEBUG pctl_ctl_rx_rgbuf_wt_byte(): = %d \r\n", gi_cnt_tmp);
	buf_data.cring_buf[buf_data.loc_tail] = *pcdata;     //从尾部追加（当前）
	buf_data.loc_tail++;
	if (buf_data.loc_tail >= D_SIZE_RX_RING_BUFFER)
	{
		buf_data.loc_tail = 0;  //大于数组最大长度,归零,形成环形队列
	}
}
/**
*
*/
unsigned char pctl_ctl_rx_rgbuf_rd_byte (unsigned char *pcrtn_data)
{
	if ((buf_data.loc_head == buf_data.loc_tail) &&   //如果头尾接触表示缓冲区为空
					(buf_data.loc_head == 0))
	{
		//printf ("@DEBUG pctl_ctl_rx_rgbuf_rd_byte() : FLAG_DISABLE \n");
		return 0;
	}
	else
	{
		//printf ("@DEBUG pctl_ctl_rx_rgbuf_rd_byte() : FLAG_ENABLE \n");
		*pcrtn_data = buf_data.cring_buf[buf_data.loc_head];    //如果缓冲区非空则取头节点值并偏移头节点
		buf_data.loc_head++;
		if (buf_data.loc_head >= D_SIZE_RX_RING_BUFFER)
		{
			buf_data.loc_head = 0;
		}
	}
	return 1;
}

/**
 * @brief   : 读取队列中设定长度的数据串
 * (1) 使用前务必获取缓冲数据长度，从而确保不会超限制
 * (2) 需要判断是否超过尾部
 * @param[in] csize
 * @param[out] pcdata
 * @return
 * @note 新的读位置为下次读位置的起始点，即每次均从当前开始读取
 */
unsigned short pctl_ctl_rx_rgbuf_rd_data (unsigned char *pcdata, unsigned short ssize)
{
	static unsigned short stmp;
	if (buf_data.loc_head <= buf_data.loc_tail)  //写入未回头：头在尾前 1、加了 '='
	{
		memcpy (pcdata, &(buf_data.cring_buf[buf_data.loc_head]), ssize);  
		buf_data.loc_head = buf_data.loc_head + ssize;

	}
	else
	{
		stmp = (D_SIZE_RX_RING_BUFFER - 1) - buf_data.loc_head + 1;   //头距缓冲边界的距离
		if (stmp <= ssize)
		{

			memcpy (pcdata, &(buf_data.cring_buf[buf_data.loc_head]), ssize);
			buf_data.loc_head = buf_data.loc_head + ssize;
		}
		else  //需要回头读取
		{

			memcpy (pcdata, &(buf_data.cring_buf[buf_data.loc_head]), stmp);

			ssize = ssize - stmp;
			buf_data.loc_head = 0;
			memcpy ((pcdata + stmp), &(buf_data.cring_buf[buf_data.loc_head]), ssize);
			buf_data.loc_head = ssize - 1;
		}
	}
	return stmp;
}

/**
 * @brief   : 计算队列中缓冲区实际数据长度
 * @param[in]
 * @param[out]
 * @return 多少个字节 buf_data.csize_data
 * @note
 */
unsigned short pctl_ctl_rx_rgbuf_get_size_byte (void)
{
	if (buf_data.loc_head <= buf_data.loc_tail)  //写入未回头
	{
		buf_data.size_data = buf_data.loc_tail - buf_data.loc_head;
	}
	else
	{
		buf_data.size_data = (D_SIZE_RX_RING_BUFFER - 1) - buf_data.loc_head;  //到边界的距离
		buf_data.size_data = buf_data.size_data + buf_data.loc_tail;
	}
	return buf_data.size_data;
}

/**
 * @brief   : 清空缓冲区:在数据读取完毕后，可以使用
 * @note
 */
void pctl_ctl_rx_rgbuf_reset_buf (void)
{
	buf_data.loc_head = 0;
	buf_data.loc_tail = 0;
	memset (&(buf_data.cring_buf[0]), 0, D_SIZE_RX_RING_BUFFER);
}

//*<---------------------- EVENT PROC
/**
 * @brief   配置回调函数：写接收数据到环形缓冲区
 * @param[in] *pcdata
 * @param[out] gst_buf_data
 * @note
 */
void on_rx_uart_data_wt_buf (unsigned char *pcdata)
{
	//printf ("@DEBUG on_rx_uart_data_wt_buf() \r\n");
	//printf ("@DEBUG *pcdata = %d \r\n", *pcdata);
	pctl_ctl_rx_rgbuf_wt_byte (pcdata);

	//pctl_ctl_rx_rgbuf_get_size_byte ();  //更新实际接收数据长度
}