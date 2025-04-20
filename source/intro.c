#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "intro.h"
#include "page.h"

// Fonction pour centrer une texture
static SDL_Rect centrer_texture(SDL_Texture* texture, SDL_Window* fenetre) {
    int largeur_fenetre, hauteur_fenetre;
    SDL_GetWindowSize(fenetre, &largeur_fenetre, &hauteur_fenetre);
    int largeur_texture, hauteur_texture;
    SDL_QueryTexture(texture, NULL, NULL, &largeur_texture, &hauteur_texture);

    SDL_Rect position = {
        (largeur_fenetre - largeur_texture) / 2,
        (hauteur_fenetre - hauteur_texture) / 2,
        largeur_texture,
        hauteur_texture
    };
    return position;
}

Page afficher_intro(SDL_Renderer* rendu, SDL_Window* fenetre) {
    SDL_Texture* logo = IMG_LoadTexture(rendu, "ressource/image/logo_mym.png");
    if (!logo) {
        SDL_Log("Erreur chargement logo : %s", SDL_GetError());
        return PAGE_MENU;
    }

    Mix_Music* musique = Mix_LoadMUS("ressource/musique/intro.wav");
    if (musique) Mix_PlayMusic(musique, 1);

    Uint32 debut = SDL_GetTicks();
    SDL_Event evenement;

    while (SDL_GetTicks() - debut < 3000) {
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT) {
                SDL_DestroyTexture(logo);
                if (musique) Mix_FreeMusic(musique);
                return PAGE_QUITTER;
            }
        }

        SDL_RenderClear(rendu);
        SDL_Rect position = centrer_texture(logo, fenetre);
        SDL_RenderCopy(rendu, logo, NULL, &position);
        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    SDL_DestroyTexture(logo);
    if (musique) Mix_FreeMusic(musique);
    return PAGE_MENU;
}
