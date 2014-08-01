#ifndef _FIND_STR_H_
#define _FIND_STR_H_
#include "roundbuf.h"
unsigned short int Get_Find_STR_Data(unsigned char* msg,NL_ROUNDBUF_T *round, int maxlen, unsigned char *h_str,unsigned char *h_end,int include_h, unsigned char *t_str,unsigned char *t_end,int include_t );
#endif

