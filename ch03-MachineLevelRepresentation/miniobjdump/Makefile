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
      src/hex_dump.c\
      src/symbol_viewer.c\
      src/function_viewer.c\
      src/disassembler.c\
      src/section_stats.c

TARGET = miniobjdump

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
