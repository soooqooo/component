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

//#include<sys/stat.h> //fstat stat
//#include<unistd.h>//fstat
#include<dirent.h>//opendir,readdir
#include<unistd.h>

#include "MN_384_IC.h"
#include "Tlinked_list.h"
#include "add_msg_link.h"
unsigned short int SEND_MSG_LINK_count=0;
g_SEND_MSG_LINK_TYPE *SEND_MSG_DATA_LINK=NULL;
int PACK_SEND_MSG_LINK(unsigned char *msg , unsigned short int msg_len,unsigned char msg_type)
{
	g_SEND_MSG_LINK_TYPE *item = NULL, *tail = NULL, *first = NULL;
	int i=0;
	if (msg == NULL || msg_len <= 0 ) 
		{
		printf( "PACK_SEND_MSG_LINK: erro\r\n");	
		return -1;
		}
	
	Ser_Num++;
//	for(i=0;i<msg_len;i++)
	//	printf("msg[%d]= %x \n",i,msg[i]);
	item = (g_SEND_MSG_LINK_TYPE*)calloc(1, sizeof(g_SEND_MSG_LINK_TYPE));
	item->msg_H.msg_head= 0x7e;
	item->msg_H.msg_type = msg_type;
	item->msg_H.ser_num= Ser_Num;
	item->msg_H.msg_len = msg_len;	
	item->msg_data = (unsigned char*)calloc(1,msg_len);	
	memcpy(item->msg_data,msg,msg_len);
	item->next=NULL;
	item->prev=NULL;
	ADD_LINK_NOTE(&SEND_MSG_DATA_LINK,item,Insert_Link_P_next,Tatol_Link_tail,NULL,&SEND_MSG_LINK_count);
	if(SEND_MSG_LINK_count>MAX_SEND_MSG_LINK_count)
		{  /* 超过缓冲最大数目，尾部增加一个开头删除一个 */
		//printf(" first = Rec_LinkList \n");
		DEl_LINK_NOTE(&SEND_MSG_DATA_LINK,1,NULL,&SEND_MSG_LINK_count);
		//printf(" Data_Rec_count   MAX=%d\n",Data_Rec_count);
		}
}
void Compiled_Send_MSG(g_SEND_MSG_LINK_TYPE *msg,g_Compiled_Send_MSG_type* send_msg)
{
	unsigned char *p;
	unsigned char *p1;
	unsigned char check_sum=0;
	g_SEND_MSG_LINK_h_TYPE *msg_h;
	int i,j;
	msg_h = (g_SEND_MSG_LINK_h_TYPE *)calloc(1, sizeof(g_SEND_MSG_LINK_h_TYPE));
	p = (unsigned char *)calloc(1, 2048);
	memcpy((unsigned char *)msg_h,(unsigned char *)&msg->msg_H,sizeof(g_SEND_MSG_LINK_h_TYPE));
	msg_h->msg_len=cvt_end2(msg_h->msg_len);
	msg_h->ser_num=cvt_end2(msg_h->ser_num);
	memcpy(p,(unsigned char *)msg_h,sizeof(g_SEND_MSG_LINK_h_TYPE));
	memcpy(p+sizeof(g_SEND_MSG_LINK_h_TYPE),msg->msg_data,msg->msg_H.msg_len);
	send_msg->len=0;
	for(i=0;i<((msg->msg_H.msg_len)+sizeof(g_SEND_MSG_LINK_h_TYPE));i++)
		{
		if(i!=0)
			{
			if(p[i] == 0x7e)
				{
				*(send_msg->msg)++=0x7d;
				send_msg->len++;
				*(send_msg->msg)++=0x02;
				send_msg->len++;
				}
			else if(p[i] == 0x7d)
				{
				*(send_msg->msg)++=0x7d;
				send_msg->len++;
				*(send_msg->msg)++=0x01;
				send_msg->len++;
				}
			else{
				*(send_msg->msg)++=p[i];
				send_msg->len++;
				}
			check_sum=check_sum^p[i];
			printf("p[%d] = 0x%x      ",i,p[i]);
			printf("check_sum= 0x%x\n",check_sum);
			}
		else{
			*(send_msg->msg)++=p[i];
			send_msg->len++;
			}
		//printf(" p [%d] = %x\n",i,p[i]);
		}
	*(send_msg->msg)++=check_sum;
	send_msg->len++;
	*(send_msg->msg)++=0x7e;
	send_msg->len++;
	//*(send_msg->msg)++=0x7e;
	//send_msg->len++;
	for(i=0;i<send_msg->len;i++)
		*(send_msg->msg)--;
	for(i=0;i<send_msg->len;i++)
		printf("send_msg->msg[%d] = 0x%x",i,*(send_msg->msg)++);
	for(i=0;i<send_msg->len;i++)
		*(send_msg->msg)--;
	if(msg_h)free(msg_h);
	if(p)free(p);
	
}
