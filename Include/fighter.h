#ifndef FIGHTER_H
#define FIGHTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define LARGEUR_FENETRE 1000
#define HAUTEUR_FENETRE 700

typedef enum {
    PAGE_MENU,
    PAGE_SELEC_MODE,
    PAGE_SELEC_DIFFICULTE,
    PAGE_SELECTION_PERSO,
    PAGE_JEU,
    PAGE_OPTIONS,
    PAGE_HISTOIRE,
    PAGE_QUITTER
} Page;

// === Fonctions principales ===
extern int mode_choisi;

Page afficher_chargement(SDL_Renderer* rendu);
Page afficher_menu(SDL_Renderer* rendu);
Page afficher_selec_mode(SDL_Renderer* rendu);
Page afficher_selec_difficulte(SDL_Renderer* rendu);
Page afficher_selection_perso(SDL_Renderer* rendu);
Page afficher_jeu(SDL_Renderer* rendu);
Page afficher_options(SDL_Renderer* rendu, Page page_prec);
Page afficher_histoire(SDL_Renderer* rendu);

// === Fonctions utilitaires ===
void jouer_musique(const char* chemin, int volume);

// === Variables globales externes ===
extern Mix_Music* musique_global;
extern int musique_lancee;

#endif
