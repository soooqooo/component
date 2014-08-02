TARGET 	= mn_384_IC

SRC     =  timer.c Troundbuf.c MN_384_IC.c add_msg_link.c Tlinked_list.c get_gps_date.c find_str.c  Tchange_data.c send_gps_date.c  Ttime.c
OBJS    =  timer.o Troundbuf.o MN_384_IC.o add_msg_link.o Tlinked_list.o get_gps_date.o find_str.o  Tchange_data.o send_gps_date.o Ttime.o

CC = gcc
LD = gcc
CFLAGS = 
#-Wall -g
LDLIBS = -lpthread

#ifeq ($(DEBUG),y)
#  CFLAGS += -DDEBUG
#endif


all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(LD) $(LDLIBS) -o $@ $(OBJS)

.PHONY: all clean


