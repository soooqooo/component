#ifndef _GET_GPS_DATE_H_
#define _GET_GPS_DATE_H_

#include "Troundbuf.h"
#define file_get_fifo	"./gps_file.txt"
/******���λ���*********/
#define MSG_DEFAULT_LEN 2048   //���ջ��λ����С
extern  NL_ROUNDBUF_T tcpround; //���廷�λ�������
extern unsigned char s_tcpbuf[MSG_DEFAULT_LEN];


extern unsigned long read_count;
extern unsigned char debug_print_en;

extern unsigned char en_send_flage;

typedef struct 
{
	unsigned char GPS_DATA[MSG_DEFAULT_LEN];
	unsigned short int GPS_DATA_len;
	unsigned short int GPS_t_msglen;
}g_GPS_DATA_BUF;
extern g_GPS_DATA_BUF GPS_DATA_BUF;
void* thr_GET_GPS(void);
void Creat_GET_GPS(void);
//�����Ҫ����
//void Get_Find_STR_Data(NL_ROUNDBUF_T *round, int maxlen, unsigned char *h_str,unsigned char *h_end,int include_h, unsigned char *t_str,unsigned char *t_end,int include_t );


#endif
