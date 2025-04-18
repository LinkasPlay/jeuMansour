#include "texte.h"
#include <SDL2/SDL_ttf.h>

SDL_Texture* generer_texte(SDL_Renderer* rendu, const char* texte, TTF_Font* police) {
    SDL_Color blanc = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(police, texte, blanc);
    if (!surface) return NULL;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_FreeSurface(surface);
    return texture;
}
