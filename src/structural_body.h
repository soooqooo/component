#ifndef __STRUCTURAL_BODY_H__
#define __STRUCTURAL_BODY_H__


#pragma pack(1) 
typedef struct Register_msg_def
{
	unsigned short int 	Province_ID;					//省域ID
	unsigned short int 	City_ID;						//市域ID
	unsigned char Manufacturers_ID[5];					//制造商ID
	unsigned char Device_model[8];						//设备型号
	unsigned char Device_ID[7];							//设备ID
	unsigned char Color_plates;							//车牌颜色
	unsigned char License_plate[10];					//车牌号码
}g_Register_msg;
 
typedef struct Authentication_msg_def
{
	char Authentication_code[20];						//鉴权码
}g_Authentication_msg;

#define tcp_connect 0
#define udp_connect 1
#define sms_connect 2
typedef struct 
{
	struct Register_msg_def Register_msg;
	struct Authentication_msg_def Authentication_msg;
	
	unsigned char Connect_Mode;						//连接模式0-tcp 1-udp 2-sms(短信包)
	
	unsigned long Jumper_Timer;						//终端心跳发送间隔
	unsigned long TCP_Anwer_OverTime;				//tcp消息应答超时
	unsigned long TCP_Resend_Count;					//tcp消息重传次数
	unsigned long UDP_Anwer_OverTime;				//UDP消息应答超时
	unsigned long UDP_Resend_Count;					//UDP消息重传次数
	unsigned long SMS_Anwer_OverTime;				//SMS消息应答超时
	unsigned long SMS_Resend_Count;					//SMS消息重传次数
	char			Master_Server_APN[20];				//主中心服务器APN，无线通信拨号访问点/CDMA->PPP拨号号码
	char			Master_Server_UserName[10];		//主服务器无线通讯拨号用户名
	char			Master_Server_PassWord[10];		//主服务器无线通信拨号密码
	char			Master_Server_IP[20];				//主服务器地址，ip或域名
	char			Reserve_Server_APN[20];			//备份服务器APN，无线通信拨号访问点/CDMA->PPP拨号号码
	char			Reserve_Server_UserName[10];		//主服务器无线通讯拨号用户名
	char			Reserve_Server_PassWord[10];		//主服务器无线通信拨号密码
	char			Reserve_Server_IP[20];				//主服务器地址，ip或域名
	unsigned int	TCP_Port;							//服务器TCP端口
	unsigned int	UDP_Port;							//服务器UDP端口
	unsigned long Position_Report_Tactics;				//位置汇报策略 0-定时汇报；1定距汇报；2定时和定距汇报
	unsigned long Position_Report_Plan;				//位置汇报方案 0-根据ACC状态；1-根据登录状态和ACC状态
	unsigned long Aeronaut_UnLogin_Report_Timer;		//驾驶员未登录汇报时间间隔
	unsigned long Sleep_Report_Timer;					//休眠时间汇报时间间隔
	unsigned long Emergency_Alarm_Report_Timer;		//紧急报警时汇报时间间隔
	unsigned long Default_Report_Distance;				//缺省距离汇报间隔
	unsigned long Default_Report_Timer;				//缺省时间汇报间隔
	unsigned long Aeronaut_UnLogin_Report_Distance;	//驾驶员未登录汇报时间间隔
	unsigned long Sleep_Report_Distance;				//休眠时间汇报距离间隔
	unsigned long Emergency_Alarm_Report_Distance;	//紧急报警时汇报距离间隔
	unsigned long Round_Supplemental_transmission_Angl;//拐点补传角度
	unsigned char Server_TELNum[15];					//监控平台电话号码
	unsigned char Reset_Terminal_TelNum[15];			//终端复位电话号码
	unsigned char Default_Para_TelNum[15];			//恢复出厂设置电话号码
	unsigned char Server_SMS_TelNum[15];				//监控平台SMS电话号码
	unsigned char Receiver_SMS_Alarm_Report_TelNum;//接收终端SMS文本报警号码
	unsigned long Tel_Answer_Tactics;					//电话接听策略 0-自动接听；1-ACC ON时自动接听OFF时手动接听
	unsigned long Max_Tel_Answer_Timer_Once;		//每次通话最长时间0-不允许；最大值为不限制
	unsigned long Max_Tel_Answer_Timer_Month;		//每月最长通话时间0-不允许；最大值为不限制
	unsigned char Listen_TelNum[15];					//监听电话号码
	unsigned char	VIP_SMS_TelNum[15];				//监管平台特权短信号码
	unsigned long Disable_Alarm_Flage;				//报警屏蔽字
	unsigned long Send_Alarm_SMS_Flage;				//报警发送SMS文本开关
	unsigned long Alarm_Photograph_Flage;			//报警拍摄开关1为拍照
	unsigned long Alarm_Photograph_Save_Flage;		//报警拍摄存储标志位1为存储否则上传
	unsigned long Crucial_Flage;						//关键标志，与位置信息汇报中报警标志相对应，1则对应报警为关键报警
	unsigned long Max_Speed;							//最高速度
	unsigned long Over_Speed_Continu_time;			//超速持续时间
	unsigned long Max_Continu_Drivering_Time;				//连续驾驶时间门限
	unsigned long Continu_Drivering_Time_Day;			//当天累计驾驶时间
	unsigned long Min_Rest_Time;						//最小休息时间
	unsigned long Max_Stop_Time;						//最长停车时间
	unsigned long Image_Quality_Mode;				//图像视频质量1~10，1最好
	unsigned long Brightness_Para;						//亮度0~255
	unsigned long Contrast_Para;						//对比度0~127
	unsigned long Saturation_Para;						//饱和度0~127
	unsigned long Chroma_Para;						//色度0~255
	unsigned long Odometer_Numerical;				//里程表数值1/10km
	

	int Check_Sum;
	
}G_JT_T_808_2011_Parameter;

typedef struct g_msg_send_Method
{
	unsigned char send_flage;			//发送标志位
	unsigned short int Resend_count;	//重传次数
	unsigned  long Resend_Timer;		//重传时间

}msg_send_Method_type;

typedef struct heah_type			//消息头
{
	unsigned char head;
	unsigned short int ID;
	unsigned short int attrib;
	unsigned char tel_num[6];
	unsigned short int ser_num;
}JT_T_808_2011_data_heah_type_def;

typedef struct Pack_Type			//分包结构体
{
	unsigned short int total_pack_num;
	unsigned short int pack_num;
}JT_T_808_2011_data_PAck_type_def;

typedef struct data_end_def		//要发送的数据  ????
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
	unsigned short int len;  //数据长度
	unsigned char * buf;     //数据首地址
}msg_buf_type;

typedef struct Send_data
{
	int len;
	unsigned char *msg;
}send_data_msg;

#pragma pack()

#endif

