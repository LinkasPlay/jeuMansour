#ifndef TEXTE_H
#define TEXTE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* generer_texte(SDL_Renderer* rendu, const char* texte, TTF_Font* police);

#endif
