#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "menu.h"

void afficher_menu_simple(SDL_Renderer *rendu) {
    SDL_Surface *fond_surface = IMG_Load("ressource/image/Menu.png");
    SDL_Texture *fond = SDL_CreateTextureFromSurface(rendu, fond_surface);
    SDL_FreeSurface(fond_surface);

    SDL_Surface *cadre_surface = IMG_Load("ressource/image/CadreTitre.png");
    SDL_Texture *cadre_titre = SDL_CreateTextureFromSurface(rendu, cadre_surface);
    SDL_FreeSurface(cadre_surface);

    TTF_Font *police = TTF_OpenFont("ressource/langue/police/arial.ttf", 32);
    SDL_Color blanc = {255, 255, 255, 255};

    int largeur_fenetre, hauteur_fenetre;
    SDL_GetRendererOutputSize(rendu, &largeur_fenetre, &hauteur_fenetre);

    SDL_Rect plein_ecran = {0, 0, largeur_fenetre, hauteur_fenetre};
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, fond, NULL, &plein_ecran);

    // --- CADRE IMAGE AVEC TITRE ---
    int largeur_cadre = 450;
    int hauteur_cadre = 220;
    int x_cadre = (largeur_fenetre - largeur_cadre) / 2;
    int y_cadre = hauteur_fenetre * 0.05;
    SDL_Rect pos_cadre = {x_cadre, y_cadre, largeur_cadre, hauteur_cadre};
    SDL_RenderCopy(rendu, cadre_titre, NULL, &pos_cadre);

    // --- BOUTONS ---
    int largeur_bouton = 320;
    int hauteur_bouton = 70;
    int espacement = 40;
    int x_bouton = (largeur_fenetre - largeur_bouton) / 2;
    int y_depart = y_cadre + hauteur_cadre + 40;

    const char *noms[] = {"Jouer", "Options", "Quitter"};

    for (int i = 0; i < 3; i++) {
        SDL_Rect bouton = {
            x_bouton,
            y_depart + i * (hauteur_bouton + espacement),
            largeur_bouton,
            hauteur_bouton
        };

        // Fond marron cuir
        SDL_SetRenderDrawColor(rendu, 101, 67, 33, 255);
        SDL_RenderFillRect(rendu, &bouton);

        // Cadre clair effet parchemin
        SDL_SetRenderDrawColor(rendu, 200, 160, 100, 255);
        for (int ep = 0; ep < 3; ep++) {
            SDL_Rect bord = {
                bouton.x - ep,
                bouton.y - ep,
                bouton.w + ep * 2,
                bouton.h + ep * 2
            };
            SDL_RenderDrawRect(rendu, &bord);
        }

        // Texte centré
        SDL_Surface *surf = TTF_RenderUTF8_Blended(police, noms[i], blanc);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(rendu, surf);
        SDL_Rect zone_texte = {
            bouton.x + (bouton.w - surf->w) / 2,
            bouton.y + (bouton.h - surf->h) / 2,
            surf->w,
            surf->h
        };

        SDL_FreeSurface(surf);
        SDL_RenderCopy(rendu, tex, NULL, &zone_texte);
        SDL_DestroyTexture(tex);
    }

    SDL_RenderPresent(rendu);

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre_titre);
    TTF_CloseFont(police);
}
