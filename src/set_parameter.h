#ifndef __SET_PARAMETER_H__
#define __SET_PARAMETER_H__


#include "structural_body.h"
#include "defined.h"
#include "roundbuf.h"




void GET_SET_Parameter(void);
int Creat_Message_queue_for_SPI(void);
int FILE_Find(char * file_name,char *file_dir);

void Clear_File(char* dest);
void Save_Para(void);
void init_Parameter(void);
int Get_CheckSum(char* buf,unsigned int len);




#endif

