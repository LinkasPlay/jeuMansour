#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


// Center horizontally, fix Y and apply scale
SDL_Rect center_texture(SDL_Texture* tex, SDL_Window* win, int y, float scale) {
    int win_w, win_h;
    SDL_GetWindowSize(win, &win_w, &win_h);

    int tex_w, tex_h;
    SDL_QueryTexture(tex, NULL, NULL, &tex_w, &tex_h);

    int new_w = win_w * scale;
    int new_h = new_w * tex_h / tex_w;

    SDL_Rect rect = {
        (win_w - new_w) / 2,
        y,
        new_w,
        new_h
    };
    return rect;
}

// Error handler
void quit(const char* msg) {
    SDL_Log("Error: %s\nSDL_Error: %s", msg, SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    exit(1);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) quit("SDL Init failed");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) quit("IMG Init failed");

    SDL_Window* win = SDL_CreateWindow("Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);
    if (!win) quit("Window failed");

    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) quit("Renderer failed");

    // Load buttons
    SDL_Texture* start_btn = IMG_LoadTexture(renderer, "image/start_button.png");
    SDL_Texture* settings_btn = IMG_LoadTexture(renderer, "image/setting_button.png");
    SDL_Texture* exit_btn = IMG_LoadTexture(renderer, "image/exit_button.png");
    if (!start_btn || !settings_btn || !exit_btn) quit("Button image load failed");

    // Load video frames
    const int total_frames = 150;
    SDL_Texture* frames[total_frames];
    char path[64];
    for (int i = 0; i < total_frames; i++) {
        sprintf(path, "image/video_frames/frame_%03d.png", i);
        frames[i] = IMG_LoadTexture(renderer, path);
        if (!frames[i]) quit("Failed to load video frame");
    }

    // Loop
    int running = 1;
    SDL_Event event;
    int frame = 0;
    Uint32 last = SDL_GetTicks();
    int spacing = 10; // less gap between buttons
    int start_y = 40; // move everything higher

    // Initializing exit_rect before the loop
    SDL_Rect exit_rect = {500, 300, 100, 50}; // Position initiale de exit_rect

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;

                // Vérifie si on clique dans le bouton exit
                if (mouse_x >= exit_rect.x && mouse_x <= exit_rect.x + exit_rect.w &&
                    mouse_y >= exit_rect.y && mouse_y <= exit_rect.y + exit_rect.h) {
                    running = 0; // Ferme la fenêtre
                }
            }
            
        }

        Uint32 now = SDL_GetTicks();
        if (now - last > 1000 / 30) {
            frame = (frame + 1) % total_frames;
            last = now;
        }

        // Get positions of buttons
        SDL_Rect start_rect = center_texture(start_btn, win, start_y, 0.28f);
        SDL_Rect settings_rect = center_texture(settings_btn, win, start_rect.y + start_rect.h + spacing, 0.28f);

        // Mise à jour de la position de exit_rect après avoir mis à jour settings_rect
        exit_rect = center_texture(exit_btn, win, settings_rect.y + settings_rect.h + spacing, 0.28f);

        // Render
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, frames[frame], NULL, NULL);
        SDL_RenderCopy(renderer, start_btn, NULL, &start_rect);
        SDL_RenderCopy(renderer, settings_btn, NULL, &settings_rect);
        SDL_RenderCopy(renderer, exit_btn, NULL, &exit_rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }

    // Clean
    for (int i = 0; i < total_frames; i++) SDL_DestroyTexture(frames[i]);
    SDL_DestroyTexture(start_btn);
    SDL_DestroyTexture(settings_btn);
    SDL_DestroyTexture(exit_btn);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}