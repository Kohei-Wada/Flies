OBJS=flies.o
SRCS=$(OBJS:%.0=%.c)
CFLAGS=-g -Wall -lm
LDLIBS=
TARGET=flies
$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)
