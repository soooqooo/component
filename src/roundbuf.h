#ifndef __ROUNDBUF_H__
#define __ROUNDBUF_H__
#pragma pack(1)

typedef struct {
    	unsigned int           	bufsize;             /* round buffer size */
    	unsigned int           	used;                /* used bytes */
    	unsigned char        	*bptr;               /* begin position */
    	unsigned char        	*eptr;               /* end position */
    	unsigned char          	*wptr;               /* write position */
    	unsigned char          	*rptr;               /* read position */
	unsigned char          	*rrptr;               /*  用于读取时暂时存储用读取指针 */
	unsigned int           	rused;                /* 用于读取时暂时存储用使用计数*/
} NL_ROUNDBUF_T;
#pragma pack() 



void NL_InitRoundBuf(NL_ROUNDBUF_T *round, unsigned char *mem, unsigned int memsize);
void NL_ResetRoundBuf(NL_ROUNDBUF_T *round);
unsigned char *NL_RoundBufStartPos(NL_ROUNDBUF_T *round);
int NL_WriteRoundBuf(NL_ROUNDBUF_T *round, unsigned char data);
int NL_ReadRoundBuf(NL_ROUNDBUF_T *round);
int NL_ReadRoundBufNoMVPtr(NL_ROUNDBUF_T *round);
unsigned int NL_LeftOfRoundBuf(NL_ROUNDBUF_T *round);
unsigned int NL_UsedOfRoundBuf(NL_ROUNDBUF_T *round);
int NL_WriteBlockRoundBuf(NL_ROUNDBUF_T *round, unsigned char *bptr, unsigned int blksize);

int NL_BackRoundBuf(NL_ROUNDBUF_T *round,int count);
void NL_SETReadRoundBuf(NL_ROUNDBUF_T *round);
void NL_RESETReadRoundBuf(NL_ROUNDBUF_T *round);

#endif

