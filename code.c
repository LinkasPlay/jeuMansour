// Pour compiler        gcc code.c -o run -lSDL2
// Pour lancer          ./run
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlid.h>

//printf("yo");



int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* fenetre = SDL_CreateWindow("Ma fenêtre",SDL_WINDOWPOS_CENTERED
                                                            ,SDL_WINDOWPOS_CENTERED,500,500,0);

    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        } //fe
        SDL_Delay(16); // pause = + fluide
    }

    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}
