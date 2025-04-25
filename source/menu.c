#include "fighter.h"
#include <string.h>

// === CHARGEMENT ===
Page afficher_chargement(SDL_Renderer *rendu) {
    SDL_Surface *image_fond = IMG_Load("ressource/image/Chargement.png");
    SDL_Texture *fond = SDL_CreateTextureFromSurface(rendu, image_fond);
    SDL_FreeSurface(image_fond);

    TTF_Font *police = TTF_OpenFont("ressource/langue/police/arial.ttf", 28);
    SDL_Color blanc = {255, 255, 255, 255};

    SDL_Rect zone_barre = {60, 550, 900, 30};
    SDL_Rect zone_texte = {zone_barre.x, zone_barre.y - 50, 400, 30};

    SDL_Surface *surf_texte = TTF_RenderUTF8_Blended(police, "Chargement en cours...", blanc);
    SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(rendu, surf_texte);
    SDL_FreeSurface(surf_texte);

    int nb_blocs = 50, marge = 2;
    int largeur_bloc = (zone_barre.w - (nb_blocs - 1) * marge) / nb_blocs;

    for (int i = 0; i <= nb_blocs; i++) {
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, fond, NULL, NULL);
        SDL_RenderCopy(rendu, texture_texte, NULL, &zone_texte);
        SDL_SetRenderDrawColor(rendu, 255, 220, 0, 255);
        for (int j = 0; j < i; j++) {
            SDL_Rect bloc = { zone_barre.x + j * (largeur_bloc + marge), zone_barre.y, largeur_bloc, zone_barre.h };
            SDL_RenderFillRect(rendu, &bloc);
        }
        SDL_RenderPresent(rendu);
        SDL_Delay(20);
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(texture_texte);
    TTF_CloseFont(police);
    return PAGE_HISTOIRE;
}
Page afficher_histoire(SDL_Renderer* rendu) {
    #define NB_PHRASES 5

    const char* phrases[NB_PHRASES] = {
        "Dans un monde divisé par les royaumes...",
        "Un phénomène étrange a bouleversé l’équilibre.",
        "Les artefacts Shōnen refont surface...",
        "Toi, jeune combattant, relèveras-tu le défi ?",
        "Bienvenue dans Project Shōnen Smash."
    };

    char affichage[NB_PHRASES][256] = {{0}};
    int lettres[NB_PHRASES] = {0};

    // Charger les frames d'arrière-plan
    const int NB_FRAMES = 99;
    SDL_Texture* frames[NB_FRAMES];
    char chemin[128];
    for (int i = 1; i <= NB_FRAMES; i++) {
        sprintf(chemin, "ressource/video/frame_histoire/frame_%03d.png", i);
        SDL_Surface* surf = IMG_Load(chemin);
        if (surf) {
            frames[i - 1] = SDL_CreateTextureFromSurface(rendu, surf);
            SDL_FreeSurface(surf);
        } else {
            frames[i - 1] = NULL;
        }
    }

    // Police et couleur
    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 32);
    SDL_Color blanc = {255, 255, 255, 255};

    // Bouton Flash Skip
    SDL_Texture* skip_btn = IMG_LoadTexture(rendu, "ressource/image/Flash Skip.png");
    SDL_Rect skip_rect = {LARGEUR_FENETRE - 120, 20, 80, 80};

    if (!skip_btn) {
        SDL_Log("ERREUR: Impossible de charger 'Flash Skip.png' : %s", SDL_GetError());
    }

    Uint32 last_char = SDL_GetTicks();
    SDL_Event event;
    int phrase = 0;

    while (phrase < NB_PHRASES) {
        Uint32 now = SDL_GetTicks();
        int frame = (now / 33) % NB_FRAMES;

        if (lettres[phrase] < strlen(phrases[phrase]) && now - last_char > 40) {
            lettres[phrase]++;
            last_char = now;
            strncpy(affichage[phrase], phrases[phrase], lettres[phrase]);
            affichage[phrase][lettres[phrase]] = '\0';
        }

        SDL_RenderClear(rendu);
        if (frames[frame]) SDL_RenderCopy(rendu, frames[frame], NULL, NULL);
        else SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255), SDL_RenderClear(rendu);

        for (int i = 0; i <= phrase; i++) {
            if (lettres[i] > 0) {
                SDL_Surface* surf = TTF_RenderUTF8_Blended(police, affichage[i], blanc);
                if (surf) {
                    SDL_Texture* tex = SDL_CreateTextureFromSurface(rendu, surf);
                    SDL_Rect rect = {
                        (LARGEUR_FENETRE - surf->w) / 2,
                        60 + i * 80,
                        surf->w,
                        surf->h
                    };
                    SDL_RenderCopy(rendu, tex, NULL, &rect);
                    SDL_FreeSurface(surf);
                    SDL_DestroyTexture(tex);
                }
            }
        }

        // Afficher le bouton skip s'il est chargé
        if (skip_btn) {
            SDL_RenderCopy(rendu, skip_btn, NULL, &skip_rect);
        } else {
            // Alternative visible : rectangle rouge si image manquante
            SDL_SetRenderDrawColor(rendu, 255, 0, 0, 255);
            SDL_RenderFillRect(rendu, &skip_rect);
        }

        SDL_RenderPresent(rendu);

        if (lettres[phrase] == strlen(phrases[phrase])) {
            SDL_Delay(1000);
            phrase++;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return PAGE_QUITTER;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= skip_rect.x && x <= skip_rect.x + skip_rect.w &&
                    y >= skip_rect.y && y <= skip_rect.y + skip_rect.h)
                    return PAGE_MENU;
            }
        }
    }

    for (int i = 0; i < NB_FRAMES; i++) if (frames[i]) SDL_DestroyTexture(frames[i]);
    if (skip_btn) SDL_DestroyTexture(skip_btn);
    TTF_CloseFont(police);
    return PAGE_MENU;
}


