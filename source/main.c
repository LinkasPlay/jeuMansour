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

// Quitte le jeu avec un message d'erreur
void quitter(const char* message) {
    SDL_Log("Erreur : %s\nSDL_Error : %s", message, SDL_GetError());
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}

// Affiche le logo MYM + texte au lancement
void afficher_logo_lancement(SDL_Renderer* rendu, SDL_Window* fenetre) {
    SDL_Texture* logo = IMG_LoadTexture(rendu, "ressource/image/logo_MYM.png");
    if (!logo) {
        SDL_Log("Erreur chargement logo MYM : %s", SDL_GetError());
        return;
    }

    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 24);
    if (!police) {
        SDL_Log("Erreur chargement police : %s", TTF_GetError());
        SDL_DestroyTexture(logo);
        return;
    }

    SDL_Color rouge = {200, 0, 0};
    SDL_Texture* texte_intro = generer_texte_couleur(rendu, "Bienvenue dans MYM Fighters !", police, rouge);

    Uint32 debut = SDL_GetTicks();
    SDL_Event e;

    while (SDL_GetTicks() - debut < 2000) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
        }

        int largeur_fenetre, hauteur_fenetre;
        SDL_GetWindowSize(fenetre, &largeur_fenetre, &hauteur_fenetre);

        // Redimension du logo
        int taille_logo = largeur_fenetre / 8;
        SDL_Rect position_logo = {20, 20, taille_logo, taille_logo};

        // Texte centré sous le logo
        int tw, th;
        SDL_QueryTexture(texte_intro, NULL, NULL, &tw, &th);
        SDL_Rect position_texte = {
            (largeur_fenetre - tw) / 2,
            position_logo.y + position_logo.h + 20,
            tw,
            th
        };

        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, logo, NULL, &position_logo);
        SDL_RenderCopy(rendu, texte_intro, NULL, &position_texte);
        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(logo);
    SDL_DestroyTexture(texte_intro);
    TTF_CloseFont(police);
}

int main() {
    // Initialisation
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) quitter("SDL_Init");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) quitter("IMG_Init");
    if (TTF_Init() != 0) quitter("TTF_Init");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) quitter("Mix_OpenAudio");

    // Fenêtre et rendu
    SDL_Window* fenetre = SDL_CreateWindow("MYM Fighters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    if (!fenetre) quitter("Création fenêtre");

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rendu) quitter("Création rendu");

    // Langue
    charger_langue("ressource/langue/francais.txt");

    // Logo MYM au lancement
    afficher_logo_lancement(rendu, fenetre);

    // Générique (logo MYM FIGHTERS + vidéo)
    Page page = afficher_intro(rendu, fenetre);

    // Navigation
    while (page != PAGE_QUITTER) {
        if (page == PAGE_MENU) {
            page = afficher_menu(rendu, fenetre);
        } else if (page == PAGE_HISTOIRE) {
            // (plus tard) page = afficher_histoire(...);
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
