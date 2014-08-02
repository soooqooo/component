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

#include "get_gps_date.h"
#include "send_gps_date.h"
#include "MN_384_IC.h"

//#include "get_can.h"
//#include "send_can.h"
#if 0
./mn_384_IC > logfile.log 2>&1

#endif
unsigned short int Ser_Num=0;
unsigned char exit_flage=1;

int main(void)
{
	pthread_t GPS_GET, GPS_SEND;
	printf("main start\n");
	timer_init();//心跳包定时及其他定时功能
	pthread_create( &GPS_GET, NULL, (void*)thr_GET_GPS, NULL );
	pthread_create( &GPS_SEND, NULL, (void*)thr_SEND_GPS, NULL );
	while(exit_flage);
}
