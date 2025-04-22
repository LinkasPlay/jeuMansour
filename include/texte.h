#ifndef TEXTE_H
#define TEXTE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Texture* generer_texte(SDL_Renderer* rendu, const char* texte, TTF_Font* police);
SDL_Texture* generer_texte_couleur(SDL_Renderer* rendu, const char* texte, TTF_Font* police, SDL_Color couleur);
SDL_Rect centrer_texte(SDL_Texture* texture, SDL_Window* fenetre, int y);

#endif
