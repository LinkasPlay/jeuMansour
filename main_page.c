// Compile: gcc *.c -o run -lSDL2 -lSDL2_image
// Run:     ./run

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//
// ===================== FUNCTION TO CENTER A RECT =====================
SDL_Rect center_rect(SDL_Texture* texture, SDL_Window* window, int y, float scale) {
    int win_w, win_h;
    SDL_GetWindowSize(window, &win_w, &win_h);

    int tex_w, tex_h;
    SDL_QueryTexture(texture, NULL, NULL, &tex_w, &tex_h);

    int w = win_w * scale;
    int h = w * tex_h / tex_w;

    SDL_Rect rect = {
        (win_w - w) / 2,
        y,
        w,
        h
    };

    return rect;
}

//
// ===================== ERROR HANDLER =====================
void quit(const char* message) {
    SDL_Log("Error: %s\nSDL_Error: %s", message, SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    exit(1);
}

//
// ===================== MAIN =====================
int main(void) {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        quit("SDL Init failed");
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        quit("SDL_image Init failed");
    }

    // Create window and renderer
    SDL_Window* window = SDL_CreateWindow("Menu",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          500, 500,
                                          SDL_WINDOW_RESIZABLE);
    if (!window) quit("Window failed");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_DestroyWindow(window);
        quit("Renderer failed");
    }

    //
    // ===================== LOAD BUTTONS =====================
    SDL_Texture* start_button = IMG_LoadTexture(renderer, "image/start_button.png");
    SDL_Texture* setting_button = IMG_LoadTexture(renderer, "image/setting_button.png");

    if (!start_button || !setting_button) {
        quit("Button image load failed");
    }

    //
    // ===================== LOAD VIDEO FRAMES =====================
    const int total_frames = 300;
    SDL_Texture* frames[total_frames];

    char path[64];
    for (int i = 0; i < total_frames; i++) {
        sprintf(path, "image/video_frames/frame_%03d.png", i);
        frames[i] = IMG_LoadTexture(renderer, path);
        if (!frames[i]) {
            quit("Failed to load video frame");
        }
    }

    //
    // ===================== MAIN LOOP =====================
    int running = 1;
    SDL_Event event;
    int frame = 0;
    Uint32 last_frame_time = SDL_GetTicks();
    int frame_delay = 1000 / 30; // 30 FPS

    while (running) {
        // Events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Update frame if enough time has passed
        Uint32 now = SDL_GetTicks();
        if (now - last_frame_time >= frame_delay) {
            frame = (frame + 1) % total_frames;
            last_frame_time = now;
        }

        // Position buttons
        int gap = 20;
        SDL_Rect start_rect = center_rect(start_button, window, 100, 0.3f);
        SDL_Rect setting_rect = center_rect(setting_button, window, start_rect.y + start_rect.h + gap, 0.3f);

        // Draw background frame
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frames[frame], NULL, NULL); // full screen

        // Draw buttons
        SDL_RenderCopy(renderer, start_button, NULL, &start_rect);
        SDL_RenderCopy(renderer, setting_button, NULL, &setting_rect);
        SDL_RenderPresent(renderer);

        SDL_Delay(1); // tiny delay
    }

    //
    // ===================== CLEANUP =====================
    for (int i = 0; i < total_frames; i++) {
        SDL_DestroyTexture(frames[i]);
    }

    SDL_DestroyTexture(start_button);
    SDL_DestroyTexture(setting_button);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
