#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "menu.h"
#include "langue.h"
#include "texte.h"
#include "page.h"

#define NB_IMAGES_VIDEO 100
SDL_Texture* fond_video[NB_IMAGES_VIDEO];

// Fonction pour centrer un rectangle à l’horizontale
static SDL_Rect centrer_page(SDL_Window* fenetre, int y, int largeur, int hauteur) {
    int largeur_fenetre;
    SDL_GetWindowSize(fenetre, &largeur_fenetre, NULL);

    SDL_Rect zone = {
        (largeur_fenetre - largeur) / 2,
        y,
        largeur,
        hauteur
    };
    return zone;
}

Page afficher_menu(SDL_Renderer* rendu, SDL_Window* fenetre) {
    // Charger la police
    TTF_Font* police = TTF_OpenFont("ressource/langue/police/arial.ttf", 28);
    if (!police) {
        SDL_Log("Erreur chargement police : %s", TTF_GetError());
        return PAGE_QUITTER;
    }

    // Texte rouge visible
    SDL_Color couleur_texte = (SDL_Color){200, 0, 0};

    // Générer les textes
    SDL_Texture* texte_jouer   = generer_texte_couleur(rendu, get_texte("START"), police, couleur_texte);
    SDL_Texture* texte_options = generer_texte_couleur(rendu, get_texte("OPTIONS"), police, couleur_texte);
    SDL_Texture* texte_quitter = generer_texte_couleur(rendu, get_texte("QUIT"), police, couleur_texte);

    // Charger les 100 images de fond (à partir de frame_001.png)
    char chemin[128];
    for (int i = 0; i < NB_IMAGES_VIDEO; i++) {
        sprintf(chemin, "ressource/video/frame_menu/frame_%03d.png", i + 1); // commence à 1
        fond_video[i] = IMG_LoadTexture(rendu, chemin);
        if (!fond_video[i]) {
            SDL_Log("Image %03d manquante ou illisible", i + 1);
        }
    }

    int actif = 1;
    SDL_Event evenement;
    Page prochaine_page = PAGE_MENU;

    int numero_image = 0;
    Uint32 moment_precedent = SDL_GetTicks();

    while (actif) {
        Uint32 maintenant = SDL_GetTicks();
        if (maintenant - moment_precedent > 1000 / 10) {
            numero_image = (numero_image + 1) % NB_IMAGES_VIDEO;
            moment_precedent = maintenant;
        }

        int largeur_fenetre;
        SDL_GetWindowSize(fenetre, &largeur_fenetre, NULL);
        int largeur_bouton = largeur_fenetre * 0.25;
        int hauteur_bouton = largeur_bouton / 3;

        SDL_Rect bouton_jouer   = centrer_page(fenetre, 150, largeur_bouton, hauteur_bouton);
        SDL_Rect bouton_options = centrer_page(fenetre, bouton_jouer.y + hauteur_bouton + 10, largeur_bouton, hauteur_bouton);
        SDL_Rect bouton_quitter = centrer_page(fenetre, bouton_options.y + hauteur_bouton + 10, largeur_bouton, hauteur_bouton);

        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT)
                return PAGE_QUITTER;

            if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                int x = evenement.button.x;
                int y = evenement.button.y;

                if (x >= bouton_jouer.x && x <= bouton_jouer.x + bouton_jouer.w &&
                    y >= bouton_jouer.y && y <= bouton_jouer.y + bouton_jouer.h) {
                    prochaine_page = PAGE_HISTOIRE;
                    actif = 0;
                }

                if (x >= bouton_quitter.x && x <= bouton_quitter.x + bouton_quitter.w &&
                    y >= bouton_quitter.y && y <= bouton_quitter.y + bouton_quitter.h) {
                    prochaine_page = PAGE_QUITTER;
                    actif = 0;
                }
            }
        }

        SDL_RenderClear(rendu);

        if (fond_video[numero_image]) {
            SDL_RenderCopy(rendu, fond_video[numero_image], NULL, NULL);
        }

        SDL_RenderCopy(rendu, texte_jouer,   NULL, &bouton_jouer);
        SDL_RenderCopy(rendu, texte_options, NULL, &bouton_options);
        SDL_RenderCopy(rendu, texte_quitter, NULL, &bouton_quitter);
        SDL_RenderPresent(rendu);
        SDL_Delay(1);
    }

    for (int i = 0; i < NB_IMAGES_VIDEO; i++) {
        if (fond_video[i]) SDL_DestroyTexture(fond_video[i]);
    }

    SDL_DestroyTexture(texte_jouer);
    SDL_DestroyTexture(texte_options);
    SDL_DestroyTexture(texte_quitter);
    TTF_CloseFont(police);

    return prochaine_page;
}
