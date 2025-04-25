#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define LARGEUR_FENETRE 1024
#define HAUTEUR_FENETRE 640

typedef enum {
    PAGE_MENU,
    PAGE_OPTIONS,
    PAGE_HISTOIRE,
    PAGE_JEU,
    PAGE_QUITTER
} Page;

Page afficher_chargement(SDL_Renderer *rendu);
Page afficher_histoire(SDL_Renderer* rendu);
Page afficher_menu(SDL_Renderer* rendu);
Page afficher_options(SDL_Renderer* rendu, Page page_prec);

#endif
