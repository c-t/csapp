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
	src/cachesim.c \
	src/address.c \
	src/cache.c

TARGET = build/cachesim

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run