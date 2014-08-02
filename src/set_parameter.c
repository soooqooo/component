#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>



#include"set_parameter.h"
 



#define HVT_SET_FILE_NAME "/home/hvt_SET_FILE.cfg"  //�����ļ�
NL_ROUNDBUF_T tcpround;
extern unsigned char s_tcpbuf[MSG_DEFAULT_LEN];

G_JT_T_808_2011_Parameter JT_T_808_2011_Parameter;


/**********************************************************************************
��������: GET_SET_Parameter
����˵��:��ȡ���ò�����JT_T_808_2011_Parameter�У����д��ʧ�ܣ�
				����Save_Para()����
			
***********************************************************************************/
void GET_SET_Parameter(void)
{
	int fd;
	int len,size;
	memset(&JT_T_808_2011_Parameter, 0, sizeof(G_JT_T_808_2011_Parameter));
	fd=open(HVT_SET_FILE_NAME,O_RDONLY|O_EXCL,0755);
	size=sizeof(G_JT_T_808_2011_Parameter);
#if db	
	printf("G_JT_T_808_2011_Parameter is %d \r\n",size);
#endif
	if(fd<0)
	{
		printf("aopen %s erro\r\n",HVT_SET_FILE_NAME);
	}
	if((size=read(fd,(char * )&JT_T_808_2011_Parameter,sizeof(G_JT_T_808_2011_Parameter)))<0)
	{//��ȡʧ������¼���ʼ������
		printf("read %s erro\r\n",HVT_SET_FILE_NAME);
		goto erro;
	}
	else
	{
#if debug
		printf("size wang %d \r\n",size);
		printf("Check_Sum %d \r\n",JT_T_808_2011_Parameter.Check_Sum);
		printf("Province_ID %d \r\n",JT_T_808_2011_Parameter.Register_msg.Province_ID);
		printf("Sleep_Report_Distance %d \r\n",JT_T_808_2011_Parameter.Sleep_Report_Distance);
#endif
		if(JT_T_808_2011_Parameter.Check_Sum!=(len=Get_CheckSum((char *)&JT_T_808_2011_Parameter,sizeof(G_JT_T_808_2011_Parameter)-sizeof(JT_T_808_2011_Parameter.Check_Sum))))
		{
#if debug		
			printf("len %d \r\n",len);
			printf("check %s erro\r\n",HVT_SET_FILE_NAME);
#endif			
			goto erro;
		}
	}
	if(fd)
		close(fd);
	return;
erro:	
	if(fd)
		close(fd);
#if debug	
	printf("1close(fd);\r\n");
#endif
	Save_Para();
	return;
}
/*******************************************************************************
��������:void Clear_File(char* dest)
����˵��  :����ļ�dest
����: dest   �ļ����ַ������׵�ַ

********************************************************************************/

