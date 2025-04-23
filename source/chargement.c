#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "fighter.h"

void afficher_chargement(SDL_Renderer *rendu) {
    SDL_Surface *image_fond = IMG_Load("ressource/image/Chargement.png");
    SDL_Texture *fond = SDL_CreateTextureFromSurface(rendu, image_fond);
    SDL_FreeSurface(image_fond);

    TTF_Font *police = TTF_OpenFont("ressource/langue/police/arial.ttf", 28);  // texte normal
    TTF_Font *police_grasse = TTF_OpenFont("ressource/langue/police/arial.ttf", 34); // texte gras simulé
    SDL_Color blanc = {255, 255, 255, 255};

    SDL_Rect zone_barre = {60, 550, 900, 30};
    SDL_Rect zone_texte = {zone_barre.x, zone_barre.y - 50, 400, 30};

    SDL_Surface *surf_texte = TTF_RenderUTF8_Blended(police, "Chargement en cours...", blanc);
    SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(rendu, surf_texte);
    SDL_FreeSurface(surf_texte);

    int nb_blocs = 50;
    int marge = 2;
    int largeur_bloc = (zone_barre.w - (nb_blocs - 1) * marge) / nb_blocs;

    for (int i = 0; i <= nb_blocs; i++) {
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, fond, NULL, NULL);
        SDL_RenderCopy(rendu, texture_texte, NULL, &zone_texte);

        // Cadre noir
        SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
        for (int epaisseur = 0; epaisseur < 2; epaisseur++) {
            SDL_Rect contour = {
                zone_barre.x - epaisseur,
                zone_barre.y - epaisseur,
                zone_barre.w + epaisseur * 2,
                zone_barre.h + epaisseur * 2
            };
            SDL_RenderDrawRect(rendu, &contour);
        }

        // Blocs jaunes remplis
        SDL_SetRenderDrawColor(rendu, 255, 220, 0, 255);
        for (int j = 0; j < i; j++) {
            SDL_Rect bloc = {
                zone_barre.x + j * (largeur_bloc + marge),
                zone_barre.y,
                largeur_bloc,
                zone_barre.h
            };
            SDL_RenderFillRect(rendu, &bloc);
        }

        // Afficher le pourcentage centré en "gras"
        int pourcentage = (i * 100) / nb_blocs;
        char texte_pourcentage[8];
        sprintf(texte_pourcentage, "%d%%", pourcentage);
        SDL_Surface *surf_pct = TTF_RenderUTF8_Blended(police_grasse, texte_pourcentage, blanc);
        SDL_Texture *tex_pct = SDL_CreateTextureFromSurface(rendu, surf_pct);

        SDL_Rect zone_pct;
        zone_pct.w = surf_pct->w;
        zone_pct.h = surf_pct->h;
        zone_pct.x = zone_barre.x + (zone_barre.w - zone_pct.w) / 2;
        zone_pct.y = zone_barre.y + (zone_barre.h - zone_pct.h) / 2;

        SDL_FreeSurface(surf_pct);
        SDL_RenderCopy(rendu, tex_pct, NULL, &zone_pct);
        SDL_DestroyTexture(tex_pct);

        SDL_RenderPresent(rendu);
        SDL_Delay(5);
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(texture_texte);
    TTF_CloseFont(police);
    TTF_CloseFont(police_grasse);
}