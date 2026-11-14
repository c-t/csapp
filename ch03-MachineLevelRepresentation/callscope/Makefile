CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c17 -O0 -g -fno-omit-frame-pointer -Iinclude

SRC = src/callscope.c

TARGET = test_stack_args

all: $(TARGET)

$(TARGET): tests/test_stack_args.c $(SRC) include/callscope.h
	$(CC) $(CFLAGS) \
	tests/test_stack_args.c \
	$(SRC) \
	-o $(TARGET)

clean:
	rm -f $(TARGET)
