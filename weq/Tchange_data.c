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
** 函数描述:  将ASCII码转换为16进制数范围为0~9;A~F;a~f
** 参数:       [in]    msg_in:     	输入需要转换数据BUFF
**             	   [in]    len :   		输入需要转换数据长度
**			   [out]    msg_out:		输出转换后数据BUFF
**			   [out]    :			输出转换后长度
** 返回:       接收数据长度
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
** 函数描述:  将输入数组转换为两字节WORD型
** 参数:       [in]    msg_in:     		输入需要转换数据BUFF
**             	   [in]    len :   			输入需要转换数据长度
**			   [out]  move_count:		需要移位位数
**			   [out]    :			输出转换后两字节WORD型
** 返回:       接收数据长度
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
** 函数描述:  将输入数组转换为四字节LONG型
** 参数:       [in]    msg_in:     		输入需要转换数据BUFF
**             	   [in]    len :   			输入需要转换数据长度
**			   [out]  move_count:		需要移位位数
**			   [out]    :			输出转换后四字节LONG型
** 返回:       接收数据长度
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
** 函数描述:  将输入数组转换为CHAR型
** 参数:       [in]    msg_in:     		输入需要转换数据BUFF
**             	   [in]    len :   			输入需要转换数据长度
**			   [out]  move_count:		需要移位位数
**			   [out]    :			输出转换后CHAR型
** 返回:       接收数据长度
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