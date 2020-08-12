CC = clang
CFLAGS = -g -Wall -std=c18

TARGET = lang
OBJS = lang.o eval.o
.PHONY: all clean format check

all: $(TARGET)

clean:
	- rm -f *.o $(TARGET) test
format:
	clang-format -i *.c *.h

check: all test
	./test

$(TARGET): $(OBJS)
$(OBJS): lang.h
