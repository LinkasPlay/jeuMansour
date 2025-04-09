PROG = projet

SRC = src/main.c src/graphics.c src/game.c src/fighter.c src/combat.c

CC = gcc
CFLAGS = -Wall sdl2-config --cflags
LDFLAGS = sdl2-config --libs -lSDL2_image
INCLUDES = -Iinclude

all: $(PROG)

$(PROG): $(SRC)
    $(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

clean:
    rm -f $(PROG)