CC = gcc
CFLAGS = -Wall -Iinclude `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = build/Cyfighters.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f src/*.o $(TARGET)
