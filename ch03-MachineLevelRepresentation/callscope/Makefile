CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c17 -O0 -g -fno-omit-frame-pointer -Iinclude

SRC = src/callscope.c

TARGET = test_pointers

all: $(TARGET)

$(TARGET): tests/test_pointers.c
	$(CC) $(CFLAGS) \
	tests/test_pointers.c \
	$(SRC) \
	-o $(TARGET)

clean:
	rm -f $(TARGET)
