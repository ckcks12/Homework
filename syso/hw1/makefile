CC = gcc
OBJS = mytree.o
TARGET = mytree

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS)

clean : 
	rm -f $(OBJS) $(TARGET)
