#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "list.h"

JT_T_808_2011_data_type_Link *Rec_LinkList=NULL;		//定义接受链表
JT_T_808_2011_data_type_Link *Send_LinkList=NULL;		//定义发送链表

/******************************************************************
函数名称:JT_T_808_2011_data_type_Link* Link_node_find(JT_T_808_2011_data_type_Link* p1,int num,JT_T_808_2011_data_heah_type_def* code_ser)
函数功能:
参数 :    num 查找的节点号

********************************************************************/
JT_T_808_2011_data_type_Link* Link_node_find(JT_T_808_2011_data_type_Link* p1,int num,JT_T_808_2011_data_heah_type_def* code_ser)
{
	JT_T_808_2011_data_type_Link *p2=NULL;
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
		}
	}
	if(num==Tatol_Link_tail || num==1)
	//if(num==Tatol_Link_tail )
	{
		return p2;
	}
	if(code_ser!=NULL)//只有一个链表时不进循环增加判断
	{
		if((p2->JT_T_808_2011_data.head1.ser_num==code_ser->ser_num)||(p2->JT_T_808_2011_data.head1.ID==code_ser->ID))
			return p2;
	}
	printf("Link_node_find end*********\n");
	return NULL;
}

/*
函数名称:ADD_LINK_NOTE
参数    :p1  发送链表指针地址 澹()
	         p2  这个是要发送数据的链表指针澹(在子函数中完成了)
	         prev_tail 头插入还尾插入标志位
		  num 插入节点号
		  code_ser  消息头
		  coun_num 消息流水
*/

int ADD_LINK_NOTE(JT_T_808_2011_data_type_Link** p1,JT_T_808_2011_data_type_Link* p2,
unsigned int prev_tail, int num,JT_T_808_2011_data_heah_type_def* code_ser,int *count_num)
{
	JT_T_808_2011_data_type_Link *p3=NULL,*p4=NULL;
	printf("ADD_LINK_NOTE start*********\n");
	if(num==Tatol_Link_head)
		p3=(*p1);
	else
		p3=Link_node_find(*p1,num,code_ser);
	if(p3)
	{
		if(prev_tail==Insert_Link_P_prev)//把P2加到P3头部
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
	else
	{
		(*p1)=p2;
	}
	(*count_num)++;
	return;
}

/******************************************************************
函数名称:int DEl_LINK_NOTE(JT_T_808_2011_data_type_Link** p1,int num,JT_T_808_2011_data_heah_type_def* code_ser,int *count_num)
删除链表节点链表顺序按照12345起始为1
参数 :p1发送链表地址
		num  节点
		code_ser  消息头(同下)
		count_num  流水(没什么用)
		
********************************************************************/
int DEl_LINK_NOTE(JT_T_808_2011_data_type_Link** p1,int num,JT_T_808_2011_data_heah_type_def* code_ser,int *count_num)
{
	JT_T_808_2011_data_type_Link *p2=NULL,*p3=NULL;
	int i=1;
		
	printf("DEl_LINK_NOTE start********\n");
	if(code_ser!=NULL)
		printf("code_ser->ser_num %x\n",code_ser->ser_num);
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
	else
	{
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
	if(p3 && (p3->data_buf))
	{
		free(p3->data_buf);
		p3->data_buf=NULL;
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

