#include "../Include/fighter.h"
#include <string.h>

// === PAGE DE SÉLECTION DES PERSONNAGES ===
Page afficher_selection_perso(SDL_Renderer* rendu) {
    SDL_Texture* fond = IMG_LoadTexture(rendu, "Ressource/image/Fonds/fond_selection_perso.png");
    SDL_Texture* bouton_retour = IMG_LoadTexture(rendu, "Ressource/image/Utilité/retour.png");

    if (!fond) {
        SDL_Log("Erreur chargement fond_selection_perso.png : %s", SDL_GetError());
    }
    if (!bouton_retour) {
        SDL_Log("Erreur chargement retour.png : %s", SDL_GetError());
    }

    if (!musique_lancee) {
        musique_global = Mix_LoadMUS("Ressource/musique/Wav/selection_personnages.wav");
        if (musique_global) {
            Mix_VolumeMusic(20);
            Mix_PlayMusic(musique_global, -1);
            musique_lancee = 1;
        } else {
            SDL_Log("Erreur musique sélection personnages : %s", Mix_GetError());
        }
    }

    TTF_Font* police = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 40);
    if (!police) {
        SDL_Log("Erreur chargement police : %s", TTF_GetError());
    }

    SDL_Color blanc = {255, 255, 255, 255};

    SDL_Surface* surf_texte = TTF_RenderUTF8_Blended(police, "Sélectionnez votre personnage", blanc);
    SDL_Texture* texte = SDL_CreateTextureFromSurface(rendu, surf_texte);
    SDL_FreeSurface(surf_texte);

    SDL_Rect zone_texte = { 
        (LARGEUR_FENETRE - 600) / 2, 
        30, 
        600, 
        60 
    };

    SDL_Rect retour = {20, HAUTEUR_FENETRE - 100, 80, 80};

    SDL_Event event;
    while (1) {
        SDL_RenderClear(rendu);

        SDL_RenderCopy(rendu, fond, NULL, NULL);
        SDL_RenderCopy(rendu, texte, NULL, &zone_texte);
        SDL_RenderCopy(rendu, bouton_retour, NULL, &retour);

        SDL_RenderPresent(rendu);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return PAGE_QUITTER;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // ✅ Clic sur le bouton Retour
                if (x >= retour.x && x <= retour.x + retour.w &&
                    y >= retour.y && y <= retour.y + retour.h) {
                    return PAGE_SELEC_MODE; // 🔥 On retourne à la page Choix J1vsJ2 / J1vsIA
                }
            }
        }
    }

    // Code jamais atteint (sécurité)
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(texte);
    SDL_DestroyTexture(bouton_retour);
    TTF_CloseFont(police);

    return PAGE_MENU;
}
