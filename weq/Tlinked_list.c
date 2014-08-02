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

#include "Tlinked_list.h"
/******************************************************************
删除链表节点链表顺序按照12345起始为1
********************************************************************/
int DEl_LINK_NOTE(g_SEND_MSG_LINK_TYPE** p1,int num,g_SEND_MSG_LINK_TYPE* code_ser,unsigned short int  *count_num)
{
	g_SEND_MSG_LINK_TYPE *p2=NULL,*p3=NULL;
	int i=1;
	/*
	if(num>0)
		i=num-1;
	else
		i=num;*/
		
	printf("DEl_LINK_NOTE start********\n");
	p2=Link_node_find(*p1,num,code_ser);
	#if 1
	if(p2==NULL)
			{
			printf("Link_node_find p2 erro");
			return -1;
			}
	
	if(p2->prev==NULL)
		{
		p3=*p1;
		if((*p1)->next!=NULL)
			(*p1)->next->prev=NULL;
		*p1=(*p1)->next;
		}
	else{
		printf("p2 is %x\n",p2);
		p3=p2;
		p3->prev->next=p3->next;
		printf("p3->prev->next is %x\n",p3->next);
		if(p3->next!=NULL)
			{
			p3->next->prev=p3->prev;
			printf("p3->next->prev is %x\n",p3->prev);
			}
		}
	
	if(p3 && (p3->msg_data))
		{
		free(p3->msg_data);
		p3->msg_data=NULL;
		}
	if(p3)
		{
		printf("free(p3) is \n");
		printf("p3 is %x\n",p3);
		free(p3);
		//p3=NULL;
		}
	printf("DEl_LINK_NOTE end*********\n");
	(*count_num)--;
	#endif
	return 0;
}
g_SEND_MSG_LINK_TYPE* Link_node_find(g_SEND_MSG_LINK_TYPE* p1,int num,g_SEND_MSG_LINK_TYPE* code_ser)
{
	g_SEND_MSG_LINK_TYPE *p2=NULL;
	int i=1;
	//添加判断是否全部信息没有全无时进入死循环
	//num=num-1;
	p2=p1;
	printf("Link_node_find start*********\n");
	while(p2 && p2->next)
		{
		if(num!=NONE_Link_NUM)
			{
			if(num==i)
				{
				return p2;
				}
			i++;
			p2=p2->next;
			}
		else if(code_ser!=NULL)
			{
			#if 0
			if((code_ser->ID!= 0)||(code_ser->ser_num!=0))
				{
				if((code_ser->ser_num!=0)&&(code_ser->ID!= 0))
					{
					}
				else if((code_ser->ser_num)!=0)
					{
					printf("p2->JT_T_808_2011_data.head1.ser_num = %x\n",p2->JT_T_808_2011_data.head1.ser_num);
					if((p2->JT_T_808_2011_data.head1.ser_num)==(code_ser->ser_num))
						{
						printf("get  p2->JT_T_808_2011_data.head1.ser_num = %x\n",p2->JT_T_808_2011_data.head1.ser_num);
						return p2;
						}
					}
				else if(code_ser->ID!=0)
					{
					if(p2->JT_T_808_2011_data.head1.ID==code_ser->ID)
						{
						printf("p2->JT_T_808_2011_data.head1.ID = %x\n",p2->JT_T_808_2011_data.head1.ID);
						return p2;
						}
				}
			p2=p2->next;
			}
			#endif
			}
		}
	if(num==Tatol_Link_tail || num==1)
		{
		return p2;
		}
	if(code_ser!=NULL)//只有一个链表时不进循环增加判断
		{
		#if 0
		if((p2->JT_T_808_2011_data.head1.ser_num==code_ser->ser_num)||(p2->JT_T_808_2011_data.head1.ID==code_ser->ID))
			return p2;
		#endif
		}
	printf("Link_node_find end*********\n");
	return NULL;
}
int ADD_LINK_NOTE(g_SEND_MSG_LINK_TYPE** p1,g_SEND_MSG_LINK_TYPE* p2,unsigned int prev_tail, int num,g_SEND_MSG_LINK_TYPE* code_ser,unsigned short int *count_num)
{
	g_SEND_MSG_LINK_TYPE *p3=NULL,*p4=NULL;
	printf("ADD_LINK_NOTE start*********\n");
	if(num==Tatol_Link_head)
		p3=(*p1);
	else
		p3=Link_node_find(*p1,num,code_ser);
	if(p3)
		{
		//p4=p3;
		if(prev_tail==Insert_Link_P_prev)//加到P3头部
			{
			printf("p2 is %x\n",p2);
			p2->prev=p3->prev;
			printf("p2->prev is %x\n",p2->prev);
			p2->next=p3;
			printf("p2->next is %x\n",p2->next);
			if(p3->prev!=NULL)
				{
				
				p3->prev->next=p2;
				printf("p3->prev->next is %x\n",p3->prev->next);
				}
			p3->prev=p2;
			printf("p3->prev is %x\n",p3->prev);
			printf("(*p1) is %x\n",(*p1));
			if(p2->prev==NULL)
				{
				while(p3 && p3->prev)
					{
					p3=p3->prev;
					}
				(*p1)=p3;
				}
			}
		else//加到尾部
			{
			p2->prev=p3;//
			p2->next=p3->next;
			if(p3->next!=NULL)
				p3->next->prev=p2;
			p3->next=p2;
			
			}
		}
	else{
		(*p1)=p2;
		}
	(*count_num)++;
	return;
}