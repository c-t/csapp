CC = gcc

CFLAGS = -Wall -Wextra -Werror -std=c17 -O0 -g -fno-omit-frame-pointer -Iinclude

TARGET = test_abi

all: $(TARGET)

$(TARGET): tests/test_abi.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
