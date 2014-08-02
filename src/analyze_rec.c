#include <stdio.h>
#include <stdlib.h>  //calloc
#include <string.h>

#include "analyze_rec.h"
extern int ENable_ANALYZ_REC;
extern int Data_Rec_count;
extern JT_T_808_2011_data_type_Link *Rec_LinkList;
extern JT_T_808_2011_data_type_Link *Send_LinkList;
extern G_JT_T_808_2011_Parameter JT_T_808_2011_Parameter;
extern int Register_lizhen_ed;
extern int Data_Send_count;

/***************************************************************************************
函数名称:void* Analyze_rec_pro()
函数作用 :解析接受的数据
****************************************************************************************/
void Analyze_rec_program()
{
	int flage;
	while(1)
	{
		if(ENable_ANALYZ_REC)//此处应形成独立函数查询链表				
		{
			int jj=0;
			int i;
			JT_T_808_2011_data_type_Link *prt = NULL;
			printf("**************Data_Rec_count= %d***********\n",Data_Rec_count);
			prt = Rec_LinkList;
			while(prt!=NULL)
			{
				Analyze_program(prt);
				if(prt->JT_T_808_2011_data.head1.ID==Center_Report_Universal)//如果是通用应答
				{
					JT_T_808_2011_data_heah_type_def* code_ser=NULL;
					unsigned short int snum;
					snum=prt->data_buf[0];
					snum=snum*0x100+prt->data_buf[1];//获取应答流水号
					printf("snum = %x\n",snum);
					code_ser=(JT_T_808_2011_data_heah_type_def*)calloc(1, sizeof(JT_T_808_2011_data_heah_type_def));
					code_ser->ser_num=snum;
					printf("prt->JT_T_808_2011_data.head1.ID==Center_Report_Universal snum=%x\n",code_ser->ser_num);
					printf("prt->JT_T_808_2011_data.head1.ID==Center_Report_Universal snum=%x\n",snum);
					DEl_LINK_NOTE(&Send_LinkList,NONE_Link_NUM,code_ser,&Data_Send_count);
					//DEl_LINK_NOTE(&Send_LinkList,i,NULL,&Data_Send_count);
					free(code_ser);
				}
				printf("Analyze_rec_program Rec_LinkList DEl_LINK_NOTE\n");
				DEl_LINK_NOTE(&Rec_LinkList,1,NULL,&Data_Rec_count);
				//DEl_LINK_NOTE(&Rec_LinkList,1,NULL,&Data_Rec_count);
				prt=prt->next;
			}
			ENable_ANALYZ_REC=0;
		}		
	}
	return;
}
/***********************************************************************************
函数名称:void* Analyze_rec_pro()
函数作用 :分析接受数据线程
****************************************************************************************/
void* Analyze_rec_pro()
{
	pthread_detach( pthread_self() );
	//pthread_t cthd;
	//int stat = pthread_create( &cthd, NULL, thr_get, NULL );
	Analyze_rec_program();
	pthread_exit(0);
}
/***********************************************************************************
函数名称:void Analyze_program(JT_T_808_2011_data_type_Link *prt)
函数作用 :分析应答
****************************************************************************************/

void Analyze_program(JT_T_808_2011_data_type_Link *prt)
{
	int i;
	
	switch((*prt).JT_T_808_2011_data.head1.ID)
	{
		case Center_Confirm_GPRSRegistrationB:  
			memcpy(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code,prt->data_buf+3,((*prt).JT_T_808_2011_data.head1.attrib)-3);			
			pack_Register_send_msg((unsigned short int)(Device_Report_GPRSRegistrationA),NULL,prt);
			JT_T_808_2011_data_heah_type_def* code_ser=NULL;
			code_ser=(JT_T_808_2011_data_heah_type_def*)calloc(1, sizeof(JT_T_808_2011_data_heah_type_def));
			code_ser->ID=Device_Report_GPRSRegistrationB;
			DEl_LINK_NOTE(&Send_LinkList,NONE_Link_NUM,code_ser,&Data_Send_count);
			free(code_ser);
			memset(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code,0,sizeof(JT_T_808_2011_Parameter.Authentication_msg.Authentication_code));
			printf("get Center_Confirm_GPRSRegistrationB\n");
			break;
		case Center_Report_Universal:
			{
			printf("get Center_Report_Universal\n");
			unsigned short int ID_Code=0;
			ID_Code+=prt->data_buf[2];
			ID_Code=ID_Code*0x100+prt->data_buf[3];//应答ID
			printf("get ID_Code=%x\n",ID_Code);
			if(ID_Code==Device_Report_GPRSRegistrationA)//如果是鉴权通用应答
			{
				Register_lizhen_ed=1;
				printf("get Register_lizhen_ed=%x\n",Register_lizhen_ed);
			}
			for (i=0;i<((*prt).JT_T_808_2011_data.head1.attrib);i++)
				printf("Center_Report_Universal data[%d]: %x\n",i,*(prt->data_buf)++);
			for (i=0;i<((*prt).JT_T_808_2011_data.head1.attrib);i++)
				*(prt->data_buf)--;
			}
			break;		
		}	
	return;
}

