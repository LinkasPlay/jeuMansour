// intro.h

#ifndef INTRO_H
#define INTRO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Function to show the intro with text and music
void show_intro(SDL_Renderer* renderer, TTF_Font* font, Mix_Music* music);

#endif
