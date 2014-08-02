#ifndef __STRUCTURAL_BODY_H__
#define __STRUCTURAL_BODY_H__


#pragma pack(1) 
typedef struct Register_msg_def
{
	unsigned short int 	Province_ID;					//ʡ��ID
	unsigned short int 	City_ID;						//����ID
	unsigned char Manufacturers_ID[5];					//������ID
	unsigned char Device_model[8];						//�豸�ͺ�
	unsigned char Device_ID[7];							//�豸ID
	unsigned char Color_plates;							//������ɫ
	unsigned char License_plate[10];					//���ƺ���
}g_Register_msg;
 
typedef struct Authentication_msg_def
{
	char Authentication_code[20];						//��Ȩ��
}g_Authentication_msg;

#define tcp_connect 0
#define udp_connect 1
#define sms_connect 2
typedef struct 
{
	struct Register_msg_def Register_msg;
	struct Authentication_msg_def Authentication_msg;
	
	unsigned char Connect_Mode;						//����ģʽ0-tcp 1-udp 2-sms(���Ű�)
	
	unsigned long Jumper_Timer;						//�ն��������ͼ��
	unsigned long TCP_Anwer_OverTime;				//tcp��ϢӦ��ʱ
	unsigned long TCP_Resend_Count;					//tcp��Ϣ�ش�����
	unsigned long UDP_Anwer_OverTime;				//UDP��ϢӦ��ʱ
	unsigned long UDP_Resend_Count;					//UDP��Ϣ�ش�����
	unsigned long SMS_Anwer_OverTime;				//SMS��ϢӦ��ʱ
	unsigned long SMS_Resend_Count;					//SMS��Ϣ�ش�����
	char			Master_Server_APN[20];				//�����ķ�����APN������ͨ�Ų��ŷ��ʵ�/CDMA->PPP���ź���
	char			Master_Server_UserName[10];		//������������ͨѶ�����û���
	char			Master_Server_PassWord[10];		//������������ͨ�Ų�������
	char			Master_Server_IP[20];				//����������ַ��ip������
	char			Reserve_Server_APN[20];			//���ݷ�����APN������ͨ�Ų��ŷ��ʵ�/CDMA->PPP���ź���
	char			Reserve_Server_UserName[10];		//������������ͨѶ�����û���
	char			Reserve_Server_PassWord[10];		//������������ͨ�Ų�������
	char			Reserve_Server_IP[20];				//����������ַ��ip������
	unsigned int	TCP_Port;							//������TCP�˿�
	unsigned int	UDP_Port;							//������UDP�˿�
	unsigned long Position_Report_Tactics;				//λ�û㱨���� 0-��ʱ�㱨��1����㱨��2��ʱ�Ͷ���㱨
	unsigned long Position_Report_Plan;				//λ�û㱨���� 0-����ACC״̬��1-���ݵ�¼״̬��ACC״̬
	unsigned long Aeronaut_UnLogin_Report_Timer;		//��ʻԱδ��¼�㱨ʱ����
	unsigned long Sleep_Report_Timer;					//����ʱ��㱨ʱ����
	unsigned long Emergency_Alarm_Report_Timer;		//��������ʱ�㱨ʱ����
	unsigned long Default_Report_Distance;				//ȱʡ����㱨���
	unsigned long Default_Report_Timer;				//ȱʡʱ��㱨���
	unsigned long Aeronaut_UnLogin_Report_Distance;	//��ʻԱδ��¼�㱨ʱ����
	unsigned long Sleep_Report_Distance;				//����ʱ��㱨������
	unsigned long Emergency_Alarm_Report_Distance;	//��������ʱ�㱨������
	unsigned long Round_Supplemental_transmission_Angl;//�յ㲹���Ƕ�
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
	

	int Check_Sum;
	
}G_JT_T_808_2011_Parameter;

typedef struct g_msg_send_Method
{
	unsigned char send_flage;			//���ͱ�־λ
	unsigned short int Resend_count;	//�ش�����
	unsigned  long Resend_Timer;		//�ش�ʱ��

}msg_send_Method_type;

typedef struct heah_type			//��Ϣͷ
{
	unsigned char head;
	unsigned short int ID;
	unsigned short int attrib;
	unsigned char tel_num[6];
	unsigned short int ser_num;
}JT_T_808_2011_data_heah_type_def;

typedef struct Pack_Type			//�ְ��ṹ��
{
	unsigned short int total_pack_num;
	unsigned short int pack_num;
}JT_T_808_2011_data_PAck_type_def;

typedef struct data_end_def		//Ҫ���͵�����  ????
{
	unsigned char  data_buf[1024];
	unsigned char check;
	char end;
}def_end_data;

typedef struct Def_Type        //
{
	 struct heah_type head1;
	 struct Pack_Type pack;

}JT_T_808_2011_data_type_def;



typedef struct g_msg_buf
{
	unsigned short int len;  //���ݳ���
	unsigned char * buf;     //�����׵�ַ
}msg_buf_type;

typedef struct Send_data
{
	int len;
	unsigned char *msg;
}send_data_msg;

#pragma pack()

#endif

