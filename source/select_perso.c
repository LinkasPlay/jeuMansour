#include "data.h"
#include "logic.h"
#include "interface.h"
#include "son.h"
#include "attaque.h"


#include <string.h>
#include <time.h>
#include <stdbool.h>





Fighter persoChoisi[6];
int index_selection[6];



void runGame(SDL_Renderer* rendu);



Page afficher_selection_perso(SDL_Renderer* rendu, SDL_Texture* selections_j1[3], SDL_Texture* selections_j2[3]) {
	
	arreter_musique("ressource/musique/ogg/menu_1.ogg");	
	jouerMusique("ressource/musique/ogg/selection_personnages.ogg", 40);


    // --- CHARGEMENT DES TEXTURES ---
    SDL_Texture* fond_texture = IMG_LoadTexture(rendu, "ressource/image/fonds/fond_selection_perso.png");
    if (!fond_texture) {
        SDL_Log("Erreur chargement fond: %s", SDL_GetError());
        return PAGE_QUITTER;
    }

    // --- LOGO VERSUS ---
    SDL_Texture* logo_versus_texture = IMG_LoadTexture(rendu, "ressource/image/utilité/versus.png");
    if (!logo_versus_texture) {
        SDL_Log("Erreur chargement logo: %s", SDL_GetError());
        SDL_DestroyTexture(fond_texture);
        return PAGE_QUITTER;
    }

    SDL_Rect dest_logo = {
        (LARGEUR_FENETRE - 200) / 2,
        10,
        200,
        200
    };

    // --- BOUTON RETOUR ---
    SDL_Texture* btn_retour_texture = IMG_LoadTexture(rendu, "ressource/image/utilité/retour.png");
    SDL_Rect btn_retour_rect = {20, HAUTEUR_FENETRE - 100, 80, 80}; // Nom de variable corrigé

    // --- PORTRAITS DES personnages ---
    const char* noms_portraits[8] = {
        "ressource/image/personnages_pp/pp_droite/pp_darkshadow.png",
        "ressource/image/personnages_pp/pp_droite/pp_hitsugaya.png",
        "ressource/image/personnages_pp/pp_droite/pp_incassable.png",
        "ressource/image/personnages_pp/pp_droite/pp_katara.png",
        "ressource/image/personnages_pp/pp_droite/pp_kirua.png",
        "ressource/image/personnages_pp/pp_droite/pp_rengoku.png",
        "ressource/image/personnages_pp/pp_droite/pp_temari.png",
        "ressource/image/personnages_pp/pp_droite/pp_zoro.png"
    };

    SDL_Texture* portraits[8] = {NULL};
    bool perso_disponible[8] = {true, true, true, true, true, true, true, true};

    for (int i = 0; i < 8; i++) {
        portraits[i] = IMG_LoadTexture(rendu, noms_portraits[i]);
        if (!portraits[i]) {
            SDL_Log("Erreur chargement portrait %d: %s", i, SDL_GetError());
            for (int j = 0; j < i; j++) {
                if (portraits[j]) SDL_DestroyTexture(portraits[j]);
            }
            SDL_DestroyTexture(fond_texture);
            SDL_DestroyTexture(logo_versus_texture);
            if (btn_retour_texture) SDL_DestroyTexture(btn_retour_texture);
            return PAGE_QUITTER;
        }
    }

    // --- GESTION SELECTION ---
   
    int nb_selections_j1 = 0;
    int nb_selections_j2 = 0;
    bool tour_j1 = true;

    // --- POSITIONNEMENT ---
    const int largeur_perso = 150;
    const int hauteur_perso = 150;
    const int espacement_x = (LARGEUR_FENETRE - 4*largeur_perso) / 5;
    const int espacement_y = 50;
    const int start_y_persos = HAUTEUR_FENETRE - hauteur_perso - espacement_y;

    // --- MINI-PORTRAITS ---
    const int mini_size = 80;
    const int marge_haut = 20;
    const int marge_cote = 50;
    const int espacement_selections = 10;

    // --- TEXTE TOUR ---
    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 24);
    if (!police) {
        SDL_Log("Erreur chargement police: %s", TTF_GetError());
        for (int i = 0; i < 8; i++) {
            if (portraits[i]) SDL_DestroyTexture(portraits[i]);
        }
        SDL_DestroyTexture(fond_texture);
        SDL_DestroyTexture(logo_versus_texture);
        if (btn_retour_texture) SDL_DestroyTexture(btn_retour_texture);
        return PAGE_QUITTER;
    }

    //SDL_Color couleur_blanc = {213, 38, 35, 255};
    SDL_Surface* surface_tour = NULL;
    SDL_Texture* texture_tour = NULL;

    // --- BOUCLE PRINCIPALE ---
    bool running = true;
    int a = 0;
    
    while (running && (nb_selections_j1 < 3 || nb_selections_j2 < 3)) {
        // Mise à jour texte tour avec contour et gras
        if (surface_tour) SDL_FreeSurface(surface_tour);
        if (texture_tour) SDL_DestroyTexture(texture_tour);
    
        const char* texte_tour = tour_j1 ? "Tour du Joueur 1" : "Tour du Joueur 2";
        SDL_Color couleur_texte = tour_j1 ? (SDL_Color){213, 38, 35, 255} : (SDL_Color){25, 118, 210, 255};
    
        // Mettre en gras
        TTF_SetFontStyle(police, TTF_STYLE_BOLD);
    
        // Création texte coloré
        TTF_SetFontOutline(police, 0);
        surface_tour = TTF_RenderText_Blended(police, texte_tour, couleur_texte);
        texture_tour = SDL_CreateTextureFromSurface(rendu, surface_tour);
    
        SDL_Rect rect_tour = {
            (LARGEUR_FENETRE - surface_tour->w) / 2,
            marge_haut + mini_size + 80,
            surface_tour->w,
            surface_tour->h
        };
    
        SDL_Event event;
    
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                return PAGE_QUITTER;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = event.button.x;
                int mouseY = event.button.y;

                // Vérifier si clic sur bouton retour
                if (mouseX >= btn_retour_rect.x && 
                    mouseX <= btn_retour_rect.x + btn_retour_rect.w &&
                    mouseY >= btn_retour_rect.y && 
                    mouseY <= btn_retour_rect.y + btn_retour_rect.h) {
        	    jouerMusique("ressource/musique/ogg/menu_1.ogg", 20);
                    running = false;
                    return PAGE_SELEC_MODE;
                }
                else {
                    // Détection clic sur personnage
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
                            
                            jouer_effet("ressource/musique/ogg/persoClique.ogg", 40);  // ← AJOUT ICI

                            if (tour_j1 && nb_selections_j1 < 3) {
                                selections_j1[nb_selections_j1] = portraits[i];
                                nb_selections_j1++;

                            } else if (!tour_j1 && nb_selections_j2 < 3) {
                                selections_j2[nb_selections_j2] = portraits[i];
                                nb_selections_j2++;

                            }                                
                            perso_disponible[i] = false;
                            persoChoisi[a].pt= 0;
                            switch(i){

                                case 0:
                                    strcpy(persoChoisi[a].nom,"darkshadow");
                                    persoChoisi[a].actu_pv=darkshadow.actu_pv;
                                    persoChoisi[a].max_pv=darkshadow.max_pv;
                                    persoChoisi[a].attaque=darkshadow.attaque;
                                    persoChoisi[a].defense=darkshadow.defense;
                                    persoChoisi[a].agilite=darkshadow.agilite;
                                    persoChoisi[a].vitesse=darkshadow.vitesse;
                                    persoChoisi[a].element=darkshadow.element;
                                    index_selection[a] = i;
                                    break;
                               
                                case 1:
                                
                                    strcpy(persoChoisi[a].nom,"hitsugaya");
                                    persoChoisi[a].actu_pv=hitsugaya.actu_pv;
                                    persoChoisi[a].max_pv=hitsugaya.max_pv;
                                    persoChoisi[a].attaque=hitsugaya.attaque;
                                    persoChoisi[a].defense=hitsugaya.defense;
                                    persoChoisi[a].agilite=hitsugaya.agilite;
                                    persoChoisi[a].vitesse=hitsugaya.vitesse;
                                    persoChoisi[a].element=hitsugaya.element;
                                    index_selection[a] = i;
                                    break;
                                case 2:
                                
                                    strcpy(persoChoisi[a].nom,"incassable");
                                    persoChoisi[a].actu_pv=incassable.actu_pv;
                                    persoChoisi[a].max_pv=incassable.max_pv;
                                    persoChoisi[a].attaque=incassable.attaque;
                                    persoChoisi[a].defense=incassable.defense;
                                    persoChoisi[a].agilite=incassable.agilite;
                                    persoChoisi[a].vitesse=incassable.vitesse;
                                    persoChoisi[a].element=incassable.element;
                                    index_selection[a] = i;
                                    break;
                                
                                case 3:
                                    
                                    strcpy(persoChoisi[a].nom,"katara");
                                    persoChoisi[a].actu_pv=katara.actu_pv;
                                    persoChoisi[a].max_pv=katara.max_pv;
                                    persoChoisi[a].attaque=katara.attaque;
                                    persoChoisi[a].defense=katara.defense;
                                    persoChoisi[a].agilite=katara.agilite;
                                    persoChoisi[a].vitesse=katara.vitesse;
                                    persoChoisi[a].element=katara.element;
                                    index_selection[a] = i;
                                    break;
                                
                                case 4:
                                
                                    strcpy(persoChoisi[a].nom,"kirua");
                                    persoChoisi[a].actu_pv=kirua.actu_pv;
                                    persoChoisi[a].max_pv=kirua.max_pv;
                                    persoChoisi[a].attaque=kirua.attaque;
                                    persoChoisi[a].defense=kirua.defense;
                                    persoChoisi[a].agilite=kirua.agilite;
                                    persoChoisi[a].vitesse=kirua.vitesse;
                                    persoChoisi[a].element=kirua.element;
                                    index_selection[a] = i;
                                    break;
                                    
                                case 5:
                                
                                    strcpy(persoChoisi[a].nom,"rengoku");
                                    persoChoisi[a].actu_pv=rengoku.actu_pv;
                                    persoChoisi[a].max_pv=rengoku.max_pv;
                                    persoChoisi[a].attaque=rengoku.attaque;
                                    persoChoisi[a].defense=rengoku.defense;
                                    persoChoisi[a].agilite=rengoku.agilite;
                                    persoChoisi[a].vitesse=rengoku.vitesse;
                                    persoChoisi[a].element=rengoku.element;
                                    index_selection[a] = i;
                                    break;
                                    
                                case 6:
                                    
                                    strcpy(persoChoisi[a].nom,"temari");
                                    persoChoisi[a].actu_pv=temari.actu_pv;
                                    persoChoisi[a].max_pv=temari.max_pv;
                                    persoChoisi[a].attaque=temari.attaque;
                                    persoChoisi[a].defense=temari.defense;
                                    persoChoisi[a].agilite=temari.agilite;
                                    persoChoisi[a].vitesse=temari.vitesse;
                                    persoChoisi[a].element=temari.element;
                                    index_selection[a] = i;
                                    break;
                                    
                                case 7:
                                
                                    strcpy(persoChoisi[a].nom,"zoro");
                                    persoChoisi[a].actu_pv=zoro.actu_pv;
                                    persoChoisi[a].max_pv=zoro.max_pv;
                                    persoChoisi[a].attaque=zoro.attaque;
                                    persoChoisi[a].defense=zoro.defense;
                                    persoChoisi[a].agilite=zoro.agilite;
                                    persoChoisi[a].vitesse=zoro.vitesse;
                                    persoChoisi[a].element=zoro.element;
                                    index_selection[a] = i;
                                    break;

                                default :
                                    strcpy(persoChoisi[a].nom,"lukas");
                                    persoChoisi[a].actu_pv=lukas.actu_pv;
                                    persoChoisi[a].max_pv=lukas.max_pv;
                                    persoChoisi[a].attaque=lukas.attaque;
                                    persoChoisi[a].defense=lukas.defense;
                                    persoChoisi[a].agilite=lukas.agilite;
                                    persoChoisi[a].vitesse=lukas.vitesse;
                                    persoChoisi[a].element=lukas.element;
            
                                    break;
                            }
                            
                            persoChoisi[a].spe_atq1 = affutageMortal;
                            persoChoisi[a].spe_atq2 = assautTranchant;
                            persoChoisi[a].spe_atq3 = eveilDuSabre;

                            if(tour_j1) SDL_Log("Perso %d l'équipe 1 est : %s",a + 1, persoChoisi[a].nom);
                            else SDL_Log("Perso %d de l'équipe 2 est : %s",a + 1, persoChoisi[a].nom);
                            
                            index_selection[a] = i;
                            a = a + 1;
                            tour_j1 = !tour_j1;
                            
                            break;
                        }
                    }
                }
            }
        }


        // --- RENDU ---
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, fond_texture, NULL, NULL);
        SDL_RenderCopy(rendu, logo_versus_texture, NULL, &dest_logo);

        // personnages disponibles
        for (int i = 0; i < 8; i++) {
            if (!perso_disponible[i] || !portraits[i]) continue;
            
            int colonne = i % 4;
            int ligne = i / 4;
            
            SDL_Rect dest = {
                espacement_x + colonne * (largeur_perso + espacement_x),
                start_y_persos - ligne * (hauteur_perso + espacement_y),
                largeur_perso,
                hauteur_perso
            };
            
            SDL_RenderCopy(rendu, portraits[i], NULL, &dest);
        }

        // Sélections J1 (gauche)
        for (int i = 0; i < nb_selections_j1; i++) {
            if (!selections_j1[i]) continue;
            SDL_Rect dest = {
                marge_cote,
                marge_haut + i * (mini_size + espacement_selections),
                mini_size,
                mini_size
            };
            SDL_RenderCopy(rendu, selections_j1[i], NULL, &dest);
        }

        // Sélections J2 (droite)
        for (int i = 0; i < nb_selections_j2; i++) {
            if (!selections_j2[i]) continue;
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

        // Affichage simple du bouton retour
        if (btn_retour_texture) {
            SDL_RenderCopy(rendu, btn_retour_texture, NULL, &btn_retour_rect);
        }

        SDL_RenderPresent(rendu);
    }

    // --- NETTOYAGE ---
    for (int i = 0; i < 8; i++) {
        if (portraits[i]) SDL_DestroyTexture(portraits[i]);
    }
    SDL_DestroyTexture(fond_texture);
    SDL_DestroyTexture(logo_versus_texture);
    if (btn_retour_texture) SDL_DestroyTexture(btn_retour_texture);
    if (surface_tour) SDL_FreeSurface(surface_tour);
    if (texture_tour) SDL_DestroyTexture(texture_tour);
    TTF_CloseFont(police);

       

    return PAGE_CONFIRMATION_PERSO;
}





