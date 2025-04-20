#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

#include "intro.h"
#include "langue.h"
#include "menu.h"
#include "texte.h"

// Fonction pour quitter le jeu en cas d'erreur
void quitter(const char* message) {
    SDL_Log("Erreur : %s\nSDL_Error : %s", message, SDL_GetError());
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// Fonction pour centrer une texture dans la fenêtre
SDL_Rect centrer(SDL_Texture* texture, SDL_Window* fenetre, int y) {
    int largeur_fenetre, hauteur_fenetre;
    SDL_GetWindowSize(fenetre, &largeur_fenetre, &hauteur_fenetre);

    int largeur_texture, hauteur_texture;
    SDL_QueryTexture(texture, NULL, NULL, &largeur_texture, &hauteur_texture);

    SDL_Rect position = {
        (largeur_fenetre - largeur_texture) / 2,
        y,
        largeur_texture,
        hauteur_texture
    };
    return position;
}

int main() {
    // Initialisation des bibliothèques SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        quitter("Échec de l'initialisation de SDL");

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
        quitter("Échec de l'initialisation de SDL_image");

    if (TTF_Init() != 0)
        quitter("Échec de l'initialisation de SDL_ttf");

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        quitter("Échec de l'initialisation de SDL_mixer");

    // Création de la fenêtre
    SDL_Window* fenetre = SDL_CreateWindow("MYM Fighters",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           800, 600,
                                           SDL_WINDOW_RESIZABLE);
    if (!fenetre)
        quitter("Création de la fenêtre échouée");

    // Création du rendu
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rendu)
        quitter("Création du rendu échouée");

    // Chargement des textes (langue)
    charger_langue("ressource/langue/francais.txt");

    // Générique de début (logo + son)
    afficher_intro(rendu, fenetre);

    // Menu principal
    afficher_menu(rendu, fenetre);

    // Nettoyage
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
