#include <stdio.h>

#include "writeinfile.h"
/***********************************************************************
函数:void writetofile(unsigned char* buf,int len,unsigned char* filename)
参数: buf 数据首地址
		len 数据长度
		filename 数据写入的文件
*************************************************************************/
void writetofile(unsigned char* buf,int len,unsigned char* filename)
{
	char *p=NULL;
	char tmp[2048];
	p=Hex_Asiic(buf, len);
	sprintf(tmp,"echo -e \"%s\">>%s\n ",p,filename);
#if debug	
	printf("Recv_Data_Send_Link star\n");
	printf("Recv_Data is\" %s\"\n",p);
	printf("tmp is \"%s\"\n",tmp);
#endif	
	system(tmp);
}
/***********************************************************************
函数:void del_line(unsigned char* filename,unsigned char* character)
参数: filename 数据写入的文件
		character 删除包含character字符串 所在行
*************************************************************************/

void del_line(unsigned char* filename,unsigned char* character)
{
	char tmp[2048];
	sprintf(tmp,"sed -i -e \"/%s/d\" %s ",character,filename);	
	system(tmp);
#if debug	
	printf("tmp is\" %s\"\n",tmp);
#endif
}

/****************************************************************************
函数名称:char* Hex_Asiic(unsigned char *p,int len)
参数 :p  数据首地址
		len  数据长度
函数功能:16进制转成成ASIIC

*****************************************************************************/
char* Hex_Asiic(unsigned char *p,int len)

{
	char p2[2048]={0};
	char *p1=NULL;
	char High_4_bit;
	char Low_4_bit;
	int i,j=0;
	p1=p2;
	printf("Hex_Asiic start \n");
	
	for(i=0;i<len;i++)
	{
		High_4_bit=(*p)/0x10;
		Low_4_bit=(*p)%0x10;
		//printf("High_4_bit[%d]=%x \n",i,High_4_bit);
		//printf("Low_4_bit[%d]=%x \n",i,Low_4_bit);
		if(High_4_bit<0x0a)
		{
			High_4_bit=High_4_bit+0x30;
		}
		else
		{
			High_4_bit=High_4_bit+0x41-0x0a;
		}
		p2[j++]=High_4_bit;
		if(Low_4_bit<0x0a)
		{
			Low_4_bit=Low_4_bit+0x30;
		}
		else
		{
			Low_4_bit=Low_4_bit+0x41-0x0a;
		}
		p++;
		p2[j++]=Low_4_bit;
	}
	p2[j++]='\\';
	p2[j++]='n';
	printf("Recv_Data p2 is\" %s\"\n",p2);
	printf("Recv_Data p1 is\" %s\"\n",p1);
	return p1;
}



