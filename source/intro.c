/*
#include "../include/intro.h"

static void renderText(SDL_Renderer* renderer,
                       TTF_font,
                       const char* text,
                       SDL_Color color,
                       int alpha,
                       int x,
                       int y)
    {
        SDL_Color faded = {color.r, color.g, color.b, alpha};
        SDL_Surface* surface= TTF_RenderText_Blender(font, text, faded);
        SDL_Texture* texture= SDL_CreatetextureFromSurface(renderer, surface);
        SDL_Rect dst= {x,y,*surface.w,*surface.h};
        SDL_RenderCopy(renderer, texture, NULL, &dsl);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

void show_intro(SDL_Renderer* renderer,
                TTF_Font* font,
                Mix_Music* music    
                )
                
    {
    SDL_Color white = {255,255,255,255};
    }


//Play the music
if(Mix_PlayMusic(music,1)==-1){
    SDL_Log("Failed to play music %s",Mix_GetError());
}

//Fade-in text

for(int alpha = 0; alpha<=255; alpha+=5){
    SDL_RenderDrawColor(renderer, 0, 0, 0, 255);
}
SDL_RenderClear(renderer);
renderText(renderer, font, "MYM Present",white,alpha,220,250);
SDL
*/



    






