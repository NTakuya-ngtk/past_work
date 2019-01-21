CC = gcc
CFLAGS = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS = -ll

OBJS = main.o stm.o filter.o pagefeed.o linefeed.o htab.o header.o postscript.o

textformat: $(OBJS)
	$(CC) -o textformat $(OBJS) $(LDLIBS)
