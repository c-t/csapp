CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c17 -O0 -g -fno-omit-frame-pointer -Iinclude

SRC = src/callscope.c

TARGET = test_registers

all: $(TARGET)

$(TARGET): tests/test_registers.c $(SRC)
	$(CC) $(CFLAGS) \
	tests/test_registers.c \
	$(SRC) \
	-o $(TARGET)

clean:
	rm -f $(TARGET)
