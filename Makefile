CC = gcc
CFLAGS = -Wall -IInclude `sdl2-config --cflags`
LIBS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRC = \
    Source/main.c \
    Source/menu.c \
    Source/select_perso.c \
    Source/selection.c \
    Source/equipe.c \
    Source/fighter_data.c \
    Source/langue.c \
    Source/maps.c \
    Source/initialisation.c \
    Source/gameplay.c \
    Source/generation_maps.c

EXEC = exec/jeu

all: $(EXEC)

$(EXEC): $(SRC)
	@mkdir -p exec
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	@echo "✅ Compilation réussie : $(EXEC)"

compile: clean all

jeu: compile
	@echo "🎮 Lancement du jeu..."
	@./$(EXEC)

clean:
	@echo "🧹 Nettoyage..."
	@rm -f $(EXEC)
