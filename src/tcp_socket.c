#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "tcp_socket.h"

#define MAX_REC_COUNT	3
#define cvt_end2(s) (((s<<8) & 0xFF00) | ((s>>8) & 0x00FF))
int recv;//>0ʱ���ҵ�7eͷ���ҵ�7eβ��0
send_data_msg list_buff_p2;
int ENable_ANALYZ_REC=0;
int TCP_Socket_key;  //�ܵ����
int TCP_Socket_qid;  //��Ϣ�жӾ��
int  Data_Rec_count;
int Registered_sended_flag=0;
int  Data_Send_count=0;
unsigned short int ser_num=0;

extern G_JT_T_808_2011_Parameter JT_T_808_2011_Parameter;
extern JT_T_808_2011_data_type_Link *Send_LinkList;//����J808�������ݵ�������

extern NL_ROUNDBUF_T tcpround;
unsigned char s_tcpbuf[MSG_DEFAULT_LEN];
extern JT_T_808_2011_data_type_Link *Rec_LinkList;//����J808�������ݵ�������


void init_flage()
{
	TCP_Socket_key=-1;
	TCP_Socket_qid=-1;
	Data_Rec_count=0;
	//Creat_Rec_LinkList();
}
/**************************************************************
��������:void* thr_Creat_TCP_Socket()
�������� :����TCP�ӿ��߳�
***************************************************************/
void* thr_Creat_TCP_Socket()
{
	pthread_detach( pthread_self() );
	Creat_TCP_Socket();
	pthread_exit(0);
}
/**************************************************************
��������:void Creat_TCP_Socket()
�������� :����TCP�ӿ�
***************************************************************/
void Creat_TCP_Socket()
{
	int flage;	
	printf("Connect_Mode %d \r\n",JT_T_808_2011_Parameter.Connect_Mode);
	NL_InitRoundBuf(&tcpround, s_tcpbuf, sizeof(s_tcpbuf));//lizhen
	NL_ResetRoundBuf(&tcpround);  // ��ջ���
	while(1)
	{
		if(JT_T_808_2011_Parameter.Connect_Mode==tcp_connect)
		{
			while((TCP_Socket_key<0))
			{
				TCP_Socket_key=open("/home/TCP_Socket",O_RDONLY,0);
				if(TCP_Socket_key < 0)
				{
					printf("TCP_Socket creat error\n");
				}
#if debug				
				else
				printf("ftok ok");
#endif				
			}			
		}
		return;
	}
}
/************************************************************
��������:void* thr_TCP_Rcv()
tcp���ݽ����߳�
***************************************************************/
void* thr_TCP_Rcv()
{
	pthread_detach( pthread_self() );
	TCP_Rcv_Data();
	pthread_exit(0);
}
/************************************************************
��������:void TCP_Rcv_Data()
tcp���ݽ����̺߳���
***************************************************************/

void TCP_Rcv_Data()
{
	int ret;
	unsigned char* buf;
	int  fd_in;
	int  nread;
	int num;
	int i;
	int leftlen;
#if debug	
	printf("TCP_Socket_key is :%d\n",TCP_Socket_key);	
#endif
	while(1)
	{
		if(TCP_Socket_key>0)
		{

			leftlen = NL_LeftOfRoundBuf(&tcpround);
			buf = calloc(1,leftlen);
			memset(buf,0,sizeof(buf));
#if debug			
			printf("TCP_Socket_key is :%d\n",TCP_Socket_key);
			printf("leftlen is :%d\n",leftlen);
#endif			
			if((nread=read(TCP_Socket_key,buf,leftlen))==-1)
			{
				if(errno==EAGAIN)
				printf("no data can be read!!\n");
			}
			if(nread>0)
			{
				unsigned char *msg=NULL;
				msg=(unsigned char *)calloc(1,2048);
				NL_WriteBlockRoundBuf(&tcpround,buf,nread);
				while((i=Get_Find_STR_Data(msg,&tcpround, MSG_DEFAULT_LEN, "~",NULL,1, "~", NULL,1))>4)//ok
				{
					Analyze_Translation(msg, i);
				}
				if(msg)
				free(msg);
		        
			}
		}
		if(buf)
			free(buf);
	}
}

