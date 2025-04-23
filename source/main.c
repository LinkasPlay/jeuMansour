#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "chargement.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("Erreur SDL_Init : %s", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Erreur IMG_Init : %s", IMG_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        SDL_Log("Erreur TTF_Init : %s", TTF_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_Log("Erreur Mix_OpenAudio : %s", Mix_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("CY Fighters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Erreur création fenêtre : %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Erreur création renderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return 1;
    }

    // PAGE DE CHARGEMENT
    afficher_chargement(renderer);
    SDL_Delay(500);

    // MENU PRINCIPAL
    afficher_menu_simple(renderer);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
