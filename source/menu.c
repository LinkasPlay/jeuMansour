#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "fighter.h"

void afficher_menu_simple(SDL_Renderer *rendu) {
    // Musique du menu (chargée directement en WAV, pas avec une fonction)
    Mix_Music* musique = Mix_LoadMUS("ressource/musique/wav/menu.wav");
    if (!musique) {
        SDL_Log("Erreur chargement musique : %s", Mix_GetError());
    } else {
        Mix_PlayMusic(musique, -1); // -1 = boucle infinie
    }

    // Fond du menu
    SDL_Texture *fond = IMG_LoadTexture(rendu, "ressource/image/Menu.png");

    // Cadre du titre
    SDL_Texture *cadre_titre = IMG_LoadTexture(rendu, "ressource/image/CadreTitre.png");

    TTF_Font *police = TTF_OpenFont("ressource/langue/police/arial.ttf", 80);
    SDL_Color blanc = {255, 255, 255, 255};

    int largeur, hauteur;
    SDL_GetRendererOutputSize(rendu, &largeur, &hauteur);

    SDL_Rect plein_ecran = {0, 0, largeur, hauteur};
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, fond, NULL, &plein_ecran);

    // Titre
    SDL_Rect rect_titre = {
        (largeur - 450) / 2,
        hauteur * 0.05,
        450,
        220
    };
    SDL_RenderCopy(rendu, cadre_titre, NULL, &rect_titre);

    // Boutons
    int largeur_btn = 320;
    int hauteur_btn = 70;
    int espacement = 40;
    int x_btn = (largeur - largeur_btn) / 2;
    int y_base = rect_titre.y + rect_titre.h + 40;

    const char *noms[] = {"Jouer", "Options", "Quitter"};

    for (int i = 0; i < 3; i++) {
        SDL_Rect btn = {
            x_btn,
            y_base + i * (hauteur_btn + espacement),
            largeur_btn,
            hauteur_btn
        };

        SDL_SetRenderDrawColor(rendu, 101, 67, 33, 255);
        SDL_RenderFillRect(rendu, &btn);

        SDL_SetRenderDrawColor(rendu, 200, 160, 100, 255);
        for (int ep = 0; ep < 3; ep++) {
            SDL_Rect bord = {
                btn.x - ep,
                btn.y - ep,
                btn.w + ep * 2,
                btn.h + ep * 2
            };
            SDL_RenderDrawRect(rendu, &bord);
        }

        SDL_Surface *surf = TTF_RenderUTF8_Blended(police, noms[i], blanc);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(rendu, surf);
        SDL_Rect txt_rect = {
            btn.x + (btn.w - surf->w) / 2,
            btn.y + (btn.h - surf->h) / 2,
            surf->w,
            surf->h
        };
        SDL_FreeSurface(surf);
        SDL_RenderCopy(rendu, tex, NULL, &txt_rect);
        SDL_DestroyTexture(tex);
    }

    SDL_RenderPresent(rendu);

    // Libération mémoire
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre_titre);
    TTF_CloseFont(police);
}
