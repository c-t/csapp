CC = gcc

CFLAGS = \
	 -Wall \
	 -Wextra \
	 -Werror \
	 -std=c17\
	 -O0\
	 -g\
	 -Iinclude

SRC = \
      src/addrtx.c\
      src/translator.c\
      src/formatter.c\
      src/classifier.c\
      src/page_sizes.c

TARGET = build/addrtx

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
