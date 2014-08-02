#ifndef __DEFINED_H__
#define __DEFINED_H__


#define debug	1
#define db 1

#define MSG_DEFAULT_LEN 4096


#define Center_Report_Universal				0x8001		//平台通用应答8.2
#define Center_Confirm_GPRSRegistrationB	0x8100		//注册应答8.5
#define Center_Set_Device_Parameters		0x8103		//参数设置//lizhen
#define Center_Inquire_Device_Parameters	0x8104		//参数查询
#define Center_Control_Device				0x8105		//终端控制8.11
#define Center_Require_PositionInfoA		0x8201		//位置信息查询8.13
#define Center_Require_temporary_Tail		0x8202		//临时跟踪位置信息查询8.15
#define Center_Send_Text					0x8300		//文字短信8.16
#define Center_Send_Event_SET				0x8301		//事件设置8.17
#define Center_Send_quiz					0x8302		//提问下发8.19
#define Center_Send_INFO_MENU_SET			0x8303		// 信息点播菜单设置 8.21
#define Center_Send_Message_server			0x8304		//信息服务 8.23
#define Center_Send_Phone_REcall			0x8400		//电话回拨 8.24
#define Center_Phone_Book_SET				0x8401		//设置电话本8.25
#define Center_Car_Control					0x8500		//车辆控制8.26
#define Center_Circular_Region_SET			0x8600		//设置圆形区域8.28
#define Center_Circular_Region_Del			0x8601		//删除圆形区域8.29
#define Center_Rect_Region_SET				0x8602		//设置矩形区域8.30
#define Center_Rect_Region_Del				0x8603		//删除矩形区域8.31
#define Center_Poly_Region_SET				0x8604		//设置多边形区域8.32
#define Center_Poly_Region_Del				0x8605		//删除多边形区域8.33
#define Center_Lines_SET					0x8606		//线路设置 8.34
#define Center_Lines_Del					0x8607		//设置线路8.35
#define Center_SEND_Over_rate				0x8608		//超速报警附加信息8.36
#define Center_SEND_IO_ARE_LINE				0x8609		//进出区域/路线报警附加信息8.37
#define Center_SEND_Driv_TIME				0x8610		//路段行驶时间不足/过长报警8.38
#define Center_SEND_Driv_Rec_GET			0x8700		//行驶记录仪数据采集命令8.39
#define Center_SEND_Driv_Rec_parameter		0x8701		//行驶记录参数下传命令8.41
#define Center_Report_media					0x8800		//多媒体数据上传应答8.46
#define Center_Send_CAMMER_COMMAND			0x8801		//摄像头立即拍摄命令8.47
#define Center_Send_media_SAVE_DATA_SERCH_command		0x8802		//存储多媒体数据检索8.48
#define Center_Send_media_command			0x8803		//存储多媒体数据上传命令8.50
#define Center_Send_Vol_REC_START			0x8804		//录音开始命令8.51
#define Center_Send_media_oneSearch			0x8805		//单条存储多媒体数据检索上传命令
#define Cenrer_Send_DownData_Trans			0x8900		//数据下行透传8.52	
#define Center_Send_SRA_KEY					0x8A00		//平台RSA公匙8.55
#define Center_Inquire_Device_Parameters1	0x8FF1		//按类查询终端参数 
#define Center_Logins_record				0x8FF2		//登录记录查询 
#define Center_Speeding_record				0x8FF3		//超速记录查询
#define Center_Switch_record				0x8FF4		//开关量变化记录查询 
#define Center_Urgent_acceleration_record	0x8FF5		//急加速记录查询 
#define Center_five_sec_record				0x8FF6		//1秒钟级历史数据查询  
#define Center_one_min_record				0x8FF7		//1分钟级历史数据查询 
#define Center_five_min_record				0x8FF8		//5分钟级历史数据查询 
#define Center_History_Data_Inquire			0x8F12		//历史数据查询
#define Center_History_Data_Reply			0x8F13		//历史数据查询应答

