CC       = gcc
CFLAGS   = -Wall -IInclude `sdl2-config --cflags`
LIBS     = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer

SRC = \
    Source/attaque.c \
    Source/data.c \
    Source/interface.c \
    Source/jeu.c \
    Source/langue.c \
    Source/logique.c \
    Source/main.c \
    Source/maps.c \
    Source/menu.c \
    Source/select_perso.c



EXEC     = exec/jeu

.PHONY: all compile jeu clean

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