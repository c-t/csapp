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

SRC = \
      src/main.c\
      src/elf_reader.c\
      src/section_viewer.c \
      src/hex_dump.c

TARGET = miniobjdump

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
