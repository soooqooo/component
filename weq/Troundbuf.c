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
** 函数名:     NL_InitRoundBuf
** 函数描述:   初始化循环缓冲区
** 参数:       [in]  round:           循环缓冲区
**             [in]  mem:             循环缓冲区所管理的内存地址
**             [in]  memsize:         循环缓冲区所管理的内存字节数
** 返回:       无
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
** 函数名:     NL_ResetRoundBuf
** 函数描述:   复位循环缓冲区, 即将循环缓冲区的已使用字节数清0
** 参数:       [in]  round:           循环缓冲区
** 返回:       无
********************************************************************/
void NL_ResetRoundBuf(NL_ROUNDBUF_T *round)
{
    //round->used = 0;
    //round->rptr = round->wptr = round->bptr;
     round->used    = round->rused=0;
    round->rrptr =round->wptr = round->rptr = round->bptr;
}

/*******************************************************************
** 函数名:     NL_RoundBufStartPos
** 函数描述:   获取循环缓冲区所管理内存的起始指针
** 参数:       [in]  round:           循环缓冲区
** 返回:       所管理内存的起始指针
********************************************************************/
unsigned char *NL_RoundBufStartPos(NL_ROUNDBUF_T *round)
{
    return round->bptr;
}

/*******************************************************************
** 函数名:     NL_Gps_WriteRoundBuf
** 函数描述:   往循环缓冲区中写入一个字节的数据
** 参数:       [in]  round:           循环缓冲区
**             [in]  data:              待写入的数据
** 返回:       如写之前循环缓冲区中的使用字节数达到所管理内存的字节数, 
**             则返回-1; 否则, 返回0
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
** 函数名:     NL_ReadRoundBuf
** 函数描述:   从循环缓冲区中读取一个字节的数据
** 参数:       [in]  round:           循环缓冲区
** 返回:       如读之前循环缓冲区中的使用字节数为0, 则返回-1;
**             否则, 返回读取到的字节
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
** 函数名:     NL_ReadRoundNOMVBuf
** 函数描述:   从循环缓冲区中读取一个字节的数据不改变读取指针和使用空间
** 参数:       [in]  round:           循环缓冲区
** 返回:       如读之前循环缓冲区中的使用字节数为0, 则返回-1;
**             否则, 返回读取到的字节
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
** 函数名:     NL_SETReadRoundBuf
** 函数描述:   调整循环缓冲区中读取指针和使用空间为暂存
** 参数:       [in]  round:           循环缓冲区
** 返回:       如读之前循环缓冲区中的使用字节数为0, 则返回-1;
**             否则, 返回读取到的字节
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
** 函数名:     NL_RESETReadRoundBuf
** 函数描述:   调整循环缓冲区中读取指针和使用空间为当前
** 参数:       [in]  round:           循环缓冲区
** 返回:       如读之前循环缓冲区中的使用字节数为0, 则返回-1;
**             否则, 返回读取到的字节
********************************************************************/
void NL_RESETReadRoundBuf(NL_ROUNDBUF_T *round)
{
    int ret;
	round->rrptr=round->rptr;
	round->rused=round->used;
}

/*******************************************************************
** 函数名:     NL_ReadRoundBufNoMVPtr
** 函数描述:   再不移动缓冲区指针的情况下,从循环缓冲区中读取一个字节的数据
** 参数:       [in]  round:           循环缓冲区
** 返回:       剩余的可用字节数
********************************************************************/
int NL_ReadRoundBufNoMVPtr(NL_ROUNDBUF_T *round)
{
    if (round->used == 0) return -1;
    else return *round->rptr; 
}

/*******************************************************************
** 函数名:     NL_LeftOfRoundBuf
** 函数描述:   获取循环缓冲区中剩余的可用字节数
** 参数:       [in]  round:           循环缓冲区
** 返回:       剩余的可用字节数
********************************************************************/
unsigned int NL_LeftOfRoundBuf(NL_ROUNDBUF_T *round)
{
    return (round->bufsize - round->used);
}

/*******************************************************************
** 函数名:     NL_UsedOfRoundBuf
** 函数描述:   获取循环缓冲区中已使用字节数
** 参数:       [in]  round:           循环缓冲区
** 返回:       已使用的字节数
********************************************************************/
unsigned int NL_UsedOfRoundBuf(NL_ROUNDBUF_T *round)
{
    return round->used;
}

/*******************************************************************
** 函数名:     NL_WriteBlockRoundBuf
** 函数描述:   往循环缓冲区中写入一块数据单元
** 参数:       [in]  round:           循环缓冲区
**             [in]  bptr:            待写入数据块的指针
**             [in]  blksize:         待写入数据块的字节数
** 返回:       成功写入循环缓冲区的字节数
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
** 函数名:     NL_BackRoundBuf
** 函数描述:   回调循环缓冲区暂存读取指针和使用空间
** 参数:       [in]  round:           循环缓冲区
** 返回:       如读之前循环缓冲区中的使用字节数为0, 则返回-1;
**             否则, 返回读取到的字节
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
