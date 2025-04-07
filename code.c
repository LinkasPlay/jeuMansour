// Pour compiler        gcc code.c -o run -lSDL2
// Pour lancer          ./run
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>




int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO); //Window Init
    if( SDL_Init(SDL_INIT_VIDEO)!=0){//
        SDL_Log("SDL_Error %s",SDL_GetError());
        return 1;
    }
  
    SDL_Window* window = SDL_CreateWindow("Window",SDL_WINDOWPOS_CENTERED
                                                  ,SDL_WINDOWPOS_CENTERED
                                                  ,500,500,0); //Window creation
    

    SDL_Event event;
    int window_loop = 1;
    while(window_loop) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window_loop = 0;
            }
        } //fe
        SDL_Delay(16); // pause = + fluide
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
