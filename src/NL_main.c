#include <pthread.h>		
#include <stdlib.h>   //exit������Ҫ�����


#include "tcp_socket.h"
#include "analyze_rec.h"

int count_i;

int main(void)
{ 
	pthread_t cthd, dthd,Analyze_rec_thd;
	GET_SET_Parameter();
	timer_init();//��������ʱ��������ʱ����
	init_flage();
	count_i=0;
	/*����udp tcp ���Ű����գ�����s_tcpbuf����buf�������ɹ�����0
	"/home/TCP_Socket"                    �ܵ��ļ�*/
	int Creat_TCP_Socket_flage=pthread_create( &dthd, NULL, thr_Creat_TCP_Socket, NULL );
	//�������Խ����߳�***���ڵ���Ϊtcp�����߳�//�����Ƶ����̳߳����ж���tcp��udp�����Ƕ���
	pthread_create( &cthd, NULL, thr_TCP_Rcv, NULL );
	//�������Է����߳�***���ڵ���Ϊtcp�����߳�
	pthread_create( &dthd, NULL, thr_test_msg_write, NULL );
	//������Ϣ�����߳�
	pthread_create( &Analyze_rec_thd, NULL, Analyze_rec_pro, NULL );
	#if 0
	//������ȡ��¼��MCU�ӿڽ�����Ϣ�߳�
	//pthread_create( &dthd, NULL, thr_384_msg_read, NULL );
		//�������Է����߳�***���ڵ���Ϊtcp�����߳�
	//pthread_create( &dthd, NULL, thr_Creat_UDP_Socket, NULL );
	//�������ͼ�¼��MCU�ӿڽ�����Ϣ�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//������ȡ��¼�ǽ�����Ϣ�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//�������ͼ�¼�ǽ�����Ϣ�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//������ȡCAN������Ϣ�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//��������CAN������Ϣ�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//������ȡ���԰���������Ϣ�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//�����������԰���������Ϣ�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	
	//����Χ�������߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//����ftp�߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//����¼���߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	//����¼�������߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );��
	//����ä���߳�
	pthread_create( &dthd, NULL, thr_spi_msg_write, NULL );
	#endif
	while(count_i<120);
	exit(1);
}



