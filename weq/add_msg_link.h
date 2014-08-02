#ifndef _ADD_MSG_LINK_H_
#define _ADD_MSG_LINK_H_
#define MAX_SEND_MSG_LINK_count  4000
#define cvt_end2(s) (((s<<8) & 0xFF00) | ((s>>8) & 0x00FF))

#pragma pack(1) /* 指定对齐值为 1 */
typedef struct SEND_MSG_LINK_h_TYPE
{
	unsigned char msg_head;
	unsigned char msg_type;
	unsigned short int ser_num;
	unsigned short int msg_len;
}g_SEND_MSG_LINK_h_TYPE;
typedef struct SEND_MSG_LINK_TYPE
{
	struct SEND_MSG_LINK_h_TYPE msg_H;
	unsigned char *msg_data;
	struct SEND_MSG_LINK_TYPE *prev;
	struct SEND_MSG_LINK_TYPE *next;
}g_SEND_MSG_LINK_TYPE;

typedef struct Compiled_Send_MSG_type
{
	unsigned short int len;
	unsigned char *msg;
}g_Compiled_Send_MSG_type;
#pragma pack() /* 指定对齐值为 1 */
#define gps_date 1
#define can_date 2
extern g_SEND_MSG_LINK_TYPE *SEND_MSG_DATA_LINK;
extern unsigned short int SEND_MSG_LINK_count;
int PACK_SEND_MSG_LINK(unsigned char *msg , unsigned short int msg_len,unsigned char msg_type);
#endif
