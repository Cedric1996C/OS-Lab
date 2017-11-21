#set compiler and compile options
CC   = gcc
Ld   = ld
CFLAGS =-std=c99

#target to compile
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)

sort: $(OBJS)
	$(CC) -o sort $(OBJS) $(CFLAGS)

clean:
	rm -f sort
	rm -f $(OBJS) $(OBJS:.o=.d)