/*******************************************************************
** ��������:   ��TCP��������ȡһ������
** ����:       [in]   round:          TCP������
**             [in]   maxlen :        �����յĳ���
**             [out]  buf:            ���ݽ���ָ��
** ����:       �������ݳ���
********************************************************************/
void Get_Tcp_Data(NL_ROUNDBUF_T *round, unsigned char *msg, int maxlen )
{
	int  rlen = 0;
	int i;
	printf("Get_Tcp_Data start \n");
    while((recv = NL_ReadRoundBuf(round)) != -1) 
    {
		if (rlen > 0) 
		{
            if (recv == 0x7e) 
            {  /* ֡β */
                msg[rlen++] = recv;;
				printf("rlen1 is :%d\r\n",rlen);
                if (rlen >= 14) 
                {
                	Analyze_Translation(msg,rlen);					
                	printf("rlen2 is :%d\r\n",rlen);
					rlen = 0;
			        break;
                }               
            } 
            else 
            {
                if (rlen >= maxlen) 
                {  /* ����������� */
                    printf("data out!");
                    rlen = 0; 
                } 
                else 
                {
                    msg[rlen++] = recv;
                }
            }
        } 
        else 
        {
            if (recv == 0x7e) 
            {  /* ֡ͷ */
                msg[rlen++] = recv;
            }
	    } 
	}
}
/**************************************************************
��������:void Analyze_Translation(unsigned char* msg,int len)
���� :msg  �����׵�ַ
		len  ���ݳ���
��������:ת��		
**************************************************************/

void Analyze_Translation(unsigned char* msg,int len)
{
	int len1,i;
	unsigned char* buf=NULL;
	printf("Analyze_Translation start \n");
	buf = calloc(1,len);
	printf("Analyze_Translation len %d \n",len);
	len1=0;
	for(i=0;i<len;i++)
	{
		if(msg[i]==0x7d)
		{
			i++;
			if(msg[i]==0x01)
			{
				buf[len1++]=0x7d;
			}
			if(msg[i]==0x02)
			{
				buf[len1++]=0x7e;
			}
		}
		else
		{
			buf[len1++]=msg[i];
		}
	}
	Check_JT_T_808_2011_Transmission_DATA(buf,len1);
	printf("Analyze_Translation end \n");
	free(buf);
	return;	
}
/**************************************************************
��������:int Check_JT_T_808_2011_Transmission_DATA(unsigned char* buf,int len)
���� :msg  �����׵�ַ
		len  ���ݳ���
��������:У������		
**************************************************************/

int Check_JT_T_808_2011_Transmission_DATA(unsigned char* buf,int len)
{
	int flage=0;
	int i;
	unsigned char check_sum=0;
#if debug	
	printf("Check_JT_T_808_2011_Transmission_DATA start \n");
	printf("revice data is : \n");
	for(i=0;i<len;i++)
	{	
		//check_sum=check_sum^buf[i];
		printf(" 0x%x",buf[i]);
	}
	printf("\n",buf[i]);
#endif
	for(i=1;i<(len-2);i++)
	{	
		check_sum=check_sum^buf[i];
	}
	if(check_sum==buf[len-2])
	{
#if debug	
		printf("checksum ok %x\n",check_sum);
#endif
		flage=1;
		Recv_Data_Send_Link(buf,len);
	}
#if debug	
	else
	{	
		printf("checksum erro\n");
		printf("checksum erro check_sum: %x\n",check_sum);
		printf("checksum erro buf[len-2] %x\n",buf[len-2]);		
	}	
	printf("Check_JT_T_808_2011_Transmission_DATA end \n");
#endif
	return flage;
}
/**************************************************************
��������:void Recv_Data_Send_Link(unsigned char* buf,int len)
���� :buf  �����׵�ַ
		len  ���ݳ���
��������:��Ҫ���͵�����д�뷢������
  �ɷְ����Ϊ����???????
**************************************************************/

