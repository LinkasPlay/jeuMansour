#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"
#include "texte.h"
#include "langue.h"

void quitter(const char* message) {
    SDL_Log("Erreur : %s\nSDL_Error : %s", message, SDL_GetError());
    IMG_Quit(); TTF_Quit(); SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_Rect centrer(SDL_Texture* texture, SDL_Window* fenetre, int y) {
    int fw, fh, tw, th;
    SDL_GetWindowSize(fenetre, &fw, &fh);
    SDL_QueryTexture(texture, NULL, NULL, &tw, &th);
    SDL_Rect r = { (fw - tw) / 2, y, tw, th };
    return r;
}

void afficher_menu(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) quitter("SDL_Init");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) quitter("IMG_Init");
    if (TTF_Init() != 0) quitter("TTF_Init");

    SDL_Window* fenetre = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);
    if (!fenetre) quitter("fenêtre");

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!rendu) quitter("renderer");

    // Chargement de la police et création des textures de texte
    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 36);
    if (!police) quitter("police");

    SDL_Texture* txt_jouer = generer_texte(rendu, get_texte("START"), police);
    SDL_Texture* txt_options = generer_texte(rendu, get_texte("OPTIONS"), police);
    SDL_Texture* txt_quitter = generer_texte(rendu, get_texte("QUIT"), police);
    
    SDL_Rect r1 = centrer(txt_jouer, fenetre, 150);
    SDL_Rect r2 = centrer(txt_options, fenetre, r1.y + r1.h + 10);
    SDL_Rect r3 = centrer(txt_quitter, fenetre, r2.y + r2.h + 10);

    int actif = 1;
    SDL_Event event;

    while (actif) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) actif = 0;

            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                if (x >= r3.x && x <= r3.x + r3.w && y >= r3.y && y <= r3.y + r3.h) {
                    actif = 0; // clic sur "QUITTER"
                }
            }
        }

        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, txt_jouer, NULL, &r1);
        SDL_RenderCopy(rendu, txt_options, NULL, &r2);
        SDL_RenderCopy(rendu, txt_quitter, NULL, &r3);
        SDL_RenderPresent(rendu);
        SDL_Delay(1);
    }

    SDL_DestroyTexture(txt_jouer);
    SDL_DestroyTexture(txt_options);
    SDL_DestroyTexture(txt_quitter);
    TTF_CloseFont(police);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    IMG_Quit(); TTF_Quit(); SDL_Quit();
}
