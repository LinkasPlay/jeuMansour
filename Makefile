CC = gcc
CFLAGS = -Wall -Iinclude `sdl2-config --cflags` -lSDL2 -lSDL2_ttf
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = build/run

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f src/*.o $(TARGET)
