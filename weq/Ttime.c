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
#include "Ttime.h"

char *get_current_time(void)  
{  
    //Р§зг   
    static char timestr[40];  
    time_t t;  
    struct tm *nowtime;  
      
   	time(&t);  
    nowtime = localtime(&t);  
    strftime(timestr,sizeof(timestr),"%Y-%m-%d %H:%M:%S",nowtime);  
      printf("local time is %s\n",asctime(nowtime));
    return timestr;  
} 

