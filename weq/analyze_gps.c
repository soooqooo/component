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

#include "analyze_gps.h"
#include "Tchange_data.h"
//#include "send_can.h"
#include "add_msg_link.h"
void analyze_gps_data(unsigned char *msg,unsigned short int len)
{
	unsigned short int i;
	unsigned char j=0;
	can_data_def_type *item=NULL;
	unsigned char *buff=NULL;
	item= (can_data_def_type*)calloc(1, sizeof(can_data_def_type));
	item->id_can=char_TO_long(msg, 8, 4);
	i=8;
	item->can_date_len=char_TO_char(msg+i, 2, 4);
	item->data_can= (unsigned char*)calloc(1, item->can_date_len);
	printf("item->id_can = %x \n",item->id_can);
	printf("item->can_date_len = %x \n",item->can_date_len);
	//printf("item->id_can = %x \n",item->id_can);
	i=10;
	while(i<len)
		{
		item->data_can[j]=char_TO_char(msg+i, 2, 4);
		i+=2;
		printf("item->data_can[%d] = %x \n",j,item->data_can[j]);
		j++;
		}
	i=0;
	j=0;
	buff= (unsigned char *)calloc(1, sizeof(can_data_def_type));
	while(i<len)
		{
		buff[j]=char_TO_char(msg+i, 2, 4);
		printf("wang buff[%d] = %x \n",j,buff[j]);
		i+=2;
		j++;	
		}	
		PACK_SEND_MSG_LINK(buff,j,2);
		if(buff)
		free(buff);
	if(item)
		free(item);
}
