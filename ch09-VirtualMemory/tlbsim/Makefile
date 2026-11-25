CC = gcc

CFLAGS = \
	-Wall \
	-Wextra \
	-Werror \
	-std=c17 \
	-O0 \
	-g \
	-Iinclude

SRC = \
	src/tlbsim.c \
	src/tlb.c \
	src/access_pattern.c \
	src/fifo.c \
	src/lru.c \
	src/stats.c \
	src/locality.c

TARGET = build/tlbsim

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run