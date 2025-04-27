#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//test
#include "fighter.h"


SDL_Texture* generer_texte(SDL_Renderer* rendu, const char* texte, TTF_Font* police) {
    SDL_Color blanc = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(police, texte, blanc);
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Texture* generer_texte_couleur(SDL_Renderer* rendu, const char* texte, TTF_Font* police, SDL_Color couleur) {
    SDL_Surface* surface = TTF_RenderText_Blended(police, texte, couleur);
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    return texture;
}

SDL_Rect centrer_texte(SDL_Texture* texture, SDL_Window* fenetre, int y) {
    int largeur_fenetre;
    SDL_GetWindowSize(fenetre, &largeur_fenetre, NULL);

    int largeur_texte, hauteur_texte;
    SDL_QueryTexture(texture, NULL, NULL, &largeur_texte, &hauteur_texte);

    SDL_Rect position = {
        (largeur_fenetre - largeur_texte) / 2,
        y,
        largeur_texte,
        hauteur_texte
    };
    return position;
}