// === MENU PRINCIPAL ===
Page afficher_menu(SDL_Renderer* rendu) {
    Mix_Music* musique = Mix_LoadMUS("ressource/musique/menu.wav");
    if (musique) Mix_PlayMusic(musique, -1);

    SDL_Texture* fond = IMG_LoadTexture(rendu, "ressource/image/Menu.png");
    SDL_Texture* cadre_titre = IMG_LoadTexture(rendu, "ressource/image/CadreTitre.png");
    SDL_Texture* cadre_bouton = IMG_LoadTexture(rendu, "ressource/image/fond_texte.png");

    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 40);
    SDL_Color noir = {0, 0, 0, 255};

    SDL_Rect zone_titre = {262, 0, 500, 250};
    SDL_Rect boutons[3] = {
        {370, 160, 280, 190},
        {370, 280, 280, 190},
        {370, 400, 280, 190}
    };
    const char* textes[] = {"Jouer", "Options", "Quitter"};

    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, fond, NULL, NULL);
    SDL_RenderCopy(rendu, cadre_titre, NULL, &zone_titre);

    for (int i = 0; i < 3; i++) {
        SDL_RenderCopy(rendu, cadre_bouton, NULL, &boutons[i]);
        SDL_Surface* surf = TTF_RenderUTF8_Blended(police, textes[i], noir);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(rendu, surf);
        SDL_Rect txt = {
            boutons[i].x + (boutons[i].w - surf->w) / 2,
            boutons[i].y + (boutons[i].h - surf->h) / 2,
            surf->w, surf->h
        };
        SDL_RenderCopy(rendu, tex, NULL, &txt);
        SDL_FreeSurface(surf);
        SDL_DestroyTexture(tex);
    }

    SDL_RenderPresent(rendu);

    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return PAGE_QUITTER;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= boutons[0].x && x <= boutons[0].x + boutons[0].w && y >= boutons[0].y && y <= boutons[0].y + boutons[0].h) return PAGE_HISTOIRE;
                if (x >= boutons[1].x && x <= boutons[1].x + boutons[1].w && y >= boutons[1].y && y <= boutons[1].y + boutons[1].h) return PAGE_OPTIONS;
                if (x >= boutons[2].x && x <= boutons[2].x + boutons[2].w && y >= boutons[2].y && y <= boutons[2].y + boutons[2].h) return PAGE_QUITTER;
            }
        }
    }

    TTF_CloseFont(police);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre_titre);
    SDL_DestroyTexture(cadre_bouton);
    return PAGE_MENU;
}
Page afficher_options(SDL_Renderer* rendu, Page page_prec) {
    SDL_Texture* fond = IMG_LoadTexture(rendu, "ressource/image/Menu.png");
    SDL_Texture* cadre_bouton = IMG_LoadTexture(rendu, "ressource/image/fond_texte.png");
    SDL_Texture* bouton_retour = IMG_LoadTexture(rendu, "ressource/image/Retour.png");

    const char* textes[] = {"Sauvegarde", "Langue", "Son"};
    SDL_Color noir = {0, 0, 0, 255};
    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 40);

    SDL_Rect boutons[3] = {
        {370, 160, 280, 190},
        {370, 280, 280, 190},
        {370, 400, 280, 190}
    };
    SDL_Rect retour_rect = {20, HAUTEUR_FENETRE - 100, 80, 80};

    SDL_Event event;
    while (1) {
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, fond, NULL, NULL);

        for (int i = 0; i < 3; i++) {
            SDL_RenderCopy(rendu, cadre_bouton, NULL, &boutons[i]);
            SDL_Surface* surf = TTF_RenderUTF8_Blended(police, textes[i], noir);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(rendu, surf);
            SDL_Rect txt = {
                boutons[i].x + (boutons[i].w - surf->w) / 2,
                boutons[i].y + (boutons[i].h - surf->h) / 2,
                surf->w, surf->h
            };
            SDL_RenderCopy(rendu, tex, NULL, &txt);
            SDL_FreeSurface(surf);
            SDL_DestroyTexture(tex);
        }

        SDL_RenderCopy(rendu, bouton_retour, NULL, &retour_rect);
        SDL_RenderPresent(rendu);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return PAGE_QUITTER;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= retour_rect.x && x <= retour_rect.x + retour_rect.w &&
                    y >= retour_rect.y && y <= retour_rect.y + retour_rect.h)
                    return page_prec;
            }
        }
    }

    TTF_CloseFont(police);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(cadre_bouton);
    SDL_DestroyTexture(bouton_retour);
    return PAGE_MENU;
}
