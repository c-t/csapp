CC=gcc

CFLAGS=-Wall \
	-Wextra \
	-std=c11 \
	-Iinclude

SRC=src/parser.c \
	src/locality.c \
    src/visualization.c \
    src/memviz.c \
	src/heatmap.c

OBJ=$(SRC:.c=.o)

TARGET=build/memviz

$(TARGET): $(OBJ)
	mkdir -p build
	$(CC) $(OBJ) -o $(TARGET)

clean:
	rm -f src/*.o build/memviz