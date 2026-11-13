CC = gcc

CFLAGS = -D_GNU_SOURCE -Wall -Wextra -Werror -std=c17 -O0 -g -fno-omit-frame-pointer -Iinclude

LDFLAGS = -ldl -rdynamic

SRC = src/stackviz.c

TARGET = test_simple

all: $(TARGET)

$(TARGET): tests/test_simple.c $(SRC) include/stackviz.h
	$(CC) $(CFLAGS) tests/test_simple.c $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
