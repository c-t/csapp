CC = gcc

CFLAGS = \
	 -Wall\
	 -Wextra\
	 -Werror\
	 -std=c17\
	 -O0\
	 -g\
	 -fno-omit-frame-pointer\
	 -Iinclude

TARGET = hello

all: $(TARGET)

$(TARGET): tests/hello.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET)
