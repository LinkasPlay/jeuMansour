#include "texte.h"
#include <SDL2/SDL_ttf.h>

SDL_Texture* generer_texte_couleur(SDL_Renderer* rendu, const char* texte, TTF_Font* police, SDL_Color couleur) {
    SDL_Surface* surface = TTF_RenderText_Blended(police, texte, couleur);
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    return texture;
}
