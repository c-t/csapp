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
	src/cache.c \
	src/fifo.c \
	src/lru.c \
	src/replacement_demo.c

TEST_SRC = \
	tests/test_replacement.c \
	src/address.c \
	src/cache.c \
	src/fifo.c \
	src/lru.c

TARGET = build/cachesim
TEST_TARGET = build/test_replacement

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test