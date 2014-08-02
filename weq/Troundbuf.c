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

#include "Troundbuf.h"
//#include "MN_384_IC.h"


/*******************************************************************
** ������:     NL_InitRoundBuf
** ��������:   ��ʼ��ѭ��������
** ����:       [in]  round:           ѭ��������
**             [in]  mem:             ѭ����������������ڴ��ַ
**             [in]  memsize:         ѭ����������������ڴ��ֽ���
** ����:       ��
********************************************************************/
void NL_InitRoundBuf(NL_ROUNDBUF_T *round, unsigned char *mem, unsigned int memsize)
{
    round->bufsize = memsize;
    round->used    = round->rused=0;
    round->bptr    = mem;
    round->eptr    = mem + memsize;
    round->rrptr =round->wptr = round->rptr = round->bptr;
}

/*******************************************************************
** ������:     NL_ResetRoundBuf
** ��������:   ��λѭ��������, ����ѭ������������ʹ���ֽ�����0
** ����:       [in]  round:           ѭ��������
** ����:       ��
********************************************************************/
void NL_ResetRoundBuf(NL_ROUNDBUF_T *round)
{
    //round->used = 0;
    //round->rptr = round->wptr = round->bptr;
     round->used    = round->rused=0;
    round->rrptr =round->wptr = round->rptr = round->bptr;
}

/*******************************************************************
** ������:     NL_RoundBufStartPos
** ��������:   ��ȡѭ���������������ڴ����ʼָ��
** ����:       [in]  round:           ѭ��������
** ����:       �������ڴ����ʼָ��
********************************************************************/
unsigned char *NL_RoundBufStartPos(NL_ROUNDBUF_T *round)
{
    return round->bptr;
}

/*******************************************************************
** ������:     NL_Gps_WriteRoundBuf
** ��������:   ��ѭ����������д��һ���ֽڵ�����
** ����:       [in]  round:           ѭ��������
**             [in]  data:              ��д�������
** ����:       ��д֮ǰѭ���������е�ʹ���ֽ����ﵽ�������ڴ���ֽ���, 
**             �򷵻�-1; ����, ����0
********************************************************************/
int NL_WriteRoundBuf(NL_ROUNDBUF_T *round, unsigned char data)
{
    if(NULL == round) return -1;
    if (round->used >= round->bufsize) return -1;
    *round->wptr++ = data;
    if (round->wptr >= round->eptr) 
	{
        round->wptr = round->bptr;
    }
    round->used++;
    return 0;
}

/*******************************************************************
** ������:     NL_ReadRoundBuf
** ��������:   ��ѭ���������ж�ȡһ���ֽڵ�����
** ����:       [in]  round:           ѭ��������
** ����:       ���֮ǰѭ���������е�ʹ���ֽ���Ϊ0, �򷵻�-1;
**             ����, ���ض�ȡ�����ֽ�
********************************************************************/
int NL_ReadRoundBuf(NL_ROUNDBUF_T *round)
{
    int ret;
    
    if (round->used == 0) return -1;
    ret = *round->rptr++;
    if (round->rptr >= round->eptr)
	{
        round->rptr = round->bptr;
    }
    round->used--;
    return ret;
}


/*******************************************************************
** ������:     NL_ReadRoundNOMVBuf
** ��������:   ��ѭ���������ж�ȡһ���ֽڵ����ݲ��ı��ȡָ���ʹ�ÿռ�
** ����:       [in]  round:           ѭ��������
** ����:       ���֮ǰѭ���������е�ʹ���ֽ���Ϊ0, �򷵻�-1;
**             ����, ���ض�ȡ�����ֽ�
********************************************************************/
int NL_ReadRoundNOMVBuf(NL_ROUNDBUF_T *round)
{
    int ret;
    if (round->rused == 0) return -1;
    ret = *round->rrptr++;
    if (round->rrptr >= round->eptr)
	{
        round->rrptr = round->bptr;
    }
    round->rused--;
    return ret;
}

