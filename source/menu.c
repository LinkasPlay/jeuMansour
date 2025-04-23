#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "fighter.h"

void afficher_menu(SDL_Renderer *rendu) {
    Mix_Music* musique = Mix_LoadMUS("ressource/musique/menu.wav");
    if (musique) {
        Mix_PlayMusic(musique, -1);
    }

    SDL_Texture *fond = IMG_LoadTexture(rendu, "ressource/image/Menu.png");
    SDL_Texture *cadre_titre = IMG_LoadTexture(rendu, "ressource/image/CadreTitre.png");
    SDL_Texture *fond_bouton = IMG_LoadTexture(rendu, "ressource/image/fond_texte.png");

    int largeur = LARGEUR_FENETRE;
    int hauteur = HAUTEUR_FENETRE;

    SDL_Rect zone_fond = {0, 0, largeur, hauteur};
    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, fond, NULL, &zone_fond);

    // === TITRE collé en haut ===
    const int largeur_titre = 500;
    const int hauteur_titre = 220;
    SDL_Rect zone_titre = {
        (largeur - largeur_titre) / 2,
        0,
        largeur_titre,
        hauteur_titre
    };
    SDL_RenderCopy(rendu, cadre_titre, NULL, &zone_titre);

    // === BOUTONS ===
    const int largeur_bouton = 400;
    const int hauteur_bouton = 190;  // ← agrandi
    const int espacement_apres_titre = 5;  // ← plus rapproché encore
    const int espacement_bouton = 0;

    int x_bouton = (largeur - largeur_bouton) / 2;
    int y_depart = zone_titre.y + zone_titre.h + espacement_apres_titre;

    SDL_Rect bouton_jouer = {x_bouton, y_depart, largeur_bouton, hauteur_bouton};
    SDL_Rect bouton_options = {x_bouton, bouton_jouer.y + hauteur_bouton + espacement_bouton, largeur_bouton, hauteur_bouton};
    SDL_Rect bouton_quitter = {x_bouton, bouton_options.y + hauteur_bouton + espacement_bouton, largeur_bouton, hauteur_bouton};

    SDL_Rect boutons[3] = {bouton_jouer, bouton_options, bouton_quitter};
    const char* textes[] = {"Jouer", "Options", "Quitter"};

    SDL_Color noir = {0, 0, 0, 255};
    TTF_Font *police = TTF_OpenFont("ressource/langue/police/arial.ttf", 40);

    for (int i = 0; i < 3; i++) {
        SDL_RenderCopy(rendu, fond_bouton, NULL, &boutons[i]);

        SDL_Surface* surface_texte = TTF_RenderUTF8_Blended(police, textes[i], noir);
        SDL_Texture* texture_texte = SDL_CreateTextureFromSurface(rendu, surface_texte);

        SDL_Rect zone_texte = {
            boutons[i].x + (boutons[i].w - surface_texte->w) / 2,
            boutons[i].y + (boutons[i].h - surface_texte->h) / 2,
            surface_texte->w,
            surface_texte->h
        };

        SDL_RenderCopy(rendu, texture_texte, NULL, &zone_texte);
        SDL_FreeSurface(surface_texte);
        SDL_DestroyTexture(texture_texte);
    }

    SDL_RenderPresent(rendu);

    TTF_CloseFont(police);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre_titre);
    SDL_DestroyTexture(fond_bouton);
}