void Recv_Data_Send_Link(unsigned char* buf,int len)
{
	JT_T_808_2011_data_type_Link *item = NULL, *tail = NULL, *first = NULL;
	JT_T_808_2011_data_PAck_type_def buff_1,buff_2;
	int i,j;
	int start_test=0;
	writetofile(buf,len,"rec_data_buf");
	/*�ж����ݳ����Ƿ��зְ�*/
	if((buf[3] & 0x20)==0x20)
	{
		item = (JT_T_808_2011_data_type_Link*)calloc(1, sizeof(JT_T_808_2011_data_type_Link));
	}
	else
	{
		item = (JT_T_808_2011_data_type_Link*)calloc(1, sizeof(JT_T_808_2011_data_type_Link));
		memset(&(item->msg_send_Method),0,sizeof(item->msg_send_Method));
		printf(" item=%x\n",i,item);
		j=len-sizeof(JT_T_808_2011_data_heah_type_def)-2;//j��ʵ����Ϣ��ĳ���
		printf("j= %d",j);
		//copy��Ϣͷ��item��
		memcpy((char*)&((*item).JT_T_808_2011_data.head1),buf,sizeof(JT_T_808_2011_data_heah_type_def));////////////////
		memset(&((*item).JT_T_808_2011_data.pack),0,sizeof(JT_T_808_2011_data_PAck_type_def));
		/*��С��ת��*/
		(*item).JT_T_808_2011_data.head1.ser_num=cvt_end2((*item).JT_T_808_2011_data.head1.ser_num);
		(*item).JT_T_808_2011_data.head1.attrib=cvt_end2((*item).JT_T_808_2011_data.head1.attrib);
		(*item).JT_T_808_2011_data.head1.ID=cvt_end2((*item).JT_T_808_2011_data.head1.ID);
		printf(" item->JT_T_808_2011_data.data_end.data_buf=%x\n",item->data_buf);
		item->data_buf=(unsigned char*)calloc(1,((*item).JT_T_808_2011_data.head1.attrib)+2);//�������ֽ�ΪУ��ͽ���λ
		printf(" calloc item->data_buf \n");
		i=(((*item).JT_T_808_2011_data.head1.attrib)&0x3ff)+2;
		printf("  item->data_buf len = %d \n",i);
		memcpy((*item).data_buf,
			buf+sizeof(JT_T_808_2011_data_heah_type_def),
			(((*item).JT_T_808_2011_data.head1.attrib)&0x3ff)+2);//-2);//////////////////�������ֽ�ΪУ��ͽ���λ
		printf(" memcpy item->data_buf \n");
		
		printf(" item->next=NULL \n");
	}
	#if 0	
	if (msg == NULL || len <= 0 || list == NULL || num == NULL)
	{
		ERR(APP_DBG, "NL_Recv_Put_Item: PARA\r\n");	
		return -1;
	}	
	#endif
	item->next=NULL;
	item->prev=NULL;
	ADD_LINK_NOTE(&Rec_LinkList,item,Insert_Link_P_next,Tatol_Link_tail,NULL,&Data_Rec_count);
	if(Data_Rec_count>MAX_REC_COUNT)
	{  /* �������������Ŀ��β������һ����ͷɾ��һ�� */
		printf(" first = Rec_LinkList \n");
		DEl_LINK_NOTE(&Rec_LinkList,1,NULL,&Data_Rec_count);
		printf(" Data_Rec_count   MAX=%d\n",Data_Rec_count);
		start_test=1;
	}
	//�ͷ��ź����������������߳�
	ENable_ANALYZ_REC=1;
	return ;
}

/****************************************************************************
��������:void* thr_test_msg_write()
��������:�߳�

*****************************************************************************/

void* thr_test_msg_write()
{
	pthread_detach( pthread_self() );
	//pthread_t cthd;
	//int stat = pthread_create( &cthd, NULL, thr_get, NULL );
	TCP_Send_Data();
	pthread_exit(0);
}
/****************************************************************************
��������:void TCP_Send_Data()

��������:��������

*****************************************************************************/

