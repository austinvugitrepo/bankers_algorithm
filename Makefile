CC = gcc
SRCS = banker.c safebankalgo.c rralgo.c
TARGET = banker
default:
	$(CC) -o $(TARGET) $(SRCS)
clean:
	rm $(TARGET)
