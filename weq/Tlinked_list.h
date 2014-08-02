#ifndef _TLINKED_LIST_H_
#define _TLINKED_LIST_H_

#include "add_msg_link.h"

#define Tatol_Link_tail						0xffff
#define Tatol_Link_head						-1
#define NONE_Link_NUM						0
#define Insert_Link_P_prev					0
#define Insert_Link_P_next					1
extern g_SEND_MSG_LINK_TYPE* Link_node_find(g_SEND_MSG_LINK_TYPE* p1,int num,g_SEND_MSG_LINK_TYPE* code_ser);
extern int DEl_LINK_NOTE(g_SEND_MSG_LINK_TYPE** p1,int num,g_SEND_MSG_LINK_TYPE* code_ser,unsigned short int  *count_num);
extern int ADD_LINK_NOTE(g_SEND_MSG_LINK_TYPE** p1,g_SEND_MSG_LINK_TYPE* p2,unsigned int prev_tail, int num,g_SEND_MSG_LINK_TYPE* code_ser,unsigned short int *count_num);
#endif
