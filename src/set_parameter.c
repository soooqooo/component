#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>



#include"set_parameter.h"
 



#define HVT_SET_FILE_NAME "/home/hvt_SET_FILE.cfg"  //配置文件
NL_ROUNDBUF_T tcpround;
extern unsigned char s_tcpbuf[MSG_DEFAULT_LEN];

G_JT_T_808_2011_Parameter JT_T_808_2011_Parameter;


/**********************************************************************************
函数名称: GET_SET_Parameter
函数说明:读取设置参数到JT_T_808_2011_Parameter中，如果写入失败，
				调用Save_Para()函数
			
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
	{//读取失败重新录入初始化数据
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
函数名称:void Clear_File(char* dest)
函数说明  :清空文件dest
参数: dest   文件名字符串的首地址

********************************************************************************/

void Clear_File(char* dest)
{
	printf("Clear_File star\r\n");
	char p[100]="cat /dev/null > ";
	strcat(p,dest);//连接2个字符串
	printf("Clear_File command %s\r\n",p);
	system(p);	
	//cat /dev/null > /etc/test.txt 此为清空/etc/test.txt档案内容
	printf("Clear_File end\r\n");
	return;
}
/**********************************************************************************
函数名称:void Save_Para(void)
函数说明  :保存初始化数据
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
	JT_T_808_2011_Parameter.Register_msg.Province_ID=83;							//省域ID
	JT_T_808_2011_Parameter.Register_msg.City_ID=20;								//市域ID
	strcpy(JT_T_808_2011_Parameter.Register_msg.Manufacturers_ID,"12345");			//制造商ID
	strcpy(JT_T_808_2011_Parameter.Register_msg.Device_model,"hvt100");			//设备型号
	strcpy(JT_T_808_2011_Parameter.Register_msg.Device_ID,"hvt100");				//设备ID
	JT_T_808_2011_Parameter.Register_msg.Color_plates=1;						//车牌颜色
	strcpy(JT_T_808_2011_Parameter.Register_msg.License_plate,"沪Bd1234");		//车牌号码
	memset(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code,0,sizeof(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code));
	//strcpy(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code,"1234554321");//测试用int

	JT_T_808_2011_Parameter.Connect_Mode=0;						//连接模式0-tcp 1-udp 2-sms(短信包)
	
	JT_T_808_2011_Parameter.Jumper_Timer=10;						//终端心跳发送间隔
	JT_T_808_2011_Parameter.TCP_Anwer_OverTime=60;				//tcp消息应答超时
	JT_T_808_2011_Parameter.TCP_Resend_Count=10;					//tcp消息重传次数
	JT_T_808_2011_Parameter.UDP_Anwer_OverTime=60;				//UDP消息应答超时
	JT_T_808_2011_Parameter.UDP_Resend_Count=10;					//UDP消息重传次数
	JT_T_808_2011_Parameter.SMS_Anwer_OverTime=60;				//SMS消息应答超时
	JT_T_808_2011_Parameter.SMS_Resend_Count=10;					//SMS消息重传次数
	strcpy(JT_T_808_2011_Parameter.Master_Server_APN,"1234");		//主中心服务器APN，无线通信拨号访问点/CDMA->PPP拨号号码
	//Master_Server_PassWord
	strcpy(JT_T_808_2011_Parameter.Master_Server_UserName,"lizhen");		//主服务器无线通讯拨号用户名
	strcpy(JT_T_808_2011_Parameter.Master_Server_PassWord,"2345");		//主服务器无线通信拨号密码
	strcpy(JT_T_808_2011_Parameter.Master_Server_IP,"117.135.136.130");		//主服务器地址，ip或域名
	
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_APN,"1234");		//备份服务器APN，无线通信拨号访问点/CDMA->PPP拨号号码
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_UserName,"lizhen");	//备份务器无线通讯拨号用户名
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_PassWord,"5678");		//备份务器无线通信拨号密码
	strcpy(JT_T_808_2011_Parameter.Reserve_Server_IP,"117.135.136.130");		//备份务器地址，ip或域名
	JT_T_808_2011_Parameter.TCP_Port=8080;							//服务器TCP端口
	JT_T_808_2011_Parameter.UDP_Port=6060;							//服务器UDP端口
	JT_T_808_2011_Parameter.Position_Report_Tactics=0;				//位置汇报策略 0-定时汇报；1定距汇报；2定时和定距汇报
	JT_T_808_2011_Parameter.Position_Report_Plan=0;				//位置汇报方案 0-根据ACC状态；1-根据登录状态和ACC状态
	JT_T_808_2011_Parameter.Aeronaut_UnLogin_Report_Timer=20;		//驾驶员未登录汇报时间间隔
	JT_T_808_2011_Parameter.Sleep_Report_Timer=120;					//休眠时间汇报时间间隔
	JT_T_808_2011_Parameter.Emergency_Alarm_Report_Timer=5;		//紧急报警时汇报时间间隔
	JT_T_808_2011_Parameter.Default_Report_Distance=500;				//缺省距离汇报间隔
	JT_T_808_2011_Parameter.Default_Report_Timer=10;				//缺省时间汇报间隔
	JT_T_808_2011_Parameter.Aeronaut_UnLogin_Report_Distance=100;	//驾驶员未登录汇报时间间隔
	JT_T_808_2011_Parameter.Sleep_Report_Distance=50;				//休眠时间汇报距离间隔
	#if 0
	SET_Parameter.Emergency_Alarm_Report_Distance=100;	//紧急报警时汇报距离间隔
	unsigned long Round_Supplemental_transmission_Angl=15;//拐点补传角度
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


