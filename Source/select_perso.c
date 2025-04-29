#include "../Include/fighter.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>

Page afficher_selection_perso(SDL_Renderer* rendu) {
    // --- CHARGEMENT DES TEXTURES ---
    SDL_Texture* fond_texture = IMG_LoadTexture(rendu, "Ressource/image/Fonds/fond_selection_perso.png");
    if (!fond_texture) {
        SDL_Log("Erreur chargement fond: %s", SDL_GetError());
        return PAGE_QUITTER;
    }

    // --- LOGO VERSUS ---
    SDL_Texture* logo_versus_texture = IMG_LoadTexture(rendu, "Ressource/image/Utilité/versus.png");
    SDL_Rect dest_logo = {
        (LARGEUR_FENETRE - 80) / 2,
        10,
        80,
        80
    };

    // --- PORTRAITS DES PERSONNAGES ---
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

    SDL_Texture* portraits[8];
    bool perso_disponible[8] = {true, true, true, true, true, true, true, true}; // Tous disponibles au départ

    for (int i = 0; i < 8; i++) {
        portraits[i] = IMG_LoadTexture(rendu, noms_portraits[i]);
        if (!portraits[i]) {
            SDL_Log("Erreur chargement portrait %d: %s", i, SDL_GetError());
        }
    }

    // --- GESTION DE LA SELECTION (3 MAX) ---
    SDL_Texture* selections_j1[3] = {NULL, NULL, NULL};
    SDL_Texture* selections_j2[3] = {NULL, NULL, NULL};
    int nb_selections_j1 = 0;
    int nb_selections_j2 = 0;
    bool tour_j1 = true; // Commence avec J1

    // --- POSITIONNEMENT DES PERSOS ---
    const int largeur_perso = 150;
    const int hauteur_perso = 150;
    const int espacement_x = (LARGEUR_FENETRE - 4*largeur_perso) / 5;
    const int espacement_y = 50;
    const int start_y_persos = HAUTEUR_FENETRE - hauteur_perso - espacement_y;

    // --- MINI-PORTRAITS SELECTIONNES ---
    const int mini_size = 80;
    const int marge_haut = 20;
    const int marge_cote = 50;
    const int espacement_selections = 10;

    // --- TEXTE TOUR ---
    TTF_Font* police = TTF_OpenFont("Ressource/police/arial.ttf", 24);
    SDL_Color couleur_blanc = {255, 255, 255, 255};
    SDL_Surface* surface_tour = NULL;
    SDL_Texture* texture_tour = NULL;

    // --- BOUCLE PRINCIPALE ---
    bool running = true;
    while (running && (nb_selections_j1 < 3 || nb_selections_j2 < 3)) {
        // Mise à jour du texte "Tour de..."
        if (surface_tour) SDL_FreeSurface(surface_tour);
        if (texture_tour) SDL_DestroyTexture(texture_tour);
        
        const char* texte_tour = tour_j1 ? "Tour du Joueur 1" : "Tour du Joueur 2";
        surface_tour = TTF_RenderText_Blended(police, texte_tour, couleur_blanc);
        texture_tour = SDL_CreateTextureFromSurface(rendu, surface_tour);
        
        SDL_Rect rect_tour = {
            (LARGEUR_FENETRE - surface_tour->w) / 2,
            marge_haut + mini_size + 20,
            surface_tour->w,
            surface_tour->h
        };

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                return PAGE_QUITTER;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Détection clic sur personnage disponible
                for (int i = 0; i < 8; i++) {
                    if (!perso_disponible[i]) continue;
                    
                    int colonne = i % 4;
                    int ligne = i / 4;
                    
                    SDL_Rect pos_perso = {
                        espacement_x + colonne * (largeur_perso + espacement_x),
                        start_y_persos - ligne * (hauteur_perso + espacement_y),
                        largeur_perso,
                        hauteur_perso
                    };

                    if (mouseX >= pos_perso.x && mouseX <= pos_perso.x + pos_perso.w &&
                        mouseY >= pos_perso.y && mouseY <= pos_perso.y + pos_perso.h) {
                        
                        if (tour_j1 && nb_selections_j1 < 3) {
                            selections_j1[nb_selections_j1] = portraits[i];
                            nb_selections_j1++;
                        } else if (!tour_j1 && nb_selections_j2 < 3) {
                            selections_j2[nb_selections_j2] = portraits[i];
                            nb_selections_j2++;
                        }
                        
                        perso_disponible[i] = false; // Plus disponible
                        tour_j1 = !tour_j1; // Changement de tour
                        break;
                    }
                }
            }
        } 

        // --- RENDU ---        
        SDL_RenderClear(rendu);
        
        // Fond
        SDL_RenderCopy(rendu, fond_texture, NULL, NULL);
        
        // Logo versus
        SDL_RenderCopy(rendu, logo_versus_texture, NULL, &dest_logo);

        // Affichage des personnages disponibles
        for (int i = 0; i < 8; i++) {
            if (!perso_disponible[i]) continue;
            
            int colonne = i % 4;
            int ligne = i / 4;
            
            SDL_Rect dest = {
                espacement_x + colonne * (largeur_perso + espacement_x),
                start_y_persos - ligne * (hauteur_perso + espacement_y),
                largeur_perso,
                hauteur_perso
            };
            
            if (portraits[i]) {
                SDL_RenderCopy(rendu, portraits[i], NULL, &dest);
                
                // Surbrillance si c'est le tour du joueur
                if ((tour_j1 && nb_selections_j1 < 3) || (!tour_j1 && nb_selections_j2 < 3)) {
                    SDL_SetRenderDrawColor(rendu, 255, 255, 0, 128);
                    SDL_RenderDrawRect(rendu, &dest);
                }
            }
        }

        // Affichage des sélections J1 (gauche)
        for (int i = 0; i < nb_selections_j1; i++) {
            SDL_Rect dest = {
                marge_cote,
                marge_haut + i * (mini_size + espacement_selections),
                mini_size,
                mini_size
            };
            SDL_RenderCopy(rendu, selections_j1[i], NULL, &dest);
        }

        // Affichage des sélections J2 (droite)
        for (int i = 0; i < nb_selections_j2; i++) {
            SDL_Rect dest = {
                LARGEUR_FENETRE - marge_cote - mini_size,
                marge_haut + i * (mini_size + espacement_selections),
                mini_size,
                mini_size
            };
            SDL_RenderCopy(rendu, selections_j2[i], NULL, &dest);
        }

        // Affichage du texte "Tour de..."
        if (texture_tour) {
            SDL_RenderCopy(rendu, texture_tour, NULL, &rect_tour);
        }

        SDL_RenderPresent(rendu);
    }

    /// --- NETTOYAGE ---    
    for (int i = 0; i < 8; i++) {
        if (portraits[i]) SDL_DestroyTexture(portraits[i]);
    }
    if (fond_texture) SDL_DestroyTexture(fond_texture);
    if (logo_versus_texture) SDL_DestroyTexture(logo_versus_texture);
    if (surface_tour) SDL_FreeSurface(surface_tour);
    if (texture_tour) SDL_DestroyTexture(texture_tour);
    if (police) TTF_CloseFont(police);

    if (!running) {
        return PAGE_QUITTER;
    }
}
