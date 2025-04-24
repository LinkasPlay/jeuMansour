#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#define LARGEUR_FENETRE 1024
#define HAUTEUR_FENETRE 640

typedef enum {
    PAGE_MENU,
    PAGE_OPTIONS,
    PAGE_HISTOIRE,
    PAGE_QUITTER
} Page;

extern Page afficher_chargement(SDL_Renderer *rendu);
extern Page afficher_menu(SDL_Renderer *rendu);
extern Page afficher_options(SDL_Renderer *rendu, Page page_prec);
extern Page afficher_histoire(SDL_Renderer *rendu);

#endif
