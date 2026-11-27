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

STATISTICS_TEST_SRC = \
	tests/test_statistics.c \
	src/address.c \
	src/cache.c \
	src/fifo.c \
	src/lru.c

LOCALITY_TEST_SRC = \
	tests/test_locality.c \
	src/address.c \
	src/cache.c \
	src/fifo.c \
	src/lru.c

TARGET = build/cachesim
TEST_TARGET = build/test_replacement
STATISTICS_TEST_TARGET = build/test_statistics
LOCALITY_TEST_TARGET = build/test_locality

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_TARGET)

$(STATISTICS_TEST_TARGET): $(STATISTICS_TEST_SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(STATISTICS_TEST_SRC) -o $(STATISTICS_TEST_TARGET)

$(LOCALITY_TEST_TARGET): $(LOCALITY_TEST_SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(LOCALITY_TEST_SRC) -o $(LOCALITY_TEST_TARGET)

test: $(TEST_TARGET) $(STATISTICS_TEST_TARGET) $(LOCALITY_TEST_TARGET)
	./$(TEST_TARGET)
	./$(STATISTICS_TEST_TARGET)
	./$(LOCALITY_TEST_TARGET)

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test