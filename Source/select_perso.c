#include "../Include/fighter.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>

// === PAGE DE SÉLECTION DES PERSONNAGES ===

Page afficher_selection_perso(SDL_Renderer* rendu) {
    // --- CHARGEMENTS ---
    SDL_Texture* fond = IMG_LoadTexture(rendu, "Ressource/image/Fonds/fond_selection_perso.png");
    SDL_Texture* bouton_retour = IMG_LoadTexture(rendu, "Ressource/image/Utilité/retour.png");
    SDL_Texture* bouton_continuer = IMG_LoadTexture(rendu, "Ressource/image/Utilité/avance.png");

    if (!fond || !bouton_retour || !bouton_continuer) {
        SDL_Log("Erreur chargement textures de base : %s", SDL_GetError());
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

    SDL_Rect zone_texte = {(LARGEUR_FENETRE - 600) / 2, 30, 600, 60};
    SDL_Rect retour = {20, HAUTEUR_FENETRE - 100, 80, 80};
    SDL_Rect continuer = {120, HAUTEUR_FENETRE - 100, 80, 80};

    // --- CHARGEMENT PORTRAITS + SPRITES PIXELS ---
    const char* noms_portraits[8] = {
        "Ressource/image/Personnages_pp/pp_droite/pp_darkshadow.png",
        "Ressource/image/Personnages_pp/pp_droite/pp_hitsugaya.png",
        "Ressource/image/Personnages_pp/pp_droite/pp_incassable.png",
        "Ressource/image/Personnages_pp/pp_droite/pp_katara.png",
        "Ressource/image/Personnages_pp/pp_droite/pp_kirua.png",
        "Ressource/image/Personnages_pp/pp_droite/pp_rengoku.png",
        "Ressource/image/Personnages_pp/pp_droite/pp_temari.png",
        "Ressource/image/Personnages_pp/pp_droite/pp_zoro.png"
    };

    const char* noms_pixels[8] = {
        "Ressource/image/Personnages_pixel/darkShadow.png",
        "Ressource/image/Personnages_pixel/hitsugaya.png",
        "Ressource/image/Personnages_pixel/incassable.png",
        "Ressource/image/Personnages_pixel/katara.png",
        "Ressource/image/Personnages_pixel/kirua.png",
        "Ressource/image/Personnages_pixel/kengoku.png",
        "Ressource/image/Personnages_pixel/temari.png",
        "Ressource/image/Personnages_pixel/zoro.png"
    };

    SDL_Texture* portraits[8] = {NULL};
    SDL_Texture* sprites[8] = {NULL};

    for (int i = 0; i < 8; i++) {
        portraits[i] = IMG_LoadTexture(rendu, noms_portraits[i]);
        sprites[i] = IMG_LoadTexture(rendu, noms_pixels[i]);
    }

    // === Variables de sélection ===
    int selection[2] = {-1, -1};
    int joueur_courant = rand() % 2; // 0 ou 1 random
    bool selection_active = false;
    int perso_selectionne = -1;
    bool tous_selectionnes = false;

    SDL_Event event;

    // === Variables de positionnement des portraits ===
    int ligne, colonne;  // Déclare les variables ici avant la boucle
    int largeur_portrait = 200;  // Taille des portraits
    int hauteur_portrait = 200;  // Taille des portraits
    int espacement_x = (LARGEUR_FENETRE - (4 * largeur_portrait)) / 5;  // Espacement horizontal
    int espacement_y = (HAUTEUR_FENETRE - (zone_texte.y + zone_texte.h) - 100 - (2 * hauteur_portrait)) / 3;  // Espacement vertical
    int start_x = espacement_x;  // Début des portraits horizontalement
    int start_y = zone_texte.y + zone_texte.h + 100;  // Début des portraits après le texte et à 100px vers le bas

    while (1) {
        SDL_RenderClear(rendu);

        // Afficher fond + texte
        SDL_RenderCopy(rendu, fond, NULL, NULL);
        SDL_RenderCopy(rendu, texte, NULL, &zone_texte);

        // === Affichage des portraits ===
        for (int i = 0; i < 8; i++) {
            ligne = i / 4;  // Calcul de la ligne
            colonne = i % 4;  // Calcul de la colonne
            
            start_x = espacement_x + colonne * (largeur_portrait + espacement_x);
            start_y = zone_texte.y + zone_texte.h + 100 + ligne * (hauteur_portrait + espacement_y);  // 100px vers le bas

            SDL_Rect dest = {start_x, start_y, largeur_portrait, hauteur_portrait};
            SDL_RenderCopy(rendu, portraits[i], NULL, &dest);
        }

        // === Affichage sprite pixel + description ===
        if (selection_active && perso_selectionne != -1) {
            SDL_Rect grand_sprite = {LARGEUR_FENETRE / 2 + 100, 250, 300, 300};
            SDL_RenderCopy(rendu, sprites[perso_selectionne], NULL, &grand_sprite);

            // (optionnel : afficher cadre texte avec description du perso ici)
        }

        // Affichage boutons
        SDL_RenderCopy(rendu, bouton_retour, NULL, &retour);
        if (selection_active) {
            SDL_RenderCopy(rendu, bouton_continuer, NULL, &continuer);
        }

        SDL_RenderPresent(rendu);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return PAGE_QUITTER;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                // Bouton retour
                if (x >= retour.x && x <= retour.x + retour.w && y >= retour.y && y <= retour.y + retour.h) {
                    return PAGE_SELEC_MODE;
                }

                // Bouton continuer
                if (selection_active && x >= continuer.x && x <= continuer.x + continuer.w && y >= continuer.y && y <= continuer.y + continuer.h) {
                    selection[joueur_courant] = perso_selectionne;
                    selection_active = false;
                    perso_selectionne = -1;

                    if (selection[0] != -1 && selection[1] != -1) {
                        tous_selectionnes = true;
                    } else {
                        joueur_courant = 1 - joueur_courant; // Changer joueur
                    }
                }

                // Sélection d'un portrait
                if (!selection_active) {
                    for (int i = 0; i < 8; i++) {
                        if (selection[0] == i || selection[1] == i) continue;

                        ligne = i / 4;
                        colonne = i % 4;
                        SDL_Rect dest = {start_x + colonne * (largeur_portrait + espacement_x), start_y + ligne * (hauteur_portrait + espacement_y), largeur_portrait, hauteur_portrait};

                        if (x >= dest.x && x <= dest.x + dest.w && y >= dest.y && y <= dest.y + dest.h) {
                            perso_selectionne = i;
                            selection_active = true;
                        }
                    }
                }
            }
        }

        if (tous_selectionnes) {
            // Libérer textures
            SDL_DestroyTexture(fond);
            SDL_DestroyTexture(texte);
            SDL_DestroyTexture(bouton_retour);
            SDL_DestroyTexture(bouton_continuer);
            for (int i = 0; i < 8; i++) {
                SDL_DestroyTexture(portraits[i]);
                SDL_DestroyTexture(sprites[i]);
            }
            TTF_CloseFont(police);

            return PAGE_JEU;
        }
    }
}
