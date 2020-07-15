CC=gcc
CFLGAS=-g -Wall
TARGET=a.out
OBJS=ArrayList.o ListMain.o NameCard.o

$(TARGET) : $(OBJS)
	$(CC) $(CFLGAS) -o $@ $^

ListMain.o : ArrayList.h ListMain.c
ArrayList.o : ArrayList.h ArrayList.c
NameCard.o : NameCard.h NameCard.c


clean :
	rm -rf $(TARGET) $(OBJS)