#define Device_Report_Universal				0x0001//终端通用应答8.1
#define Device_Jumper						0x0002//心跳8.3
#define Device_UnRegistration				0x0003//终端注销8.6
#define Device_Report_GPRSRegistrationB		0x0100//终端注册8.4
#define Device_Report_GPRSRegistrationA		0x0102//终端鉴权8.7
#define Device_Report_parameter				0x0104//查询终端参数应答8.10
#define Device_Report_PositionInfo2			0x0200		//主动上报//lizhen
#define Device_Report_PositionInfo3			0x0201		//后台查询回答//lizhen
#define Device_Report_Active				0x0301//事件报告8.18
#define Device_Answer_Question				0x0302//提问应答8.20
#define Device_Meg_ON_OFF					0x0303//信息点播取消8.23
#define Device_Report_Car_Control			0x0500//车辆控制应答8.27
#define DEVICE_SEND_Rec_Data	   			0x0700//行驶记录数据上传8.40
#define DEVICE_SEND_Cargo_menu				0x0701//电子运单上报8.42
#define DEVICE_SEND_DRIVER_MEG				0x0702//IC卡上报8.43
#define DEVICE_SEND_ACTIVE_Media			0x0800//	多媒体事件信息上传8.44
#define DEVICE_SEND_Media_data				0x0801//多媒体数据上传8.45
#define Device_Report_Media_data_serch		0x0802	//存储多媒体数据检索应答8.49
#define DEVICE_SEND_NO_AT_DATA				0x0900		//终端上行透传数据8.53
#define DEVICE_SEND_RSA_KEY					0x0A00		//终端RSA公匙8.56
#define DEVICE_SEND_ZIP_DATA				0x0901		//终端数据压缩上报8.54
#define Device_Report_parameter1			0x0FF1		//按类查询终端参数应答 
#define Device_Report_Logins_record			0x0FF2		//登录记录查询应答 
#define Device_Report_Speeding_record		0x0FF3		//超速记录查询应答
#define Device_Report_Switch_record			0x0FF4		//开关量变化记录查询应答 
#define Device_Report_Urgent_acceleration_record		0x0FF5		//急加速记录查询应答
#define Device_Report_five_sec_record		0x0FF6		//1秒钟级历史数据查询应答  
#define Device_Report_one_min_record		0x0FF7		//1分钟级历史数据查询应答 
#define Device_Report_five_min_record		0x0FF8		//5分钟级历史数据查询应答
#define Device_Report_dead_zone 			0x0F10		//盲区补传数据
#define Device_Report_car_Analytics 		0x0F11		//车辆数据分析
#define Device_Report_History_Data 			0x0F13		//历史数据上传
#define Device_Report_drive_acvtive 		0x0F14		//驾驶员行为事件

/*yp*/
#if 0
#define NL_MILAGE_LEN		4	//里程数的宽度
#define NL_VERSION_LEN 		100
#define NL_PHONE_LEN 		15
#define NL_MUSTER_LEN 		512
#define NL_IP_LEN 			12 	//IP地址每一段占3位，不足的前补"0"
#define NL_PORT_LEN			8
#define NL_PSW_LEN 			8
#define PSW_SHA1_LEN   		20	//密码sha_1摘要后位数
#define NL_APN_LEN 			20
#define NL_GPRS_USER_LEN	32
#define NL_GPRS_PSW_LEN		32
#define NL_USER_NUM 		10
#define NL_MSG_NO_LEN 		4 	//报文序列号长度
#define NL_MSG_LEN 			2     //数据长度
#define NL_CMD_LEN			2	//命令长度
#define NL_PARAM_LEN		2 	//参数长度

#define NL_TCP_TIME_OUT	10	//TCP超时时间5秒
#define NL_RCV_TIME_OUT	20	//TCP超时时间5秒
#define NL_SEND_TIME_OUT	30	//GPRS发送超时时间30秒
#define NL_SMS_TIME_OUT	40	//短信响应超时时间40秒
#define NL_KEY_TIME_OUT	120	//密钥请求超时时间120秒
#define NL_DTMF_TIME_OUT	180	//DTMF发送报警信息超时时间180秒
#define NL_SUSPEND_TIME	15	//休眠唤醒等待时间
#define NL_COMPRESS_NUM	10	//GPS压缩发送的数目
#define NL_ALALM_SMS_NUM	1	//使用短信发送报警一次发送的个数
#define NL_GPS_TIME_LEN 15
#define NL_MRVS_LEN         11      /* 终端版本号 */
#define NL_VEN_LEN          5      /* 厂商ID */
#endif
#define max_resend_count	5//重传次数后期调用设置
#define max_anw_timer		5//应答超时时间后期调用设置
#define MAX_Send_COUNT	10


#endif
