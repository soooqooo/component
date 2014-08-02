#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "roundbuf.h"
#include "find_str.h"

/*******************************************************************
** ��������:   ��TCP��������ȡһ������
** ����:       [in]    round:        ������
**             	   [in]    maxlen :    �����յĳ���
**			   [in]    h_str:		������ʼ���鴮����ʼ�ض�����
**			   [in]    h_end:		������ʼ���鴮�Ľ����ض�����
**			   [in]    include_h:	�Ƿ����ͷ��ʼ�ض�����1��������0��������
**			   [in]    t_str:		���ҽ������鴮����ʼ�ض�����
**			   [in]    t_end:		���ҽ������鴮�Ľ����ض�����
**			   [in]    include_t:	�Ƿ����β��ʼ�ض�����1��������0��������
** ����:       �������ݳ���
********************************************************************/
unsigned short int Get_Find_STR_Data(unsigned char* msg,NL_ROUNDBUF_T *round, int maxlen, unsigned char *h_str,unsigned char *h_end,int include_h, unsigned char *t_str,unsigned char *t_end,int include_t )
{
	int recv, rlen = 0;
	int i,j=0,k=0;
	int h_str_size=0,t_str_size=0,h_end_size=0,t_end_size=0;
	unsigned short int h_msglen=0,t_msglen=0;
	unsigned short int msglen=0,h_str_len=0,h_end_len=0,t_str_len=0,t_end_len=0;
	unsigned char get_flage=0;
	printf("Get_Tcp_Data start \n");
	if(h_str)
		h_str_size=strlen(h_str);
		t_str_size=strlen(t_str);
	if(h_end == NULL)
		h_end_size=0;
	else
		h_end_size=strlen(h_end);
	if(t_end == NULL)
		t_end_size=0;
	else
		t_end_size=strlen(t_end);
	NL_RESETReadRoundBuf(round);
	while((recv = NL_ReadRoundNOMVBuf(round)) != -1) 
		{
		{
			if((h_str_len>=h_str_size) && (h_end_len<h_end_size))
				h_msglen++;
			if((t_str_len>=t_str_size) && (t_end_len<t_end_size))
				t_msglen++;
			if(msglen>=maxlen)
					{
					 /* ����������� */
					printf("data out!");
					 h_msglen=0;t_msglen=0;
					 msglen=0;h_str_len=0;h_end_len=0;t_str_len=0;t_end_len=0;

					}
				else{
					msg[(msglen)]=recv;
						(msglen)++;
					}
			}
		if(h_str_len<h_str_size)
			{
			if(recv==h_str[h_str_len])
				{
				h_msglen++;
				h_str_len++;
				}
			else
				{
				msglen=0;
				h_msglen=0;
				h_str_len=0;
				}
			}
		else if((h_end_len<h_end_size) && (h_str_len>=h_str_size))
			{
			if(recv==h_end[h_end_len])
				h_end_len++;
			else
				h_end_len=0;
			}
		else if((t_str_len<t_str_size) && (h_end_len>=h_end_size))
			{
			if(recv==t_str[t_str_len])
				{
				t_msglen++;
				t_str_len++;
				}
			else
				{
				t_msglen=0;
				t_str_len=0;
				}
			}
		else if((t_end_len<t_end_size) && (t_str_len>=t_str_size))
			{
			if(recv==t_end[t_end_len])
				t_end_len++;
			else
				t_end_len=0;
			}
		if((t_end_len>=t_end_size) && (t_str_len>=t_str_size) && (h_end_len>=h_end_size) && (h_str_len>=h_str_size) )
			{
			if(msglen<10)//������ݹ���Ŀǰֻ֧�ֵ����ֽ�
				{
				printf("get total  msglen erro\n");
				printf("recv222=%x\n",recv);
				h_msglen=0;t_msglen=0;
				msglen=0;h_str_len=0;h_end_len=0;t_str_len=0;t_end_len=0;
				if(h_str_len<h_str_size)
					{
					if(recv==h_str[h_str_len])
						{
						msg[(msglen)]=recv;
						h_msglen++;
						h_str_len++;
						msglen++;
						}
					else
						{
						msglen=0;
						h_msglen=0;
						h_str_len=0;
						}
					}
				}
			else{
				//�õ�����
				int count=0;
				//�õ�ȫ�����д���
				printf("get total\n");
				//msg[msglen++]=recv;
				if(include_t==0)
					{
					msglen=msglen - t_msglen;
					count=t_msglen+1;
					}
				if(include_h==0)
					{//������ʼ�����ַ���
					unsigned char *p=NULL;
					printf("h_msglen=%d\n",h_msglen);
					msglen=msglen-h_msglen;
					p = (unsigned char*)calloc(1, maxlen);
					memcpy(p,msg+h_msglen,msglen);
					memcpy(msg,p,maxlen);
					free(p);
					}
				printf("msglen=%d\n",msglen);
				#if 1
				//if(debug_print_en)
					{
					printf("\nget msg is : ");
					for(i=0;i<(msglen);i++)
						{
						printf("%x ",msg[i]);
						}
					printf("\r\n");
					}
				#endif
				NL_SETReadRoundBuf(round);
				printf("recv111=%c\n",recv);
				break;
				}
			}
			

		}
	
	if(get_flage)
		{
		printf("get_flage_msglen=%d\n",msglen);
		return msglen;
		}
	else
		NL_RESETReadRoundBuf(round);
	printf("cant_find msglen=%d\n",msglen);
	return 0;
}


