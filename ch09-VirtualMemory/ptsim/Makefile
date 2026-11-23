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
	src/ptsim.c \
	src/translator.c \
	src/formatter.c \
	src/pagetable.c \
	src/pagewalk.c \
	src/physical.c

TARGET = build/ptsim

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -rf build

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run