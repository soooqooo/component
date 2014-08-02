#ifndef __LIST_H__
#define __LIST_H__

#include "structural_body.h"
#define Tatol_Link_tail						0xffff //链表尾
#define Tatol_Link_head						-1
#define NONE_Link_NUM						0
#define Insert_Link_P_prev					0
#define Insert_Link_P_next					1


#pragma pack(1) 
typedef struct Type_List       //链表结构体定义
{
	msg_send_Method_type msg_send_Method;
	JT_T_808_2011_data_type_def JT_T_808_2011_data;
	unsigned char  *data_buf;
	struct Type_List *prev;
	struct Type_List *next;
}JT_T_808_2011_data_type_Link;
#pragma pack()


int ADD_LINK_NOTE(JT_T_808_2011_data_type_Link** p1,JT_T_808_2011_data_type_Link* p2,
unsigned int prev_tail, int num,JT_T_808_2011_data_heah_type_def* code_ser,int *count_num);

JT_T_808_2011_data_type_Link* Link_node_find(JT_T_808_2011_data_type_Link* p1,
	int num,JT_T_808_2011_data_heah_type_def* code_ser);

#endif
