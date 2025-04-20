#ifndef TEXTE_H
#define TEXTE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Déclaration de la fonction
SDL_Texture* generer_texte_couleur(SDL_Renderer* rendu, const char* texte, TTF_Font* police, SDL_Color couleur);

#endif