Page afficher_confirmation_perso(SDL_Renderer* rendu, SDL_Texture* equipe1[3], SDL_Texture* equipe2[3]) {
    SDL_Texture* fond_texture = IMG_LoadTexture(rendu, "ressource/image/fonds/fond_selection_perso.png");
    SDL_Texture* btn_avancer_texture = IMG_LoadTexture(rendu, "ressource/image/utilité/avance.png");
    SDL_Texture* btn_retour_texture = IMG_LoadTexture(rendu, "ressource/image/utilité/retour.png");
    SDL_Texture* vs_texture = IMG_LoadTexture(rendu, "ressource/image/utilité/versus_recap.png");

    if (!fond_texture || !btn_avancer_texture || !btn_retour_texture || !vs_texture) {
        if (fond_texture) SDL_DestroyTexture(fond_texture);
        if (btn_avancer_texture) SDL_DestroyTexture(btn_avancer_texture);
        if (btn_retour_texture) SDL_DestroyTexture(btn_retour_texture);
        if (vs_texture) SDL_DestroyTexture(vs_texture);
        return PAGE_QUITTER;
    }

    SDL_Texture* textures_pixel[6] = {NULL};

    // Chargement des textures pixelisées selon l'ordre de sélection (J1-J2 alterné)
    for (int i = 0; i < 3; i++) {
        // Joueur 1 : index pair (0, 2, 4)
        int idx_j1 = i * 2;
        if (idx_j1 < 6) {
            char chemin[256];
            snprintf(chemin, sizeof(chemin), "ressource/image/personnages_pixel/%s.png", persoChoisi[idx_j1].nom);
            textures_pixel[i] = IMG_LoadTexture(rendu, chemin);
            if (!textures_pixel[i]) {
                SDL_Log("Erreur chargement image %s : %s", chemin, SDL_GetError());
            }
        }

        // Joueur 2 : index impair (1, 3, 5)
        int idx_j2 = i * 2 + 1;
        if (idx_j2 < 6) {
            char chemin[256];
            snprintf(chemin, sizeof(chemin), "ressource/image/personnages_pixel/%s_reverse.png", persoChoisi[idx_j2].nom);
            textures_pixel[i + 3] = IMG_LoadTexture(rendu, chemin);
            if (!textures_pixel[i + 3]) {
                SDL_Log("Erreur chargement image %s : %s", chemin, SDL_GetError());
            }
        }
    }

    const SDL_Rect btn_retour_rect = {20, HAUTEUR_FENETRE - 100, 80, 80};
    const SDL_Rect btn_avancer_rect = {LARGEUR_FENETRE - 100, HAUTEUR_FENETRE - 100, 80, 80};
    const SDL_Rect vs_rect = {LARGEUR_FENETRE / 2 - 40, HAUTEUR_FENETRE / 2 - 40, 200, 200};

    const int largeur_perso = 150;
    const int hauteur_perso = 150;
    const int marge_haut = 100;
    const int espacement = 30;
    const int start_x_j1 = 100;
    const int start_x_j2 = LARGEUR_FENETRE - 100 - largeur_perso;

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                return PAGE_QUITTER;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_Point mouse = {event.button.x, event.button.y};
                if (SDL_PointInRect(&mouse, &btn_avancer_rect)) {
                    running = false;
                    runGame(rendu);
                    return PAGE_COMBAT;
                } else if (SDL_PointInRect(&mouse, &btn_retour_rect)) {
                    running = false;
                    return PAGE_SELECTION_PERSO;
                }
            }
        }

        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, fond_texture, NULL, NULL);

        for (int i = 0; i < 3; i++) {
            // Joueur 1
            if (textures_pixel[i]) {
                SDL_Rect dest1 = {
                    start_x_j1,
                    marge_haut + i * (hauteur_perso + espacement),
                    largeur_perso,
                    hauteur_perso
                };
                SDL_RenderCopy(rendu, textures_pixel[i], NULL, &dest1);
            }

            // Joueur 2
            if (textures_pixel[i + 3]) {
                SDL_Rect dest2 = {
                    start_x_j2,
                    marge_haut + i * (hauteur_perso + espacement),
                    largeur_perso,
                    hauteur_perso
                };
                SDL_RenderCopy(rendu, textures_pixel[i + 3], NULL, &dest2);
            }
        }

        SDL_RenderCopy(rendu, btn_retour_texture, NULL, &btn_retour_rect);
        SDL_RenderCopy(rendu, vs_texture, NULL, &vs_rect);
        SDL_RenderCopy(rendu, btn_avancer_texture, NULL, &btn_avancer_rect);

        SDL_RenderPresent(rendu);
    }

    for (int i = 0; i < 6; i++) {
        if (textures_pixel[i]) SDL_DestroyTexture(textures_pixel[i]);
    }

    SDL_DestroyTexture(fond_texture);
    SDL_DestroyTexture(btn_avancer_texture);
    SDL_DestroyTexture(btn_retour_texture);
    SDL_DestroyTexture(vs_texture);

    return PAGE_CONFIRMATION_PERSO;
}

