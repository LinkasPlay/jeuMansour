#include "../Include/fighter.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>

Page afficher_selection_perso(SDL_Renderer* rendu) {
    // --- CHARGEMENT DE L'IMAGE DU CADRE ---
    SDL_Texture* cadre_pp_texture = NULL;
    SDL_Surface* cadre_pp_surface = NULL;

    // Charger le cadre
    cadre_pp_surface = IMG_Load("Ressource/image/Utilité/cadre_pp.png");
    if (!cadre_pp_surface) {
        SDL_Log("Erreur chargement de l'image cadre_pp.png : %s", SDL_GetError());
        return PAGE_QUITTER; // Quitte si l'image ne peut pas être chargée
    } else {
        cadre_pp_texture = SDL_CreateTextureFromSurface(rendu, cadre_pp_surface);
        SDL_FreeSurface(cadre_pp_surface);
        if (!cadre_pp_texture) {
            SDL_Log("Erreur création de la texture du cadre : %s", SDL_GetError());
            return PAGE_QUITTER; // Quitte si la texture ne peut pas être créée
        }
    }

    // --- CHARGEMENT DE L'IMAGE DE FOND ---
    SDL_Texture* fond_texture = IMG_LoadTexture(rendu, "Ressource/image/Fonds/fond_selection_perso.png");
    if (!fond_texture) {
        SDL_Log("Erreur chargement de l'image de fond : %s", SDL_GetError());
        return PAGE_QUITTER; // Quitte si l'image de fond ne peut pas être chargée
    }

    // --- CHARGEMENT PORTRAITS ---
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

    SDL_Texture* portraits[8] = {NULL};

    for (int i = 0; i < 8; i++) {
        portraits[i] = IMG_LoadTexture(rendu, noms_portraits[i]);
        if (!portraits[i]) {
            SDL_Log("Erreur chargement de l'image portrait %d : %s", i, SDL_GetError());
        }
    }

    // Variables de positionnement des portraits
    int largeur_portrait = 200;
    int hauteur_portrait = 200;
    int espacement_x = (LARGEUR_FENETRE - (4 * largeur_portrait)) / 5;
    int espacement_y = (HAUTEUR_FENETRE - 200 - (2 * hauteur_portrait)) / 3;  // Ajusté pour 200px du haut
    int start_x = espacement_x;
    int start_y = 200; // Début à 200px du haut (baisse de 100px)

    SDL_Event event;

    // Affichage de l'écran
    while (1) {
        SDL_RenderClear(rendu);

        // === Affichage de l'image de fond ===
        SDL_RenderCopy(rendu, fond_texture, NULL, NULL);

        // === Affichage des portraits avec le cadre ===
        for (int i = 0; i < 8; i++) {
            int ligne = i / 4;
            int colonne = i % 4;

            start_x = espacement_x + colonne * (largeur_portrait + espacement_x);
            start_y = 200 + ligne * (hauteur_portrait + espacement_y);  // Position à partir de 200px du haut

            SDL_Rect dest = {start_x, start_y, largeur_portrait, hauteur_portrait};
            SDL_RenderCopy(rendu, cadre_pp_texture, NULL, &dest);  // Affichage du cadre
            SDL_RenderCopy(rendu, portraits[i], NULL, &dest);  // Affichage du portrait dans le cadre
        }

        SDL_RenderPresent(rendu);

        // Écoute des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return PAGE_QUITTER;

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Gérer la sélection des personnages ici si besoin
            }
        }
    }
}
