#ifndef _TCHANGE_DATA_H_
#define _TCHANGE_DATA_H_
unsigned short int ASCII_TO_16(unsigned char*msg_in,unsigned char*msg_out,unsigned short int len);
unsigned short int char_TO_word(unsigned char*msg_in,unsigned short int len,unsigned char move_count);
unsigned  long char_TO_long(unsigned char*msg_in,unsigned short int len,unsigned char move_count);
unsigned char char_TO_char(unsigned char*msg_in,unsigned short int len,unsigned char move_count);
#endif
