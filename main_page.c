// Compile       gcc *.c -o run -lSDL2 -lSDL2_image
// Run           ./run

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Error handler
void quit(const char* message) {
    SDL_Log("Error: %s\nSDL_Error: %s", message, SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    exit(1);
}

int main(void) {
    // SDL Init
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        quit("SDL Init failed");
    }

    // SDL_image Init
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        quit("Init PNG failed");
    }

    // Window creation
    SDL_Window* window = SDL_CreateWindow("Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          500, 500, 0);
    if (!window) {
        quit("Window failed");
    }

    // Renderer creation
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        quit("Renderer failed");
    }

    // Load PNG image into a texture
    SDL_Texture* image = IMG_LoadTexture(renderer, "image/start_button.png");
    if (!image) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        quit("Image failed to load");
    }

    // Define position and size of the image
    SDL_Rect dest_rect = {150, 200, 200, 100}; // x, y, width, height

    SDL_Event event;
    int window_loop = 1;

    // Main loop
    while (window_loop) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                window_loop = 0;
            }
        }

        // Rendering
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, image, NULL, &dest_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // 60 FPS
    }

    // Clean up
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
