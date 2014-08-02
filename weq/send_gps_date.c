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

//#include <sys/stat.h>

#include "add_msg_link.h"
#include "Tlinked_list.h"
#include "get_gps_date.h"
#include "send_gps_date.h"
#include "timer.h"
#include "Ttime.h"
unsigned int count_i_old=0;
int IC384_send_fd;
 

void* thr_SEND_GPS(void)
{
	pthread_detach( pthread_self() );
	Send_Gps_Data();
	pthread_exit(0);
}
void Send_Gps_Data(void)
{
	int fd;
	int cntw;
	int i;
	printf("wangbaowen\n");
	if ( (mkfifo("/home/gps_send", O_EXCL|O_RDWR) < 0) && (errno != EEXIST))
		{
		perror("mkfifo");
		printf("wangbaowen1\n");
		}
	printf("wangbaowen111\n");
	fd = open("/home/gps_send", O_WRONLY);
	printf("wangbaowen222\n");
	if (fd < 0)
		{
		perror("open");
		printf("wangbaowen2\n");
		exit(1);
		}
	printf("wangbaowen333\n");
	printf("send GPS DATE \n");
	//sleep(10);
	while(1)
		{
		printf("send GPS DATE while(1)\n");
		if(SEND_MSG_DATA_LINK )//&& (count_i_old != count_i) )
			{
			g_Compiled_Send_MSG_type *send_msg=NULL;
			
			send_msg = (g_Compiled_Send_MSG_type*)calloc(1, sizeof(g_Compiled_Send_MSG_type));
			send_msg->msg = (unsigned char*)calloc(1,2048);
			
			Compiled_Send_MSG(SEND_MSG_DATA_LINK , send_msg);//把要发送的数据按照808进行转义
			i=0;
#if 0 			
			while(i<send_msg->len)
				{
				printf("send_msg[%d] = %x  \n",i,*(send_msg->msg)++);
				i++;
				}
			i=0;
			while(i<send_msg->len)
				{
				*(send_msg->msg)--;
				i++;
				}
#endif			
			cntw=write(fd,send_msg->msg,send_msg->len);
			printf("write SEND_FILE timer  %s ;\n",get_current_time());
			if(cntw<0)
				printf("write SEND_FILE erro \n");
			else if(cntw == send_msg->len)
				printf("write SEND_FILE total data \n");
			
			DEl_LINK_NOTE(&SEND_MSG_DATA_LINK,1,NULL,&SEND_MSG_LINK_count);
			count_i_old = count_i;
			
			if(send_msg->msg)
				free(send_msg->msg);
			if(send_msg)
				free(send_msg);
			}
		}
}
