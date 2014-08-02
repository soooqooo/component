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


#include "find_str.h"
#include "MN_384_IC.h"
#include "get_gps_date.h"
#include "add_msg_link.h"

NL_ROUNDBUF_T gpsround;
unsigned char s_gpsbuf[MSG_DEFAULT_LEN];

unsigned long read_count=0;
unsigned char debug_print_en=0;

//unsigned char en_send_flage=0;

g_GPS_DATA_BUF GPS_DATA_BUF;
void* thr_GET_GPS(void)
{
	pthread_detach( pthread_self() );
	Creat_GET_GPS();
	pthread_exit(0);
}
void Creat_GET_GPS(void)
{
	int flage;
	int fd;
	int cntr;
	int gps_date_len;
	unsigned char* buf;
	unsigned char buff[100];
	int leftlen;
	printf("Creat_GET_FILE \n");
	fd=open(file_get_fifo,O_RDONLY,0755);
	if(fd<0)
		printf("open file_get_fifo erro\n");
	NL_InitRoundBuf(&gpsround, s_gpsbuf, sizeof(s_gpsbuf));//lizhen
	NL_ResetRoundBuf(&gpsround);  // 清空缓存
	while(1)
	{
		//printf("11111111\n");
		while(SEND_MSG_DATA_LINK)//当发送链表是空的时候结束等待
			{
				//printf("SEND_MSG_DATA_LINK has date!\n");
			}
		leftlen = NL_LeftOfRoundBuf(&gpsround);
		buf = calloc(1,leftlen);
		printf("leftlen is :%d\n",leftlen);
		cntr=read(fd,buf,leftlen);
		printf("cntr=%d",cntr);
		if(cntr==0)
			{
				exit_flage=0;
				printf("read file_get_fifo over\n");
				return;
			}
		if(cntr<0)
				printf("read file_get_fifo erro");
		else{
				printf("cntr= %x\n",cntr);			
				debug_print_en=0;
				unsigned char *msg=NULL;
				msg=(unsigned char *)calloc(1,2048);
				NL_WriteBlockRoundBuf(&gpsround, buf, cntr);
				while((gps_date_len=Get_Find_STR_Data(msg,&gpsround, MSG_DEFAULT_LEN, "$GPGGA",NULL,1, "$GPRMC", "\n",1))>0)//ok
				{
					printf("get data is : %s\n",msg);
					printf("gps_date_len is : %x\n",gps_date_len);
					//sleep(10);
					PACK_SEND_MSG_LINK(msg,gps_date_len,GPS_DATA_TYPE);
					printf("PACK_SEND_MSG_LINK finsh!\n");
				}
				printf("find can_data over :\n");
				if(msg)
					free(msg);
			}		
		if(buf)
			free(buf);		
	}
}
