#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "menu.h"
#include "langue.h"
#include "texte.h"
#include "page.h"

#define NB_IMAGES_VIDEO 100
static SDL_Texture* fond_video[NB_IMAGES_VIDEO];

Page afficher_menu(SDL_Renderer* rendu, SDL_Window* fenetre) {
    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 75);
    if (!police) return PAGE_QUITTER;

    SDL_Color rouge = {200, 0, 0};
    SDL_Texture* texte_jouer   = generer_texte_couleur(rendu, get_texte("START"), police, rouge);
    SDL_Texture* texte_options = generer_texte_couleur(rendu, get_texte("OPTIONS"), police, rouge);
    SDL_Texture* texte_quitter = generer_texte_couleur(rendu, get_texte("QUIT"), police, rouge);

    char chemin[128];
    for (int i = 0; i < NB_IMAGES_VIDEO; i++) {
        sprintf(chemin, "ressource/video/frame_menu/frame_%03d.png", i + 1);
        fond_video[i] = IMG_LoadTexture(rendu, chemin);
        if (!fond_video[i]) SDL_Log("Image %03d manquante", i + 1);
    }

    int actif = 1;
    int frame_actuelle = 0;
    Uint32 dernier_tick = SDL_GetTicks();
    SDL_Event event;
    Page prochaine_page = PAGE_MENU;

    while (actif) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return PAGE_QUITTER;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                SDL_Rect r1 = centrer_texte(texte_jouer, fenetre, 150);
                SDL_Rect r2 = centrer_texte(texte_options, fenetre, r1.y + r1.h + 10);
                SDL_Rect r3 = centrer_texte(texte_quitter, fenetre, r2.y + r2.h + 10);

                if (x >= r1.x && x <= r1.x + r1.w && y >= r1.y && y <= r1.y + r1.h)
                    return PAGE_HISTOIRE;

                if (x >= r3.x && x <= r3.x + r3.w && y >= r3.y && y <= r3.y + r3.h)
                    return PAGE_QUITTER;
            }
        }

        if (SDL_GetTicks() - dernier_tick > 100) {
            frame_actuelle = (frame_actuelle + 1) % NB_IMAGES_VIDEO;
            dernier_tick = SDL_GetTicks();
        }

        SDL_RenderClear(rendu);

        // Redimension dynamique du fond à la taille de la fenêtre
        int w, h;
        SDL_GetWindowSize(fenetre, &w, &h);
        SDL_Rect plein_ecran = {0, 0, w, h};

        if (fond_video[frame_actuelle])
            SDL_RenderCopy(rendu, fond_video[frame_actuelle], NULL, &plein_ecran);

        SDL_Rect r1 = centrer_texte(texte_jouer, fenetre, 150);
        SDL_Rect r2 = centrer_texte(texte_options, fenetre, r1.y + r1.h + 10);
        SDL_Rect r3 = centrer_texte(texte_quitter, fenetre, r2.y + r2.h + 10);

        SDL_RenderCopy(rendu, texte_jouer, NULL, &r1);
        SDL_RenderCopy(rendu, texte_options, NULL, &r2);
        SDL_RenderCopy(rendu, texte_quitter, NULL, &r3);

        SDL_RenderPresent(rendu);
        SDL_Delay(1);
    }

    for (int i = 0; i < NB_IMAGES_VIDEO; i++) {
        if (fond_video[i]) SDL_DestroyTexture(fond_video[i]);
    }

    SDL_DestroyTexture(texte_jouer);
    SDL_DestroyTexture(texte_options);
    SDL_DestroyTexture(texte_quitter);
    TTF_CloseFont(police);

    return prochaine_page;
}
