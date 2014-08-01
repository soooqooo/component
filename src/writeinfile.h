#ifndef __WRITEINFILE_H__
#define __WRITEINFILE_H__


void writetofile(unsigned char* buf,int len,unsigned char* filename);
void del_line(unsigned char* filename,unsigned char* character);
char* Hex_Asiic(unsigned char *p,int len);


#endif

