#include "fighter.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) return 1;
    if (IMG_Init(IMG_INIT_PNG) == 0) return 1;
    if (TTF_Init() != 0) return 1;
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return 1;

    SDL_Window* fenetre = SDL_CreateWindow("Project Shōnen Smash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    Page page_courante = afficher_chargement(rendu);

    while (page_courante != PAGE_QUITTER) {
        if (page_courante == PAGE_MENU) page_courante = afficher_menu(rendu);
        else if (page_courante == PAGE_OPTIONS) page_courante = afficher_options(rendu, PAGE_MENU);
        else if (page_courante == PAGE_HISTOIRE) page_courante = afficher_histoire(rendu);
        else page_courante = PAGE_MENU;
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
