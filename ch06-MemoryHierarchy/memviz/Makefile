CC=gcc

CFLAGS=-Wall \
	-Wextra \
	-Werror \
	-std=c11 \
	-Iinclude

SRC=src/parser.c \
	src/locality.c \
	src/visualization.c \
	src/memviz.c \
	src/heatmap.c

TEST_COMMON=src/parser.c \
	src/locality.c \
	src/visualization.c \
	src/heatmap.c

OBJ=$(SRC:.c=.o)

TARGET=build/memviz
TEST_TARGETS=build/test_parser build/test_locality build/test_pattern

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p build
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

build/test_parser: tests/test_parser.c $(TEST_COMMON)
	mkdir -p build
	$(CC) $(CFLAGS) tests/test_parser.c $(TEST_COMMON) -o $@

build/test_locality: tests/test_locality.c $(TEST_COMMON)
	mkdir -p build
	$(CC) $(CFLAGS) tests/test_locality.c $(TEST_COMMON) -o $@

build/test_pattern: tests/test_pattern.c $(TEST_COMMON)
	mkdir -p build
	$(CC) $(CFLAGS) tests/test_pattern.c $(TEST_COMMON) -o $@

test: $(TEST_TARGETS)
	./build/test_parser
	./build/test_locality
	./build/test_pattern

release: all test
	./build/memviz help 2>/dev/null || true

clean:
	rm -f src/*.o $(TARGET) $(TEST_TARGETS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test release