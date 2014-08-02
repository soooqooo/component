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

#include "Tchange_data.h"
/*******************************************************************
** ��������:  ��ASCII��ת��Ϊ16��������ΧΪ0~9;A~F;a~f
** ����:       [in]    msg_in:     	������Ҫת������BUFF
**             	   [in]    len :   		������Ҫת�����ݳ���
**			   [out]    msg_out:		���ת��������BUFF
**			   [out]    :			���ת���󳤶�
** ����:       �������ݳ���
********************************************************************/

unsigned short int ASCII_TO_16(unsigned char*msg_in,unsigned char*msg_out,unsigned short int len)
{
	int i=0,j=0;
	for(i=0;i<len;i++)
		{
		j++;
		if((msg_in[i]<0x3a)&&(msg_in[i]>0x2f))
			msg_out[i]=msg_in[i]-0x30;
		else if((msg_in[i]<0x47)&&(msg_in[i]>0x40))
			msg_out[i]=msg_in[i]-0x37;
		else if((msg_in[i]<0x67)&&(msg_in[i]>0x60))
			msg_out[i]=msg_in[i]-0x57;
		else
			j--;
		
		}
	return j;
}
/*******************************************************************
** ��������:  ����������ת��Ϊ���ֽ�WORD��
** ����:       [in]    msg_in:     		������Ҫת������BUFF
**             	   [in]    len :   			������Ҫת�����ݳ���
**			   [out]  move_count:		��Ҫ��λλ��
**			   [out]    :			���ת�������ֽ�WORD��
** ����:       �������ݳ���
********************************************************************/

unsigned short int char_TO_word(unsigned char*msg_in,unsigned short int len,unsigned char move_count)
{
	int i=0;
	unsigned short int j=0;
	for(i=0;i<len;i++)
		{
		j<<=move_count;
		j=j+msg_in[i];
		}
	return j;
}
/*******************************************************************
** ��������:  ����������ת��Ϊ���ֽ�LONG��
** ����:       [in]    msg_in:     		������Ҫת������BUFF
**             	   [in]    len :   			������Ҫת�����ݳ���
**			   [out]  move_count:		��Ҫ��λλ��
**			   [out]    :			���ת�������ֽ�LONG��
** ����:       �������ݳ���
********************************************************************/

unsigned  long char_TO_long(unsigned char*msg_in,unsigned short int len,unsigned char move_count)
{
	int i=0;
	unsigned  long j=0;
	for(i=0;i<len;i++)
		{
		j<<=move_count;
		j=j+msg_in[i];
		}
	return j;
}
/*******************************************************************
** ��������:  ����������ת��ΪCHAR��
** ����:       [in]    msg_in:     		������Ҫת������BUFF
**             	   [in]    len :   			������Ҫת�����ݳ���
**			   [out]  move_count:		��Ҫ��λλ��
**			   [out]    :			���ת����CHAR��
** ����:       �������ݳ���
********************************************************************/

unsigned char char_TO_char(unsigned char*msg_in,unsigned short int len,unsigned char move_count)
{
	int i=0;
	unsigned char j=0;
	for(i=0;i<len;i++)
		{
		j<<=move_count;
		j=j+msg_in[i];
		}
	return j;
}