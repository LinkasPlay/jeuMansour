#include "../Include/fighter.h"
#include <string.h>
#include <time.h>

// === VARIABLE GLOBALE POUR LA MUSIQUE ===
Mix_Music* musique_global = NULL;
int musique_lancee = 0;

// === CHARGEMENT ===
Page afficher_chargement(SDL_Renderer *rendu) {
    SDL_Surface *image_fond = IMG_Load("Ressource/image/Fonds/fond_chargement.png");
    SDL_Texture *fond = SDL_CreateTextureFromSurface(rendu, image_fond);
    SDL_FreeSurface(image_fond);

    TTF_Font *police = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 28);
    SDL_Color blanc = {255, 255, 255, 255};

    // === CADRE DE TITRE SEUL ===

    SDL_Rect zone_barre = {60, 500, 900, 30};
    SDL_Rect zone_texte = {zone_barre.x, zone_barre.y + 40, 400, 30};

    SDL_Surface *surf_texte = TTF_RenderUTF8_Blended(police, "Chargement en cours...", blanc);
    SDL_Texture *texture_texte = SDL_CreateTextureFromSurface(rendu, surf_texte);
    SDL_FreeSurface(surf_texte);

    int nb_blocs = 50, marge = 2;
    int largeur_bloc = (zone_barre.w - (nb_blocs - 1) * marge) / nb_blocs;

    for (int i = 0; i <= nb_blocs; i++) {
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, fond, NULL, NULL);

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
//fzfes
        SDL_RenderCopy(rendu, texture_texte, NULL, &zone_texte);
        SDL_RenderPresent(rendu);

        if (i > nb_blocs * 0.95)
            SDL_Delay(300);
        else if (i > nb_blocs * 0.85)
            SDL_Delay(150);
        else if (i > nb_blocs * 0.6)
            SDL_Delay(50);
        else
            SDL_Delay(20);
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(texture_texte);
    TTF_CloseFont(police);
    return PAGE_HISTOIRE;
}




// === HISTOIRE ===
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

    SDL_Texture* fond = IMG_LoadTexture(rendu, "Ressource/image/Fonds/fond_histoire.png");

    TTF_Font* police = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 32);
    SDL_Color blanc = {255, 255, 255, 255};

    SDL_Texture* skip_btn = IMG_LoadTexture(rendu, "Ressource/image/Utilité/avance.png");
    SDL_Rect skip_rect = {LARGEUR_FENETRE - 120, 20, 80, 80};

    Mix_Chunk* son_phrase = Mix_LoadWAV("Ressource/musique/Wav/phrase.wav");
    if (!son_phrase) SDL_Log("ERREUR chargement son phrase : %s", Mix_GetError());

    Uint32 last_char = SDL_GetTicks();
    SDL_Event event;
    int phrase = 0;

    while (phrase < NB_PHRASES) {
        Uint32 now = SDL_GetTicks();

        if (lettres[phrase] < strlen(phrases[phrase]) && now - last_char > 40) {
            lettres[phrase]++;
            last_char = now;
            memset(affichage[phrase], 0, sizeof(affichage[phrase]));
            strncpy(affichage[phrase], phrases[phrase], lettres[phrase]);

            if (lettres[phrase] == 1 && son_phrase) {
                int volume = 30 + rand() % 35;
                Mix_VolumeChunk(son_phrase, volume);
                Mix_PlayChannel(-1, son_phrase, 0);
            }
        }

        SDL_RenderClear(rendu);
        if (fond) SDL_RenderCopy(rendu, fond, NULL, NULL);

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

        if (skip_btn) SDL_RenderCopy(rendu, skip_btn, NULL, &skip_rect);
        SDL_RenderPresent(rendu);

        if (lettres[phrase] == strlen(phrases[phrase])) {
            SDL_Delay(1000);
            phrase++;
        }

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return PAGE_QUITTER;
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x, y = event.button.y;
                if (x >= skip_rect.x && x <= skip_rect.x + skip_rect.w &&
                    y >= skip_rect.y && y <= skip_rect.y + skip_rect.h) {
                    Mix_HaltChannel(-1);
                    return PAGE_MENU;
                }
            }
        }
    }

    if (fond) SDL_DestroyTexture(fond);
    if (skip_btn) SDL_DestroyTexture(skip_btn);
    if (son_phrase) Mix_FreeChunk(son_phrase);
    TTF_CloseFont(police);

    return PAGE_MENU;
}

