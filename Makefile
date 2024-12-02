CC = gcc
CFLAGS = -Iinclude
SRC = src/menu.c src/main.c src/Labirinto.c
OBJ = $(SRC:.c=.o)
TARGET = make

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
