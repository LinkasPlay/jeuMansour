#include "fighter.h"
#include "equipe.h"
#include "gameplay.h"
#include "generation_maps.h"
#include "maps.h"
#include "personnage.h"
#include "selection.h"

#include <time.h>
#include <stdio.h>





int main(int argc, char* argv[]) {

    Partie partie;
    initialiser_equipe(&partie.equipe1);
    initialiser_equipe(&partie.equipe2);
    partie.element_map = ELEMENT_FEU;
    partie.id_map = 1;

    // Initialisation des variables
    Mix_Music* musique_global = NULL;
    SDL_Texture* selections_j1[3] = {NULL, NULL, NULL};
    SDL_Texture* selections_j2[3] = {NULL, NULL, NULL};
    Page page = PAGE_MENU;
    int quit = 0;

    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("Erreur initialisation SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur initialisation TTF : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Initialisation SDL_mixer
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        printf("Erreur initialisation Mixer : %s\n", Mix_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre
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

    // Création du renderer
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rendu) {
        printf("Erreur création renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Chargement initial
    page = afficher_chargement(rendu);

    // Boucle principale
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
                
            case PAGE_SELECTION_PERSO: {
                // Sauvegarde des sélections précédentes
                SDL_Texture* old_j1[3] = {selections_j1[0], selections_j1[1], selections_j1[2]};
                SDL_Texture* old_j2[3] = {selections_j2[0], selections_j2[1], selections_j2[2]};
                
                page = afficher_selection_perso(rendu, selections_j1, selections_j2, &partie);
                
                if (page == PAGE_CONFIRMATION_PERSO) {
                    page = afficher_confirmation_perso(rendu, selections_j1, selections_j2);
                    
                    // Si on revient à la sélection, restaurer les anciennes sélections
                    if (page == PAGE_SELECTION_PERSO) {
                        for (int i = 0; i < 3; i++) {
                            selections_j1[i] = old_j1[i];
                            selections_j2[i] = old_j2[i];
                        }
                    }
                }
                break;
            }
                
            case PAGE_COMBAT:
                page = afficher_jeu(rendu, selections_j1, selections_j2);
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
                printf("Page inconnue : %d\n", page);
                quit = 1;
                break;
        }
    }

    // Nettoyage
    if (musique_global) {
        Mix_FreeMusic(musique_global);
    }
    
    // Libération des textures de sélection
    for (int i = 0; i < 3; i++) {
        if (selections_j1[i]) SDL_DestroyTexture(selections_j1[i]);
        if (selections_j2[i]) SDL_DestroyTexture(selections_j2[i]);
    }

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}