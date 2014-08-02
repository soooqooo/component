#ifndef __DEFINED_H__
#define __DEFINED_H__


#define debug	1
#define db 1

#define MSG_DEFAULT_LEN 4096


#define Center_Report_Universal				0x8001		//ƽ̨ͨ��Ӧ��8.2
#define Center_Confirm_GPRSRegistrationB	0x8100		//ע��Ӧ��8.5
#define Center_Set_Device_Parameters		0x8103		//��������//lizhen
#define Center_Inquire_Device_Parameters	0x8104		//������ѯ
#define Center_Control_Device				0x8105		//�ն˿���8.11
#define Center_Require_PositionInfoA		0x8201		//λ����Ϣ��ѯ8.13
#define Center_Require_temporary_Tail		0x8202		//��ʱ����λ����Ϣ��ѯ8.15
#define Center_Send_Text					0x8300		//���ֶ���8.16
#define Center_Send_Event_SET				0x8301		//�¼�����8.17
#define Center_Send_quiz					0x8302		//�����·�8.19
#define Center_Send_INFO_MENU_SET			0x8303		// ��Ϣ�㲥�˵����� 8.21
#define Center_Send_Message_server			0x8304		//��Ϣ���� 8.23
#define Center_Send_Phone_REcall			0x8400		//�绰�ز� 8.24
#define Center_Phone_Book_SET				0x8401		//���õ绰��8.25
#define Center_Car_Control					0x8500		//��������8.26
#define Center_Circular_Region_SET			0x8600		//����Բ������8.28
#define Center_Circular_Region_Del			0x8601		//ɾ��Բ������8.29
#define Center_Rect_Region_SET				0x8602		//���þ�������8.30
#define Center_Rect_Region_Del				0x8603		//ɾ����������8.31
#define Center_Poly_Region_SET				0x8604		//���ö��������8.32
#define Center_Poly_Region_Del				0x8605		//ɾ�����������8.33
#define Center_Lines_SET					0x8606		//��·���� 8.34
#define Center_Lines_Del					0x8607		//������·8.35
#define Center_SEND_Over_rate				0x8608		//���ٱ���������Ϣ8.36
#define Center_SEND_IO_ARE_LINE				0x8609		//��������/·�߱���������Ϣ8.37
#define Center_SEND_Driv_TIME				0x8610		//·����ʻʱ�䲻��/��������8.38
#define Center_SEND_Driv_Rec_GET			0x8700		//��ʻ��¼�����ݲɼ�����8.39
#define Center_SEND_Driv_Rec_parameter		0x8701		//��ʻ��¼�����´�����8.41
#define Center_Report_media					0x8800		//��ý�������ϴ�Ӧ��8.46
#define Center_Send_CAMMER_COMMAND			0x8801		//����ͷ������������8.47
#define Center_Send_media_SAVE_DATA_SERCH_command		0x8802		//�洢��ý�����ݼ���8.48
#define Center_Send_media_command			0x8803		//�洢��ý�������ϴ�����8.50
#define Center_Send_Vol_REC_START			0x8804		//¼����ʼ����8.51
#define Center_Send_media_oneSearch			0x8805		//�����洢��ý�����ݼ����ϴ�����
#define Cenrer_Send_DownData_Trans			0x8900		//��������͸��8.52	
#define Center_Send_SRA_KEY					0x8A00		//ƽ̨RSA����8.55
#define Center_Inquire_Device_Parameters1	0x8FF1		//�����ѯ�ն˲��� 
#define Center_Logins_record				0x8FF2		//��¼��¼��ѯ 
#define Center_Speeding_record				0x8FF3		//���ټ�¼��ѯ
#define Center_Switch_record				0x8FF4		//�������仯��¼��ѯ 
#define Center_Urgent_acceleration_record	0x8FF5		//�����ټ�¼��ѯ 
#define Center_five_sec_record				0x8FF6		//1���Ӽ���ʷ���ݲ�ѯ  
#define Center_one_min_record				0x8FF7		//1���Ӽ���ʷ���ݲ�ѯ 
#define Center_five_min_record				0x8FF8		//5���Ӽ���ʷ���ݲ�ѯ 
#define Center_History_Data_Inquire			0x8F12		//��ʷ���ݲ�ѯ
#define Center_History_Data_Reply			0x8F13		//��ʷ���ݲ�ѯӦ��

