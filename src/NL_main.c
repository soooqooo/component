#include <pthread.h>		
#include <stdlib.h>   //exit函数需要这个库


#include "tcp_socket.h"
#include "analyze_rec.h"

int count_i;

int main(void)
{ 
	pthread_t cthd, dthd,Analyze_rec_thd;
	GET_SET_Parameter();
	timer_init();//心跳包定时及其他定时功能
	init_flage();
	count_i=0;
	/*开启udp tcp 短信包接收，创建s_tcpbuf环形buf，创建成功返回0
	"/home/TCP_Socket"                    管道文件*/
	int Creat_TCP_Socket_flage=pthread_create( &dthd, NULL, thr_Creat_TCP_Socket, NULL );
	//创建测试接收线程***后期调整为tcp接收线程//将其移到子线程程中判断是tcp，udp，还是短信
	pthread_create( &cthd, NULL, thr_TCP_Rcv, NULL );
	//创建测试发送线程***后期调整为tcp发送线程
	pthread_create( &dthd, NULL, thr_test_msg_write, NULL );
	//创建信息处理线程
	pthread_create( &Analyze_rec_thd, NULL, Analyze_rec_pro, NULL );
	#if 0
	//创建读取记录仪MCU接口进程消息线程
	//pthread_create( &dthd, NULL, thr_384_msg_read, NULL );
		//创建测试发送线程***后期调整为tcp发送线程
	//pthread_create( &dthd, NULL, thr_Creat_UDP_Socket, NULL );
	//创建发送记录仪MCU接口进程消息线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建读取记录仪进程消息线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建发送记录仪进程消息线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建读取CAN进程消息线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建发送CAN进程消息线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建读取屏显按键进程消息线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建发送屏显按键进程消息线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	
	//创建围栏计算线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建ftp线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建录音线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//创建录像拍照线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );、
	//创建盲区线程
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	#endif
	while(count_i<120);
	exit(1);
}



