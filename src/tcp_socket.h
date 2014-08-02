#ifndef __TCP_SOCKET_H__
#define  __TCP_SOCKET_H__

#include "defined.h"
#include "structural_body.h"
#include "list.h" 
#include "roundbuf.h"

void init_flage();
void* thr_Creat_TCP_Socket();

void Creat_TCP_Socket();
void* thr_TCP_Rcv();
void TCP_Rcv_Data();
void Get_Tcp_Data(NL_ROUNDBUF_T *round, unsigned char *msg, int maxlen );
void Analyze_Translation(unsigned char* msg,int len);
int Check_JT_T_808_2011_Transmission_DATA(unsigned char* buf,int len);
void Recv_Data_Send_Link(unsigned char* buf,int len);
void* thr_test_msg_write();
void TCP_Send_Data();
void pack_Register_send_msg(unsigned short int id,msg_buf_type* msgbuf,JT_T_808_2011_data_type_Link *prt);
send_data_msg* List_buff(JT_T_808_2011_data_type_Link *ptr);











#endif