/*******************************************************************
** ������:     NL_SETReadRoundBuf
** ��������:   ����ѭ���������ж�ȡָ���ʹ�ÿռ�Ϊ�ݴ�
** ����:       [in]  round:           ѭ��������
** ����:       ���֮ǰѭ���������е�ʹ���ֽ���Ϊ0, �򷵻�-1;
**             ����, ���ض�ȡ�����ֽ�
********************************************************************/
void NL_SETReadRoundBuf(NL_ROUNDBUF_T *round)
{
    int ret;
	while(round->rptr!=round->rrptr)
		{
		round->rptr++;
    		if (round->rptr >= round->eptr)
        		round->rptr = round->bptr;
		round->used--;
		}
	round->rused=round->used;
}

/*******************************************************************
** ������:     NL_RESETReadRoundBuf
** ��������:   ����ѭ���������ж�ȡָ���ʹ�ÿռ�Ϊ��ǰ
** ����:       [in]  round:           ѭ��������
** ����:       ���֮ǰѭ���������е�ʹ���ֽ���Ϊ0, �򷵻�-1;
**             ����, ���ض�ȡ�����ֽ�
********************************************************************/
void NL_RESETReadRoundBuf(NL_ROUNDBUF_T *round)
{
    int ret;
	round->rrptr=round->rptr;
	round->rused=round->used;
}

/*******************************************************************
** ������:     NL_ReadRoundBufNoMVPtr
** ��������:   �ٲ��ƶ�������ָ��������,��ѭ���������ж�ȡһ���ֽڵ�����
** ����:       [in]  round:           ѭ��������
** ����:       ʣ��Ŀ����ֽ���
********************************************************************/
int NL_ReadRoundBufNoMVPtr(NL_ROUNDBUF_T *round)
{
    if (round->used == 0) return -1;
    else return *round->rptr; 
}

/*******************************************************************
** ������:     NL_LeftOfRoundBuf
** ��������:   ��ȡѭ����������ʣ��Ŀ����ֽ���
** ����:       [in]  round:           ѭ��������
** ����:       ʣ��Ŀ����ֽ���
********************************************************************/
unsigned int NL_LeftOfRoundBuf(NL_ROUNDBUF_T *round)
{
    return (round->bufsize - round->used);
}

/*******************************************************************
** ������:     NL_UsedOfRoundBuf
** ��������:   ��ȡѭ������������ʹ���ֽ���
** ����:       [in]  round:           ѭ��������
** ����:       ��ʹ�õ��ֽ���
********************************************************************/
unsigned int NL_UsedOfRoundBuf(NL_ROUNDBUF_T *round)
{
    return round->used;
}

/*******************************************************************
** ������:     NL_WriteBlockRoundBuf
** ��������:   ��ѭ����������д��һ�����ݵ�Ԫ
** ����:       [in]  round:           ѭ��������
**             [in]  bptr:            ��д�����ݿ��ָ��
**             [in]  blksize:         ��д�����ݿ���ֽ���
** ����:       �ɹ�д��ѭ�����������ֽ���
********************************************************************/
int NL_WriteBlockRoundBuf(NL_ROUNDBUF_T *round, unsigned char *bptr, unsigned int blksize)
{
	printf("NL_WriteBlockRoundBuf start \n");
    if (blksize > NL_LeftOfRoundBuf(round)) return -1;
    for (; blksize > 0; blksize--) 
	{ 
       *round->wptr++ = *bptr++;
       if (round->wptr >= round->eptr) round->wptr = round->bptr;
       round->used++;
    }    
	printf("round->used %d\n",round->used);
	printf("NL_WriteBlockRoundBuf end\n");
    return 0;
}

/*******************************************************************
** ������:     NL_BackRoundBuf
** ��������:   �ص�ѭ���������ݴ��ȡָ���ʹ�ÿռ�
** ����:       [in]  round:           ѭ��������
** ����:       ���֮ǰѭ���������е�ʹ���ֽ���Ϊ0, �򷵻�-1;
**             ����, ���ض�ȡ�����ֽ�
********************************************************************/
int NL_BackRoundBuf(NL_ROUNDBUF_T *round,int count)
{
//    int ret;
    
//    if (round->used == 0) return -1;
	while(count--)
		{
		if (round->rrptr <= round->bptr)
			{
			printf("NL_BackRoundBuf over\n");
			round->rrptr = round->eptr;
			}
		*round->rrptr--;
		round->rused++;
		}
    return 1;
}
