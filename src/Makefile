TARGET 	= tcp

SRC     =   NL_main.c set_parameter.c list.c timer.c tcp_socket.c roundbuf.c analyze_rec.c writeinfile.c find_str.c
OBJS    =   NL_main.o set_parameter.o list.o timer.o tcp_socket.o roundbuf.o analyze_rec.o writeinfile.o find_str.o

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


