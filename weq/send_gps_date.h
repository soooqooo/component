#ifndef _SEND_GPS_DATE_H_
#define _SEND_GPS_DATE_H_
extern unsigned int count_i_old;
#define SEND_FILE "./gps_data_send.txt"

extern int IC384_send_fd;
void* thr_SEND_GPS(void);
void Send_Gps_Data(void);

#endif