void TCP_Send_Data()
{
	int fd;
	int num;
	int i;
	if ( (mkfifo("/home/yanyc_tcpsend", O_EXCL|O_RDWR) < 0) && (errno != EEXIST))
	{
		perror("mkfifo");
	}
	fd = open("/home/yanyc_tcpsend", O_WRONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	while(1)
	{
		int i,j=0;
		if(TCP_Socket_key )
		{//Authentication_lizhen			
			if(Registered_sended_flag==0)//ע�ᷢ�ͱ�־λ
			{
				Registered_sended_flag=1;
				//���û�м�Ȩ ��ע��
				if((JT_T_808_2011_Parameter.Authentication_msg).Authentication_code[0]==0)
				{
					printf("********Register_lizhen_ed==0 **************");
					pack_Register_send_msg((unsigned short int)(Device_Report_GPRSRegistrationB),NULL,NULL);
					//���λ���ظ�����
					JT_T_808_2011_data_type_Link *ptr=Send_LinkList;//����������ptr
				}
				else//����Ȩ
				{
					pack_Register_send_msg((unsigned short int)(Device_Report_GPRSRegistrationA),NULL,NULL);
				}
			}			
			JT_T_808_2011_data_type_Link *ptr=Send_LinkList;
			int i=0,jjjcount=1;
			while(ptr!=NULL)
			{
//				printf("***********SEND_COUNT jjjcount=%d\n",jjjcount);
				if(ptr->msg_send_Method.send_flage==1)
				{
					send_data_msg *p2=List_buff(ptr);//�˴�Ӧ��˫���������׷�Ӻ�ɾ��?????
					if(ptr->JT_T_808_2011_data.head1.ID==Device_Jumper)
						DEl_LINK_NOTE(&Send_LinkList, jjjcount, NULL,&Data_Send_count);
					else
						ptr->msg_send_Method.send_flage=0;
					printf("TCP_Send_ data [%d] ",j);
					for (i=0;i<(p2->len);i++)
						printf("%x ",*(p2->msg)++);
					printf("\n");
					for (i=0;i<(p2->len);i++)
						*(p2->msg)--;
					if ((num=write(fd, p2->msg, p2->len)) < 0)
					{
						if(errno == EAGAIN)
						{
							printf("FIFO has not been read yet.\n");
						}
					}
				}
				jjjcount+=1;
				ptr=ptr->next;
			}
		}
	}
	unlink("/home/yanyc_tcpsend");
}
/****************************************************************************
��������:send_data_msg* List_buff(JT_T_808_2011_data_type_Link *ptr)
��������:��Ҫ���͵���������P2�� ��(����У��)
���� :     ptr ��������ָ��

*****************************************************************************/
send_data_msg* List_buff(JT_T_808_2011_data_type_Link *ptr)
{
	unsigned char p1[2048]={0};
	unsigned char*p=NULL;	
	int i;
	int len=0;
	unsigned char check_sum=0;
	JT_T_808_2011_data_heah_type_def *buf=NULL;
	memset(&list_buff_p2,0,sizeof(send_data_msg));
	buf=(JT_T_808_2011_data_heah_type_def*)calloc(1, sizeof(JT_T_808_2011_data_heah_type_def));
	memcpy((unsigned char*)buf,(unsigned char*)&(ptr->JT_T_808_2011_data.head1),sizeof(JT_T_808_2011_data_heah_type_def));
	ser_num++;
	buf->attrib=cvt_end2(buf->attrib);
	buf->ser_num=cvt_end2(ser_num);
	buf->ID=cvt_end2(buf->ID);
	ptr->JT_T_808_2011_data.head1.ser_num=ser_num;
	//printf("buf->ID %x\n",buf->ID);
	//printf("buf->ser_num ptr %x \n",buf->ser_num);
	//printf("buf->attrib %x\n",buf->attrib);
	if((ptr->JT_T_808_2011_data.pack.total_pack_num)!=0)
		len=len+sizeof(JT_T_808_2011_data_heah_type_def)+((*ptr).JT_T_808_2011_data.head1.attrib&0x3ff)+2+sizeof(JT_T_808_2011_data_PAck_type_def);
	else
		len=len+sizeof(JT_T_808_2011_data_heah_type_def)+((*ptr).JT_T_808_2011_data.head1.attrib&0x3ff)+2;//ԭ����1ff
	printf("send len = %d\n",len);
	list_buff_p2.msg=(unsigned char*)calloc(1, len);
	//�ɴ�С��ת�������Ϣͷ��msg
	memcpy(list_buff_p2.msg,(unsigned char*)buf,sizeof(JT_T_808_2011_data_heah_type_def));
	if((ptr->JT_T_808_2011_data.pack.total_pack_num)!=0)//����ְַ� ���ܰ��ְ�copy��msg
	{
		memcpy(list_buff_p2.msg+sizeof(JT_T_808_2011_data_heah_type_def),(unsigned char*)&((*ptr).JT_T_808_2011_data.pack),sizeof(JT_T_808_2011_data_PAck_type_def));
	}
	//����Ϣ��У��7eβ����msg
	memcpy(list_buff_p2.msg+sizeof(JT_T_808_2011_data_heah_type_def),(*ptr).data_buf,(((*ptr).JT_T_808_2011_data.head1.attrib)&0x3ff)+2);
	
	free(buf);
	//printf("ID ptr %x\n",ptr->JT_T_808_2011_data.head1.ID);
	//printf("ser_num ptr %x \n",ptr->JT_T_808_2011_data.head1.ser_num);
	//printf("attrib 123ptr %x\n",ptr->JT_T_808_2011_data.head1.attrib);
	list_buff_p2.msg++;
	for(i=0;i<(len-3);i++)
		check_sum=check_sum^(*(list_buff_p2.msg)++);
	*(list_buff_p2.msg)=check_sum;//��У��
	list_buff_p2.msg--;
	for(i=0;i<(len-3);i++)
		list_buff_p2.msg--;  //ָ�븴λ
	list_buff_p2.len=len;
	//printf("send data len [%d]\n",i,p2.len);
	//memcpy(p2.msg,p,len);
	//p2.msg=p;
	#if 0
	for (i=0;i<len;i++)
		printf("send data[%d]: %x\n",i,*(p2.msg)++);
	for (i=0;i<len;i++)
		*(p2.msg)--;
	#endif
	return &list_buff_p2;
}

/**********************************************************************************
��������:void pack_Register_send_msg(unsigned short int id,msg_buf_type* msgbuf,
	JT_T_808_2011_data_type_Link *prt)
��������:������Ϣ��
����  : id ��Ϣ��id
		msgbuf ��Ϣ��Ҫ�����׵�ַ
		prt �����ַ
***********************************************************************************/
void pack_Register_send_msg(unsigned short int id,msg_buf_type* msgbuf,
	JT_T_808_2011_data_type_Link *prt)
{
	JT_T_808_2011_data_type_Link* L_ptr=NULL,*tail=NULL;
	unsigned char tel[6]={0x01,0x34,0x86,0x58,0x67,0x31};
	unsigned char end_buff[2]={0x00,0x7e};
	int i=0;
	JT_T_808_2011_data_heah_type_def* code_ser=NULL;  //������Ϣͷ�ṹ��ָ��
#if db	
	printf("pack_jmp_send_msg star \n");
#endif
	L_ptr=(JT_T_808_2011_data_type_Link*)calloc(1, sizeof(JT_T_808_2011_data_type_Link));
	L_ptr->msg_send_Method.Resend_count=max_resend_count;//�趨�ش�����
	L_ptr->msg_send_Method.Resend_Timer=max_anw_timer;//�趨�ش�ʱ��
	L_ptr->msg_send_Method.send_flage=1;				//���巢�ͱ�־λ
	switch(id)
	{
		case Device_Report_GPRSRegistrationB://ע��			
			L_ptr->JT_T_808_2011_data.head1.head=0x7e;			
			L_ptr->JT_T_808_2011_data.head1.ID=(Device_Report_GPRSRegistrationB);			
			L_ptr->JT_T_808_2011_data.head1.ser_num=0;//(ser_num);
			memcpy(&(L_ptr->JT_T_808_2011_data.head1.tel_num),tel,6);
#if db			
			printf("pack_jmp_send_msg Device_Report_GPRSRegistrationB \n");
			printf("head L_ptr %x\n",L_ptr->JT_T_808_2011_data.head1.head);
			printf("ID L_ptr %x\n",L_ptr->JT_T_808_2011_data.head1.ID);
			printf("ser_num L_ptr %x \n",L_ptr->JT_T_808_2011_data.head1.ser_num);
			printf("attrib L_ptr %x\n",L_ptr->JT_T_808_2011_data.head1.attrib);
			printf("tel_num L_ptr %s\n" ,L_ptr->JT_T_808_2011_data.head1.tel_num);
#endif			
			L_ptr->JT_T_808_2011_data.pack.total_pack_num=0;
			L_ptr->JT_T_808_2011_data.pack.pack_num=0;
			i=strlen(JT_T_808_2011_Parameter.Register_msg.License_plate);//���㳵�Ƴ���
			L_ptr->JT_T_808_2011_data.head1.attrib=i+25;
			L_ptr->data_buf=(unsigned char*)calloc(1,((*L_ptr).JT_T_808_2011_data.head1.attrib)+2);//�������ֽ�ΪУ��ͽ���λ
			memcpy(L_ptr->data_buf,(unsigned char *)&(JT_T_808_2011_Parameter.Register_msg),25);		
			memcpy((L_ptr->data_buf)+25,(unsigned char *)&(JT_T_808_2011_Parameter.Register_msg.License_plate),i);
			memcpy((L_ptr->data_buf)+(L_ptr->JT_T_808_2011_data.head1.attrib),end_buff,2);//У��δ����ֵ
			//��������ע����Ҫ������ȫ������l_ptr���������
			break;
		case Device_Report_GPRSRegistrationA:
	#if db		
			printf("pack_jmp_send_msg Device_Report_GPRSRegistrationA \n");
	#endif
			L_ptr->JT_T_808_2011_data.head1.head=0x7e;
			L_ptr->JT_T_808_2011_data.head1.ID=(Device_Report_GPRSRegistrationA);
			L_ptr->JT_T_808_2011_data.head1.ser_num=0;//(ser_num);
			memcpy(&(L_ptr->JT_T_808_2011_data.head1.tel_num),tel,6);
			L_ptr->JT_T_808_2011_data.pack.total_pack_num=0;
			L_ptr->JT_T_808_2011_data.pack.pack_num=0;
			i=strlen(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code);//�����Ȩ�볤��
			L_ptr->JT_T_808_2011_data.head1.attrib=i;
			L_ptr->data_buf=(unsigned char*)calloc(1,((*L_ptr).JT_T_808_2011_data.head1.attrib)+2);//�������ֽ�ΪУ��ͽ���λ
			memcpy(L_ptr->data_buf,(unsigned char *)&(JT_T_808_2011_Parameter.Authentication_msg),i);			
			memcpy((L_ptr->data_buf)+(L_ptr->JT_T_808_2011_data.head1.attrib),end_buff,2);
			break;
		case Device_Jumper :
			L_ptr->msg_send_Method.Resend_count=0;//�趨�ش�����
			L_ptr->msg_send_Method.Resend_Timer=0;//�趨�ش�����
			L_ptr->msg_send_Method.send_flage=1;
			L_ptr->JT_T_808_2011_data.head1.head=0x7e;
			L_ptr->JT_T_808_2011_data.head1.ID=(Device_Jumper);
			L_ptr->JT_T_808_2011_data.head1.ser_num=0;//(ser_num);
			L_ptr->JT_T_808_2011_data.head1.attrib=(0);
			memcpy(&(L_ptr->JT_T_808_2011_data.head1.tel_num),tel,6);
#if db			
			printf("pack_jmp_send_msg Device_Report_GPRSRegistrationB \n");
			printf("head L_ptr %x\n",L_ptr->JT_T_808_2011_data.head1.head);
			printf("ID L_ptr %x\n",L_ptr->JT_T_808_2011_data.head1.ID);
			printf("ser_num L_ptr %x \n",L_ptr->JT_T_808_2011_data.head1.ser_num);
			printf("attrib L_ptr %x\n",L_ptr->JT_T_808_2011_data.head1.attrib);
			printf("tel_num L_ptr %s\n" ,L_ptr->JT_T_808_2011_data.head1.tel_num);
#endif	
			L_ptr->data_buf=(unsigned char*)calloc(1,((*L_ptr).JT_T_808_2011_data.head1.attrib)+2);//�������ֽ�ΪУ��ͽ���λ
			memcpy(L_ptr->data_buf,end_buff,2);
			printf("data_buf L_ptr\n");
			L_ptr->next=NULL;
			break;
		#if 0
		case Device_Report_GPRSRegistrationA:
			break;
		#endif
	}
	L_ptr->next=NULL;
	ADD_LINK_NOTE(&Send_LinkList,L_ptr,Insert_Link_P_next,Tatol_Link_tail,NULL,&Data_Send_count);
	if(Data_Send_count>MAX_Send_COUNT)
	{  /* �������������Ŀ��β������һ����ͷɾ��һ�� */
		printf(" pack_Register_send_msg first = Rec_LinkList \n");
		if(Send_LinkList==NULL)
			printf(" pack_Register_send_msg first = NULL \n");
		i=DEl_LINK_NOTE(&Send_LinkList,1,NULL,&Data_Send_count);
	}
	printf(" pack_Register_send_msg first = end \n");
}