void Clear_File(char* dest)
{
	printf("Clear_File star\r\n");
	char p[100]="cat /dev/null > ";
	strcat(p,dest);//����2���ַ���
	printf("Clear_File command %s\r\n",p);
	system(p);	
	//cat /dev/null > /etc/test.txt ��Ϊ���/etc/test.txt��������
	printf("Clear_File end\r\n");
	return;
}
/**********************************************************************************
��������:void Save_Para(void)
����˵��  :�����ʼ������
***********************************************************************************/
void Save_Para(void)
{
	int fd;
	int wf;
	char *buf=NULL;
	init_Parameter();
	JT_T_808_2011_Parameter.Check_Sum=Get_CheckSum((char * )&JT_T_808_2011_Parameter, sizeof(G_JT_T_808_2011_Parameter)-sizeof(JT_T_808_2011_Parameter.Check_Sum));
	printf("Check_Sum %d \r\n",JT_T_808_2011_Parameter.Check_Sum);
	Clear_File(HVT_SET_FILE_NAME);
	fd=open(HVT_SET_FILE_NAME,O_WRONLY|O_EXCL,0755);
	if(fd<0)
	{
		printf("1open %s erro\r\n",HVT_SET_FILE_NAME);
	}
	wf=write(fd,(char*)&JT_T_808_2011_Parameter,sizeof(G_JT_T_808_2011_Parameter));
	if(wf<0)
	{
		printf("write %s erro\r\n",HVT_SET_FILE_NAME);
	}
	free(buf);
	close(fd);
	return;
}
void init_Parameter(void)
{
	printf("init_Parameter star\r\n");
	memset(&JT_T_808_2011_Parameter, 0, sizeof(G_JT_T_808_2011_Parameter));
	JT_T_808_2011_Parameter.Register_msg.Province_ID=83;							//ʡ��ID
	JT_T_808_2011_Parameter.Register_msg.City_ID=20;								//����ID
	strcpy(JT_T_808_2011_Parameter.Register_msg.Manufacturers_ID,"12345");			//������ID
	strcpy(JT_T_808_2011_Parameter.Register_msg.Device_model,"hvt100");			//�豸�ͺ�
	strcpy(JT_T_808_2011_Parameter.Register_msg.Device_ID,"hvt100");				//�豸ID
	JT_T_808_2011_Parameter.Register_msg.Color_plates=1;						//������ɫ
	strcpy(JT_T_808_2011_Parameter.Register_msg.License_plate,"��Bd1234");		//���ƺ���
	memset(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code,0,sizeof(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code));
	//strcpy(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code,"1234554321");//������int

	JT_T_808_2011_Parameter.Connect_Mode=0;						//����ģʽ0-tcp 1-udp 2-sms(���Ű�)
	
	JT_T_808_2011_Parameter.Jumper_Timer=10;						//�ն��������ͼ��
	JT_T_808_2011_Parameter.TCP_Anwer_OverTime=60;				//tcp��ϢӦ��ʱ
	JT_T_808_2011_Parameter.TCP_Resend_Count=10;					//tcp��Ϣ�ش�����
	JT_T_808_2011_Parameter.UDP_Anwer_OverTime=60;				//UDP��ϢӦ��ʱ
	JT_T_808_2011_Parameter.UDP_Resend_Count=10;					//UDP��Ϣ�ش�����
	JT_T_808_2011_Parameter.SMS_Anwer_OverTime=60;				//SMS��ϢӦ��ʱ
	JT_T_808_2011_Parameter.SMS_Resend_Count=10;					//SMS��Ϣ�ش�����
	strcpy(JT_T_808_2011_Parameter.Master_Server_APN,"1234");		//�����ķ�����APN������ͨ�Ų��ŷ��ʵ�/CDMA->PPP���ź���
	//Master_Server_PassWord
	strcpy(JT_T_808_2011_Parameter.Master_Server_UserName,"lizhen");		//������������ͨѶ�����û���
	strcpy(JT_T_808_2011_Parameter.Master_Server_PassWord,"2345");		//������������ͨ�Ų�������
	strcpy(JT_T_808_2011_Parameter.Master_Server_IP,"117.135.136.130");		//����������ַ��ip������
	
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_APN,"1234");		//���ݷ�����APN������ͨ�Ų��ŷ��ʵ�/CDMA->PPP���ź���
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_UserName,"lizhen");	//������������ͨѶ�����û���
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_PassWord,"5678");		//������������ͨ�Ų�������
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_IP,"117.135.136.130");		//����������ַ��ip������
	JT_T_808_2011_Parameter.TCP_Port=8080;							//������TCP�˿�
	JT_T_808_2011_Parameter.UDP_Port=6060;							//������UDP�˿�
	JT_T_808_2011_Parameter.Position_Report_Tactics=0;				//λ�û㱨���� 0-��ʱ�㱨��1����㱨��2��ʱ�Ͷ���㱨
	JT_T_808_2011_Parameter.Position_Report_Plan=0;				//λ�û㱨���� 0-����ACC״̬��1-���ݵ�¼״̬��ACC״̬
	JT_T_808_2011_Parameter.Aeronaut_UnLogin_Report_Timer=20;		//��ʻԱδ��¼�㱨ʱ����
	JT_T_808_2011_Parameter.Sleep_Report_Timer=120;					//����ʱ��㱨ʱ����
	JT_T_808_2011_Parameter.Emergency_Alarm_Report_Timer=5;		//��������ʱ�㱨ʱ����
	JT_T_808_2011_Parameter.Default_Report_Distance=500;				//ȱʡ����㱨���
	JT_T_808_2011_Parameter.Default_Report_Timer=10;				//ȱʡʱ��㱨���
	JT_T_808_2011_Parameter.Aeronaut_UnLogin_Report_Distance=100;	//��ʻԱδ��¼�㱨ʱ����
	JT_T_808_2011_Parameter.Sleep_Report_Distance=50;				//����ʱ��㱨������
	#if 0
	SET_Parameter.Emergency_Alarm_Report_Distance=100;	//��������ʱ�㱨������
	unsigned long Round_Supplemental_transmission_Angl=15;//�յ㲹���Ƕ�
	unsigned char Server_TELNum[15];					//���ƽ̨�绰����
	unsigned char Reset_Terminal_TelNum[15];			//�ն˸�λ�绰����
	unsigned char Default_Para_TelNum[15];			//�ָ��������õ绰����
	unsigned char Server_SMS_TelNum[15];				//���ƽ̨SMS�绰����
	unsigned char Receiver_SMS_Alarm_Report_TelNum;//�����ն�SMS�ı���������
	unsigned long Tel_Answer_Tactics;					//�绰�������� 0-�Զ�������1-ACC ONʱ�Զ�����OFFʱ�ֶ�����
	unsigned long Max_Tel_Answer_Timer_Once;		//ÿ��ͨ���ʱ��0-���������ֵΪ������
	unsigned long Max_Tel_Answer_Timer_Month;		//ÿ���ͨ��ʱ��0-���������ֵΪ������
	unsigned char Listen_TelNum[15];					//�����绰����
	unsigned char	VIP_SMS_TelNum[15];				//���ƽ̨��Ȩ���ź���
	unsigned long Disable_Alarm_Flage;				//����������
	unsigned long Send_Alarm_SMS_Flage;				//��������SMS�ı�����
	unsigned long Alarm_Photograph_Flage;			//�������㿪��1Ϊ����
	unsigned long Alarm_Photograph_Save_Flage;		//��������洢��־λ1Ϊ�洢�����ϴ�
	unsigned long Crucial_Flage;						//�ؼ���־����λ����Ϣ�㱨�б�����־���Ӧ��1���Ӧ����Ϊ�ؼ�����
	unsigned long Max_Speed;							//����ٶ�
	unsigned long Over_Speed_Continu_time;			//���ٳ���ʱ��
	unsigned long Max_Continu_Drivering_Time;				//������ʻʱ������
	unsigned long Continu_Drivering_Time_Day;			//�����ۼƼ�ʻʱ��
	unsigned long Min_Rest_Time;						//��С��Ϣʱ��
	unsigned long Max_Stop_Time;						//�ͣ��ʱ��
	unsigned long Image_Quality_Mode;				//ͼ����Ƶ����1~10��1���
	unsigned long Brightness_Para;						//����0~255
	unsigned long Contrast_Para;						//�Աȶ�0~127
	unsigned long Saturation_Para;						//���Ͷ�0~127
	unsigned long Chroma_Para;						//ɫ��0~255
	unsigned long Odometer_Numerical;				//��̱���ֵ1/10km
	#endif
	printf("init_Parameter end\r\n");
	return;
}

int Get_CheckSum(char* buf,unsigned int len)
{
	int check_sum=0;
	unsigned int i;
	printf("Get_CheckSum star\r\n");
	for(i=0;i<len;i++)
	{
		check_sum=check_sum^buf[i];
	}
	printf("Get_CheckSum end\r\n");
	return check_sum;
}