// === LECTEUR DE MUSIQUE GLOBAL ===
void jouer_musique(const char* chemin, int volume) {
    if (musique_lancee) return;

    musique_global = Mix_LoadMUS(chemin);
    if (musique_global) {
        Mix_VolumeMusic(volume);
        Mix_PlayMusic(musique_global, -1);
        musique_lancee = 1;
    } else {
        printf("Erreur musique : %s\n", Mix_GetError());
    }
}

// === MENU PRINCIPAL ===
Page afficher_menu(SDL_Renderer* rendu) {
    jouer_musique("Ressource/musique/Wav/menu.wav", 20);

    SDL_Texture* fond = IMG_LoadTexture(rendu, "Ressource/image/Fonds/fond_menu.png");
    SDL_Texture* cadre_titre = IMG_LoadTexture(rendu, "Ressource/image/Cadres/cadre_titre.png");
    SDL_Texture* cadre_bouton = IMG_LoadTexture(rendu, "Ressource/image/Cadres/cadre_texte.png");

    TTF_Font* police = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 40);
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
            surf->w,
            surf->h
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

                if (x >= boutons[0].x && x <= boutons[0].x + boutons[0].w &&
                    y >= boutons[0].y && y <= boutons[0].y + boutons[0].h)
                    return PAGE_JEU;

                if (x >= boutons[1].x && x <= boutons[1].x + boutons[1].w &&
                    y >= boutons[1].y && y <= boutons[1].y + boutons[1].h)
                    return PAGE_OPTIONS;

                if (x >= boutons[2].x && x <= boutons[2].x + boutons[2].w &&
                    y >= boutons[2].y && y <= boutons[2].y + boutons[2].h)
                    return PAGE_QUITTER;
            }
        }
    }

    return PAGE_MENU;
}

// === OPTIONS ===
Page afficher_options(SDL_Renderer* rendu, Page page_prec) {
    SDL_Texture* fond = IMG_LoadTexture(rendu, "Ressource/image/Fonds/fond_menu.png");
    SDL_Texture* cadre_bouton = IMG_LoadTexture(rendu, "Ressource/image/Cadres/cadre_texte.png");
    SDL_Texture* bouton_retour = IMG_LoadTexture(rendu, "Ressource/image/Utilité/retour.png");

    const char* textes[] = {"Sauvegarde", "Langue", "Son"};
    SDL_Color noir = {0, 0, 0, 255};
    TTF_Font* police = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 40);

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
                surf->w,
                surf->h
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
}

// === PAGE DE JEU ===
Page afficher_jeu(SDL_Renderer* rendu) {
    SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
    SDL_RenderClear(rendu);

    TTF_Font* police = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 40);
    SDL_Color blanc = {255, 255, 255, 255};
    SDL_Surface* surf = TTF_RenderUTF8_Blended(police, "JEU EN COURS...", blanc);
    SDL_Texture* texte = SDL_CreateTextureFromSurface(rendu, surf);

    SDL_Rect rect = {
        (LARGEUR_FENETRE - surf->w) / 2,
        (HAUTEUR_FENETRE - surf->h) / 2,
        surf->w,
        surf->h
    };

    SDL_RenderCopy(rendu, texte, NULL, &rect);
    SDL_RenderPresent(rendu);

    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texte);
    TTF_CloseFont(police);

    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return PAGE_QUITTER;
            if (event.type == SDL_MOUSEBUTTONDOWN) return PAGE_MENU;
        }
    }
}
