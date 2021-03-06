#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <stdio.h>




#include "timer.h"


extern int  Data_Send_count;
extern count_i;
struct itimerval value, ovalue, value2; 
extern JT_T_808_2011_data_type_Link *Send_LinkList;//定义J808接收数据单项链表
int Register_lizhen_ed=0;//后期调整到存储空间目前测试�
int count_lizhen_test=0;
int sec;
extern G_JT_T_808_2011_Parameter JT_T_808_2011_Parameter;

/********************************************************************************
函数名称:void sigroutine(int signo)
函数说明:定时器中断函数
参数   :signo  信号类别
*********************************************************************************8*/


void sigroutine(int signo)
{
	JT_T_808_2011_data_type_Link* L_ptr=NULL,*tail=NULL;
	int i;
	switch (signo)
	{
		case SIGALRM:
			signal(SIGALRM, sigroutine);
			if((count_i++)>30000)
				count_i=0;
			L_ptr=Send_LinkList;
			while(L_ptr!=NULL)
			{
				if(L_ptr->msg_send_Method.Resend_Timer>0)
					L_ptr->msg_send_Method.Resend_Timer--;
				else
				{
					if(L_ptr->msg_send_Method.Resend_count>0)
					{
						L_ptr->msg_send_Method.Resend_count--;
						L_ptr->msg_send_Method.Resend_Timer=(max_resend_count-L_ptr->msg_send_Method.Resend_count)*max_anw_timer;
						L_ptr->msg_send_Method.send_flage=1;
					}
				}
				L_ptr=L_ptr->next;
			}
			if(Register_lizhen_ed )//已经上线标志位
			{
				printf("Catch a signal --AA SIGALRM Register_lizhen_ed\n");
				if(count_lizhen_test<5)    //  2m*5  10m发一次心跳包
					count_lizhen_test++;
				else
				{
#if db				
					printf("Catch a signal --AA SIGALRM \n");
#endif
					pack_Register_send_msg(Device_Jumper,NULL,NULL);
					count_lizhen_test=0;
				}
			}
			i=1;		
			break;
		case SIGVTALRM:
			signal(SIGVTALRM, sigroutine);
			break;
	}
	return;
}
/***************************************************************************
函数名称:void timer_init(void)
函数功能:启动定时器信号
****************************************************************************/
void timer_init(void)
{
	
	sec = 5;
	signal(SIGALRM, sigroutine);
	signal(SIGVTALRM, sigroutine);
	value.it_value.tv_sec = 2;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &value, &ovalue);     //(定时2s)
	value2.it_value.tv_sec = 0;
	value2.it_value.tv_usec = 500000;
	value2.it_interval.tv_sec = 0;
	value2.it_interval.tv_usec = 500000;
	setitimer(ITIMER_VIRTUAL, &value2, &ovalue);//(定时500ms)
}


