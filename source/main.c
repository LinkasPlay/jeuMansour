#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#include "intro.h"
#include "langue.h"
#include "menu.h"
#include "texte.h"
#include "page.h"

// Quitter avec un message d'erreur
void quitter(const char* message) {
    SDL_Log("Erreur : %s\nSDL_Error : %s", message, SDL_GetError());
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// Fonction pour centrer une texture
SDL_Rect centrer(SDL_Texture* texture, SDL_Window* fenetre) {
    int fw, fh, tw, th;
    SDL_GetWindowSize(fenetre, &fw, &fh);
    SDL_QueryTexture(texture, NULL, NULL, &tw, &th);

    SDL_Rect r = {
        (fw - tw) / 2,
        (fh - th) / 2,
        tw,
        th
    };
    return r;
}

// Logo de lancement (logo_MYM.png)
void afficher_logo_lancement(SDL_Renderer* rendu, SDL_Window* fenetre) {
    SDL_Texture* logo = IMG_LoadTexture(rendu, "ressource/image/logo_MYM.png");
    if (!logo) {
        SDL_Log("Erreur chargement logo lancement : %s", SDL_GetError());
        return;
    }

    Uint32 debut = SDL_GetTicks();
    SDL_Event e;

    while (SDL_GetTicks() - debut < 2000) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
        }

        SDL_RenderClear(rendu);
        SDL_Rect position = centrer(logo, fenetre);
        SDL_RenderCopy(rendu, logo, NULL, &position);
        SDL_RenderPresent(rendu);
        SDL_Delay(10);
    }

    SDL_DestroyTexture(logo);
}

int main() {
    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) quitter("SDL_Init");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) quitter("IMG_Init");
    if (TTF_Init() != 0) quitter("TTF_Init");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) quitter("Mix_OpenAudio");

    // Création de la fenêtre
    SDL_Window* fenetre = SDL_CreateWindow("MYM Fighters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    if (!fenetre) quitter("Création fenêtre");

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rendu) quitter("Création rendu");

    // Chargement de la langue
    charger_langue("ressource/langue/francais.txt");

    // === Étape 1 : logo MYM
    afficher_logo_lancement(rendu, fenetre);

    // === Étape 2 : générique de début (logo MYM Fighters + son + frames vidéo)
    Page page = afficher_intro(rendu, fenetre);

    // === Étape 3 : menu
    while (page != PAGE_QUITTER) {
        if (page == PAGE_MENU) {
            page = afficher_menu(rendu, fenetre);
        } else if (page == PAGE_HISTOIRE) {
            // à venir : afficher_histoire(rendu, fenetre);
            page = PAGE_MENU;
        } else {
            page = PAGE_QUITTER;
        }
    }

    // Nettoyage
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
