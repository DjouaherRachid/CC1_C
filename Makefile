# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/main.c src/repl.c src/btree.c
OBJ = $(SRC:.c=.o)
TARGET = db

# Règles
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean

