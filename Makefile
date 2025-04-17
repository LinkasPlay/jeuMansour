CC = gcc
CFLAGS = -Wall -Iinclude `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2

SRC = $(wildcard source/*.c)
TARGET = exec/jeu

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

compile: clean all    # Nettoie et compile

jeu: compile          # Compile et exécute
	./exec/jeu

clean:
	rm -f source/*.o $(TARGET)











 