#ifndef __TIMER_H__
#define __TIMER_H__

//#include "defined.h"
//#include "structural_body.h"
//#include "timer.h"
//#include "set_parameter.h" 
//#include "list.h"
//#include "tcp_socket.h"
//#include "analyze_rec.h"
//#include "roundbuf.h"

extern unsigned int count_i;


void timer_init(void);
void sigroutine(int signo);
//void pack_Register_send_msg(unsigned short int id,msg_buf_type* msgbuf,JT_T_808_2011_data_type_Link *prt);

#endif

