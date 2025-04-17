#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Fonction pour centrer une image dans la fenêtre
SDL_Rect centrer_image(SDL_Texture* image, SDL_Window* fenetre, int y, float taille) {
    int largeur_fenetre, hauteur_fenetre;
    SDL_GetWindowSize(fenetre, &largeur_fenetre, &hauteur_fenetre);

    int largeur_image, hauteur_image;
    SDL_QueryTexture(image, NULL, NULL, &largeur_image, &hauteur_image);

    int nouvelle_largeur = largeur_fenetre * taille;
    int nouvelle_hauteur = nouvelle_largeur * hauteur_image / largeur_image;

    SDL_Rect rectangle = {
        (largeur_fenetre - nouvelle_largeur) / 2,
        y,
        nouvelle_largeur,
        nouvelle_hauteur
    };
    return rectangle;
}

// Quitter le programme proprement en cas d’erreur
void quitter(const char* message) {
    SDL_Log("Erreur : %s\nSDL_Error : %s", message, SDL_GetError());
    IMG_Quit();
    SDL_Quit();
    exit(1);
}

int main() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) quitter("Initialisation de SDL échouée");
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) quitter("Initialisation de SDL_image échouée");

    // Création de la fenêtre
    SDL_Window* fenetre = SDL_CreateWindow("Menu Principal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_RESIZABLE);
    if (!fenetre) quitter("Création de la fenêtre échouée");

    // Création du rendu
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!rendu) quitter("Création du rendu échouée");

    // Chargement des images des boutons
    SDL_Texture* bouton_jouer = IMG_LoadTexture(rendu, "ressources/image/start_button.png");
    SDL_Texture* bouton_options = IMG_LoadTexture(rendu, "ressources/image/setting_button.png");
    SDL_Texture* bouton_quitter = IMG_LoadTexture(rendu, "ressources/image/exit_button.png");
    if (!bouton_jouer || !bouton_options || !bouton_quitter) quitter("Chargement des boutons échoué");

    // Chargement des images de la vidéo (150 images)
    const int nb_images = 150;
    SDL_Texture* images[nb_images];
    char chemin[64];
    for (int i = 0; i < nb_images; i++) {
        sprintf(chemin, "ressources/video_frames/frame_%03d.png", i);
        images[i] = IMG_LoadTexture(rendu, chemin);
        if (!images[i]) quitter("Échec du chargement d’une image de fond");
    }

    // Variables de boucle
    int actif = 1;
    SDL_Event evenement;
    int image_actuelle = 0;
    Uint32 derniere_image = SDL_GetTicks();

    int espace_boutons = 10;
    int y_depart = 40;

    SDL_Rect zone_bouton_quitter;

    while (actif) {
        // Gestion des événements
        while (SDL_PollEvent(&evenement)) {
            if (evenement.type == SDL_QUIT)
                actif = 0;

            if (evenement.type == SDL_MOUSEBUTTONDOWN) {
                int souris_x = evenement.button.x;
                int souris_y = evenement.button.y;

                // Si on clique sur le bouton "Quitter"
                if (souris_x >= zone_bouton_quitter.x && souris_x <= zone_bouton_quitter.x + zone_bouton_quitter.w &&
                    souris_y >= zone_bouton_quitter.y && souris_y <= zone_bouton_quitter.y + zone_bouton_quitter.h) {
                    actif = 0;
                }
            }
        }

        // Mise à jour de l’image de fond (30 images par seconde)
        Uint32 maintenant = SDL_GetTicks();
        if (maintenant - derniere_image > 1000 / 30) {
            image_actuelle = (image_actuelle + 1) % nb_images;
            derniere_image = maintenant;
        }

        // Position des boutons
        SDL_Rect zone_bouton_jouer = centrer_image(bouton_jouer, fenetre, y_depart, 0.28f);
        SDL_Rect zone_bouton_options = centrer_image(bouton_options, fenetre, zone_bouton_jouer.y + zone_bouton_jouer.h + espace_boutons, 0.28f);
        zone_bouton_quitter = centrer_image(bouton_quitter, fenetre, zone_bouton_options.y + zone_bouton_options.h + espace_boutons, 0.28f);

        // Affichage à l’écran
        SDL_RenderClear(rendu);
        SDL_RenderCopy(rendu, images[image_actuelle], NULL, NULL);
        SDL_RenderCopy(rendu, bouton_jouer, NULL, &zone_bouton_jouer);
        SDL_RenderCopy(rendu, bouton_options, NULL, &zone_bouton_options);
        SDL_RenderCopy(rendu, bouton_quitter, NULL, &zone_bouton_quitter);
        SDL_RenderPresent(rendu);
        SDL_Delay(1);
    }

    // Nettoyage de la mémoire
    for (int i = 0; i < nb_images; i++) SDL_DestroyTexture(images[i]);
    SDL_DestroyTexture(bouton_jouer);
    SDL_DestroyTexture(bouton_options);
    SDL_DestroyTexture(bouton_quitter);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