#define Device_Report_Universal				0x0001//�ն�ͨ��Ӧ��8.1
#define Device_Jumper						0x0002//����8.3
#define Device_UnRegistration				0x0003//�ն�ע��8.6
#define Device_Report_GPRSRegistrationB		0x0100//�ն�ע��8.4
#define Device_Report_GPRSRegistrationA		0x0102//�ն˼�Ȩ8.7
#define Device_Report_parameter				0x0104//��ѯ�ն˲���Ӧ��8.10
#define Device_Report_PositionInfo2			0x0200		//�����ϱ�//lizhen
#define Device_Report_PositionInfo3			0x0201		//��̨��ѯ�ش�//lizhen
#define Device_Report_Active				0x0301//�¼�����8.18
#define Device_Answer_Question				0x0302//����Ӧ��8.20
#define Device_Meg_ON_OFF					0x0303//��Ϣ�㲥ȡ��8.23
#define Device_Report_Car_Control			0x0500//��������Ӧ��8.27
#define DEVICE_SEND_Rec_Data	   			0x0700//��ʻ��¼�����ϴ�8.40
#define DEVICE_SEND_Cargo_menu				0x0701//�����˵��ϱ�8.42
#define DEVICE_SEND_DRIVER_MEG				0x0702//IC���ϱ�8.43
#define DEVICE_SEND_ACTIVE_Media			0x0800//	��ý���¼���Ϣ�ϴ�8.44
#define DEVICE_SEND_Media_data				0x0801//��ý�������ϴ�8.45
#define Device_Report_Media_data_serch		0x0802	//�洢��ý�����ݼ���Ӧ��8.49
#define DEVICE_SEND_NO_AT_DATA				0x0900		//�ն�����͸������8.53
#define DEVICE_SEND_RSA_KEY					0x0A00		//�ն�RSA����8.56
#define DEVICE_SEND_ZIP_DATA				0x0901		//�ն�����ѹ���ϱ�8.54
#define Device_Report_parameter1			0x0FF1		//�����ѯ�ն˲���Ӧ�� 
#define Device_Report_Logins_record			0x0FF2		//��¼��¼��ѯӦ�� 
#define Device_Report_Speeding_record		0x0FF3		//���ټ�¼��ѯӦ��
#define Device_Report_Switch_record			0x0FF4		//�������仯��¼��ѯӦ�� 
#define Device_Report_Urgent_acceleration_record		0x0FF5		//�����ټ�¼��ѯӦ��
#define Device_Report_five_sec_record		0x0FF6		//1���Ӽ���ʷ���ݲ�ѯӦ��  
#define Device_Report_one_min_record		0x0FF7		//1���Ӽ���ʷ���ݲ�ѯӦ�� 
#define Device_Report_five_min_record		0x0FF8		//5���Ӽ���ʷ���ݲ�ѯӦ��
#define Device_Report_dead_zone 			0x0F10		//ä����������
#define Device_Report_car_Analytics 		0x0F11		//�������ݷ���
#define Device_Report_History_Data 			0x0F13		//��ʷ�����ϴ�
#define Device_Report_drive_acvtive 		0x0F14		//��ʻԱ��Ϊ�¼�

/*yp*/
#if 0
#define NL_MILAGE_LEN		4	//������Ŀ��
#define NL_VERSION_LEN 		100
#define NL_PHONE_LEN 		15
#define NL_MUSTER_LEN 		512
#define NL_IP_LEN 			12 	//IP��ַÿһ��ռ3λ�������ǰ��"0"
#define NL_PORT_LEN			8
#define NL_PSW_LEN 			8
#define PSW_SHA1_LEN   		20	//����sha_1ժҪ��λ��
#define NL_APN_LEN 			20
#define NL_GPRS_USER_LEN	32
#define NL_GPRS_PSW_LEN		32
#define NL_USER_NUM 		10
#define NL_MSG_NO_LEN 		4 	//�������кų���
#define NL_MSG_LEN 			2     //���ݳ���
#define NL_CMD_LEN			2	//�����
#define NL_PARAM_LEN		2 	//��������

#define NL_TCP_TIME_OUT	10	//TCP��ʱʱ��5��
#define NL_RCV_TIME_OUT	20	//TCP��ʱʱ��5��
#define NL_SEND_TIME_OUT	30	//GPRS���ͳ�ʱʱ��30��
#define NL_SMS_TIME_OUT	40	//������Ӧ��ʱʱ��40��
#define NL_KEY_TIME_OUT	120	//��Կ����ʱʱ��120��
#define NL_DTMF_TIME_OUT	180	//DTMF���ͱ�����Ϣ��ʱʱ��180��
#define NL_SUSPEND_TIME	15	//���߻��ѵȴ�ʱ��
#define NL_COMPRESS_NUM	10	//GPSѹ�����͵���Ŀ
#define NL_ALALM_SMS_NUM	1	//ʹ�ö��ŷ��ͱ���һ�η��͵ĸ���
#define NL_GPS_TIME_LEN 15
#define NL_MRVS_LEN         11      /* �ն˰汾�� */
#define NL_VEN_LEN          5      /* ����ID */
#endif
#define max_resend_count	5//�ش��������ڵ�������
#define max_anw_timer		5//Ӧ��ʱʱ����ڵ�������
#define MAX_Send_COUNT	10


#endif
