#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "fighter.h"


// Fonction pour centrer et redimensionner le logo
static SDL_Rect centrer_logo(SDL_Texture* logo, SDL_Window* fenetre, float largeur_max) {
    int largeur_fenetre, hauteur_fenetre;
    SDL_GetWindowSize(fenetre, &largeur_fenetre, &hauteur_fenetre);

    int lw, lh;
    SDL_QueryTexture(logo, NULL, NULL, &lw, &lh);

    int nouvelle_largeur = largeur_fenetre * largeur_max;
    int nouvelle_hauteur = nouvelle_largeur * lh / lw;

    SDL_Rect zone = {
        (largeur_fenetre - nouvelle_largeur) / 2,
        (hauteur_fenetre - nouvelle_hauteur) / 2,
        nouvelle_largeur,
        nouvelle_hauteur
    };
    return zone;
}

Page afficher_intro(SDL_Renderer* rendu, SDL_Window* fenetre) {
    SDL_Texture* logo = IMG_LoadTexture(rendu, "ressource/image/logo_MYMFIGHTERS.png");
    if (!logo) {
        SDL_Log("Erreur chargement logo intro : %s", SDL_GetError());
        return PAGE_MENU;
    }

    Mix_Music* musique = Mix_LoadMUS("ressource/musique/vav/intro.wav");
    if (!musique) {
        SDL_Log("Erreur chargement musique intro : %s", Mix_GetError());
    } 
    else{
        Mix_PlayMusic(musique, 1); // une seule fois
    }

    SDL_Event e;
    int en_cours = 1;

    while (en_cours) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                return PAGE_QUITTER;
        }

        SDL_RenderClear(rendu);

        SDL_Rect position = centrer_logo(logo, fenetre, 0.5f);  // 50% de la largeur écran
        SDL_RenderCopy(rendu, logo, NULL, &position);

        SDL_RenderPresent(rendu);
        SDL_Delay(10);

        // On sort quand la musique est finie
        static int attente_finale = 0;
        static Uint32 temps_fin_musique = 0;

        if (!Mix_PlayingMusic()) {
            if (!attente_finale) {
                attente_finale = 1;
                temps_fin_musique = SDL_GetTicks();
            } 
            else if (SDL_GetTicks() - temps_fin_musique >= 2000) { // attendre 2 secondes
                en_cours = 0;
            }
}

    }

    SDL_DestroyTexture(logo);
    Mix_FreeMusic(musique);
    return PAGE_MENU;
}
