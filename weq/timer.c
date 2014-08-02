#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include<dirent.h>//opendir,readdir
#include<unistd.h>

#include "timer.h"
//#include "Add_msg_link.h"
//#include "Link_list.h"


#define max_resend_count	5//ÖØ´«´ÎÊýºóÆÚµ÷ÓÃÉèÖÃ
#define max_anw_timer		5//Ó¦´ð³¬Ê±Ê±¼äºóÆÚµ÷ÓÃÉèÖÃ
#define MAX_Send_COUNT	10

static int  Data_Send_count=0;
unsigned int count_i=0;
struct itimerval value, ovalue, value2; 
//JT_T_808_2011_data_type_Link *Send_LinkList=NULL;//¶¨ÒåJ808½ÓÊÕÊý¾Ýµ¥ÏîÁ´±í
int Register_lizhen_ed=0;//ºóÆÚµ÷Õûµ½´æ´¢¿Õ¼äÄ¿Ç°²âÊÔÓ
int count_lizhen_test=0;
int sec;
//extern G_JT_T_808_2011_Parameter JT_T_808_2011_Parameter;




void sigroutine(int signo)
{
//	JT_T_808_2011_data_type_Link* L_ptr=NULL,*tail=NULL;
	int i;
	switch (signo)
	{
		case SIGALRM:
			//printf("Catch a signal --AA SIGALRM \n");
			signal(SIGALRM, sigroutine);
			if((count_i++)>30000)
				count_i=0;
			#if 0
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
			//sem_post (&wait_timer);
			if(Register_lizhen_ed )
			{
				printf("Catch a signal --AA SIGALRM Register_lizhen_ed\n");
				if(count_lizhen_test<5)
					count_lizhen_test++;
				else
				{
					printf("Catch a signal --AA SIGALRM \n");
					pack_Register_send_msg(Device_Jumper,NULL,NULL);
					//ser_num+=1;
					count_lizhen_test=0;
				}
			}
			i=1;	
			#endif
			break;
		case SIGVTALRM:
			signal(SIGVTALRM, sigroutine);
			break;
	}
	return;
}

void timer_init(void)
{
	printf("timer_init\n");
	sec = 5;
	signal(SIGALRM, sigroutine);
	signal(SIGVTALRM, sigroutine);
	value.it_value.tv_sec = 1;
	value.it_value.tv_usec = 0;
	value.it_interval.tv_sec = 1;
	value.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL, &value, &ovalue);     //(¶¨Ê±2s)
	value2.it_value.tv_sec = 0;
	value2.it_value.tv_usec = 500000;
	value2.it_interval.tv_sec = 0;
	value2.it_interval.tv_usec = 500000;
	setitimer(ITIMER_VIRTUAL, &value2, &ovalue);//(¶¨Ê±500ms)
}


