#include "../Include/fighter.h"
#include <stdio.h>
//test 1

 
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Erreur initialisation SDL : %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        printf("Erreur initialisation TTF : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        printf("Erreur initialisation Mixer : %s\n", Mix_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    

    SDL_Window* fenetre = SDL_CreateWindow(
        "Project Shōnen Smash",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE,
        SDL_WINDOW_SHOWN
    );

    if (!fenetre) {
        printf("Erreur création fenêtre : %s\n", SDL_GetError());
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rendu) {
        printf("Erreur création renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // === PAGE DE DÉPART ===
    Page page = afficher_chargement(rendu);

    int quit = 0;
    while (!quit) {
        switch (page) {
            case PAGE_MENU:
                page = afficher_menu(rendu);
                break;
            case PAGE_SELEC_MODE:
                page = afficher_selec_mode(rendu);
                break;
            case PAGE_SELEC_DIFFICULTE:
                page = afficher_selec_difficulte(rendu);
                break;
            case PAGE_SELECTION_PERSO:
                page = afficher_selection_perso(rendu);
                break;
            case PAGE_JEU:
                page = afficher_jeu(rendu);
                break;
            case PAGE_OPTIONS:
                page = afficher_options(rendu, PAGE_MENU);
                break;
            case PAGE_HISTOIRE:
                page = afficher_histoire(rendu);
                break;
            case PAGE_QUITTER:
                quit = 1;
                break;
            default:
                quit = 1;
                break;
        }
    }

    if (musique_global) {
        Mix_FreeMusic(musique_global);
        musique_global = NULL;
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}