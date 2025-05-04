#include "attaque.h"
#include "data.h"
#include "interface.h"
#include "logic.h"
#include "son.h"


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define ECARTEMENT_PONT 20

AttaqueSauvegarde tableauAttaqueDuTour [NB_PERSOS_EQUIPE * 2];

Fighter* get_fighter(int equipe, int numero) {
    if (equipe == 1) {
        if (numero == 0) return &partieActuelle.joueur1.fighter1;
        if (numero == 1) return &partieActuelle.joueur1.fighter2;
        if (numero == 2) return &partieActuelle.joueur1.fighter3;
    } else {
        if (numero == 0) return &partieActuelle.joueur2.fighter1;
        if (numero == 1) return &partieActuelle.joueur2.fighter2;
        if (numero == 2) return &partieActuelle.joueur2.fighter3;
    }
    return NULL;
}

void renduJeu(SDL_Renderer* rendu) {
    TTF_Font* font = TTF_OpenFont("ressource/langue/police/arial.ttf", 32);
    if (!font) {
        SDL_Log("Erreur police: %s", TTF_GetError());
        return;
    }

    // === Affichage du fond ===
    char fondPath[128];
    snprintf(fondPath, sizeof(fondPath), "ressource/image/fonds/maps/map_%d.png", partieActuelle.mapType);
    SDL_Texture* fond_texture = IMG_LoadTexture(rendu, fondPath);
    if (!fond_texture) {
        SDL_Log("Erreur chargement fond de map : %s", SDL_GetError());
    } else {
        SDL_RenderCopy(rendu, fond_texture, NULL, NULL); // plein écran
    }

    const int largeur_perso = 100;
    const int hauteur_perso = 100;
    const int espacement = 30;
    const int y_perso = (HAUTEUR_FENETRE - hauteur_perso) / 2;

    Fighter* perso1[3] = {
        &partieActuelle.joueur1.fighter1,
        &partieActuelle.joueur1.fighter2,
        &partieActuelle.joueur1.fighter3
    };

    Fighter* perso2[3] = {
        &partieActuelle.joueur2.fighter1,
        &partieActuelle.joueur2.fighter2,
        &partieActuelle.joueur2.fighter3
    };

    // === ÉQUIPE 1 ===
    for (int i = 0; i < 3; i++) {
        int x = 100 + i * (largeur_perso + espacement);
        int y = y_perso + i * 30 +ECARTEMENT_PONT;
        SDL_Rect dest = {x, y, largeur_perso, hauteur_perso};

        char path[128];
        snprintf(path, sizeof(path), "ressource/image/personnages_pixel/%s.png", perso1[i]->nom);
        SDL_Texture* tex = IMG_LoadTexture(rendu, path);

        if (tex) SDL_RenderCopy(rendu, tex, NULL, &dest);

        char infos[64];
        snprintf(infos, sizeof(infos), "PV: %d/%d", perso1[i]->actu_pv, perso1[i]->max_pv);
        SDL_Surface* surf = TTF_RenderUTF8_Blended(font, infos, (SDL_Color){255, 255, 255, 255});
        SDL_Texture* txt = SDL_CreateTextureFromSurface(rendu, surf);

        SDL_Rect txtRect = {dest.x + (largeur_perso - surf->w)/2, dest.y - surf->h - 5, surf->w, surf->h};
        SDL_RenderCopy(rendu, txt, NULL, &txtRect);

        SDL_FreeSurface(surf);
        SDL_DestroyTexture(txt);
        if (tex) SDL_DestroyTexture(tex);
    }

    // === ÉQUIPE 2 ===
    for (int i = 0; i < 3; i++) {
        int x = LARGEUR_FENETRE - 100 - largeur_perso - i * (largeur_perso + espacement);
        int y = y_perso + i * 30+ECARTEMENT_PONT;
        SDL_Rect dest = {x, y, largeur_perso, hauteur_perso};

        char path[128];
        snprintf(path, sizeof(path), "ressource/image/personnages_pixel/%s_reverse.png", perso2[i]->nom);
        SDL_Texture* tex = IMG_LoadTexture(rendu, path);

        if (tex) SDL_RenderCopy(rendu, tex, NULL, &dest);

        char infos[64];
        snprintf(infos, sizeof(infos), "PV: %d/%d", perso2[i]->actu_pv, perso2[i]->max_pv);
        SDL_Surface* surf = TTF_RenderUTF8_Blended(font, infos, (SDL_Color){255, 255, 255, 255});
        SDL_Texture* txt = SDL_CreateTextureFromSurface(rendu, surf);

        SDL_Rect txtRect = {dest.x + (largeur_perso - surf->w)/2, dest.y - surf->h - 5, surf->w, surf->h};
        SDL_RenderCopy(rendu, txt, NULL, &txtRect);

        SDL_FreeSurface(surf);
        SDL_DestroyTexture(txt);
        if (tex) SDL_DestroyTexture(tex);
    }

    // Libération du fond
    if (fond_texture) SDL_DestroyTexture(fond_texture);

}

Fighter choisirCible(SDL_Renderer* rendu, int equipeAdverse){
    
    bool choisi=false;
    SDL_Event event;
    int selection = 0;
    
    SDL_Log("Ennemi %d séléctionné !",selection + 1);
    
    while(!choisi){

        renduJeu(rendu); //rendu --------------------------
    
        while(SDL_PollEvent(&event)){
           
            if(event.type==SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB) {
                selection = (selection + 1) % 3;
                SDL_Log("Ennemi %d séléctionné !",selection + 1);
                
            }

            else if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button==SDL_BUTTON_LEFT){

                choisi=true;
            }
        }
    }


    if(equipeAdverse==1){
    
        switch(selection){
            case 0:
                return partieActuelle.joueur1.fighter1;
            case 1:
                return partieActuelle.joueur1.fighter2;
            case 2:
                return partieActuelle.joueur1.fighter3;
        
        }
    }
    else{
        switch(selection){
            case 0:
                return partieActuelle.joueur2.fighter1;
            case 1:
                return partieActuelle.joueur2.fighter2;
            case 2:
                return partieActuelle.joueur2.fighter3;
        }
    }

}

int screenWidth = 0;
int screenHeight = 0;


void drawButton(SDL_Renderer* renderer, Button* btn, TTF_Font* font) {
    SDL_Color color = btn->hovered ? btn->hoverColor : btn->baseColor;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &btn->rect);

    SDL_Surface* surf = TTF_RenderUTF8_Solid(font, btn->text, (SDL_Color){255, 255, 255, 255});
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

    int tw, th;
    SDL_QueryTexture(tex, NULL, NULL, &tw, &th);
    SDL_Rect textRect = {
        btn->rect.x + (btn->rect.w - tw) / 2,
        btn->rect.y + (btn->rect.h - th) / 2,
        tw, th
    };

    SDL_RenderCopy(renderer, tex, NULL, &textRect);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}



bool isMouseOver(Button* btn, int x, int y) {
    return x >= btn->rect.x && x <= btn->rect.x + btn->rect.w &&
           y >= btn->rect.y && y <= btn->rect.y + btn->rect.h;
}

void actionPerso(SDL_Renderer* renderer, Fighter persoActuel, int equipeAdverse) {
    TTF_Font* font = TTF_OpenFont("ressource/langue/police/arial.ttf", 32);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", TTF_GetError());
        return;
    }


    Button btnAttaque = {{20, screenHeight - 100, 150, 60},{
        60, 60, 60, 255}, {120, 120, 120, 255}, false, "Attaque"};

    Button btnDefense = {{40+btnAttaque.rect.w, screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, "Defense"};

    Button btnComp1 = {{screenWidth-(btnAttaque.rect.w + 20), screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, persoActuel.spe_atq1.nom};
    
    Button btnComp2 = {{screenWidth-(btnAttaque.rect.w*2 + 40), screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, persoActuel.spe_atq2.nom};
        
    Button btnComp3 = {{screenWidth-(btnAttaque.rect.w*3 + 60), screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, persoActuel.spe_atq3.nom};

    bool quit = false;
    SDL_Event event;

    // Track hover précédent
    bool lastHoverAttaque = false, lastHoverDefense = false, lastHoverComp1 = false, lastHoverComp2 = false, lastHoverComp3 = false;

    //SDL_WarpMouseInWindow(window, screenWidth / 2, screenHeight / 2);

    while (!quit) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);

        // Mise à jour des états hover
        btnAttaque.hovered = isMouseOver(&btnAttaque, mx, my);
        btnDefense.hovered = isMouseOver(&btnDefense, mx, my);
        btnComp1.hovered = isMouseOver(&btnComp1, mx, my);
        btnComp2.hovered = isMouseOver(&btnComp2, mx, my);
        btnComp3.hovered = isMouseOver(&btnComp3, mx, my);

      

        // Mise à jour des états précédents
        lastHoverAttaque = btnAttaque.hovered;
        lastHoverDefense = btnDefense.hovered;
        lastHoverComp1 = btnComp1.hovered;
        lastHoverComp2= btnComp2.hovered;
        lastHoverComp3 = btnComp3.hovered;

        // Affichage
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        renduJeu(renderer); //renduuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu

        drawButton(renderer, &btnAttaque, font);
        drawButton(renderer, &btnDefense, font);
        drawButton(renderer, &btnComp1, font);        
        drawButton(renderer, &btnComp2, font);
        drawButton(renderer, &btnComp3, font);

        SDL_RenderPresent(renderer);

        // Événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                //if (sonClose) Mix_PlayChannel(CHANNEL_CLOSE, sonClose, 0);
                SDL_Delay(300);
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN &&
                event.button.button == SDL_BUTTON_LEFT) {
                    if(btnAttaque.hovered) {
                        
                        attaqueClassique(persoActuel, choisirCible(renderer,equipeAdverse));
                        SDL_Log("Attaque terminée");
                        quit = true;
                        break;

                } else if (btnDefense.hovered) {
                    
                } else if (btnComp1.hovered) {
                    tableauAttaqueDuTour[partieActuelle.perso_actif].idAttaque;
                }
            }
        }

        SDL_Delay(16); // ~60 FPS
    }
}


void runGame(SDL_Renderer* rendu){
    SDL_GetWindowSize(fenetre, &screenWidth, &screenHeight);

    partieActuelle.joueur1.fighter1=persoChoisi[0];
    partieActuelle.joueur1.fighter2=persoChoisi[2];
    partieActuelle.joueur1.fighter3=persoChoisi[4];

    partieActuelle.joueur2.fighter1=persoChoisi[1];
    partieActuelle.joueur2.fighter2=persoChoisi[3];
    partieActuelle.joueur2.fighter3=persoChoisi[5];

    partieActuelle.perso_actif=0;
    partieActuelle.tour=1;
    partieActuelle.fin=false;

    for (int i = 0; i < NB_PERSOS_EQUIPE * 2; i++){
        tableauAttaqueDuTour[i].idAttaque = 0;
        tableauAttaqueDuTour[i].utilisateurEquipe = 0;
        tableauAttaqueDuTour[i].utilisateurNum = 0;
        tableauAttaqueDuTour[i].cibleEquipe = 0;
        tableauAttaqueDuTour[i].cibleNum = 0;
    }
    

    partieActuelle.mapType = 1;

    renduJeu(rendu);

    //EQUIPE 1
    actionPerso(rendu,partieActuelle.joueur1.fighter1,2);
    partieActuelle.perso_actif++;
    actionPerso(rendu,partieActuelle.joueur1.fighter2,2);
    partieActuelle.perso_actif++;
    actionPerso(rendu,partieActuelle.joueur1.fighter3,2);
    partieActuelle.perso_actif++;

    //EQUIPE 2
    actionPerso(rendu,partieActuelle.joueur2.fighter1,1);
    partieActuelle.perso_actif++;
    actionPerso(rendu,partieActuelle.joueur2.fighter2,1);
    partieActuelle.perso_actif++;
    actionPerso(rendu,partieActuelle.joueur2.fighter3,1);
    partieActuelle.perso_actif = 0;

    // Execution du tour par vitesse
    int tabIdVitesse[6] = {0,1,2,3,4,5}; // a trieeeeeeeeeeqzieqidhrqoiuhfdiohqjGHFLKHJGLKJzshbf
    for (int i = 0; i < NB_PERSOS_EQUIPE * 2; i++) {
        int index = tabIdVitesse[i];
        AttaqueSauvegarde action = tableauAttaqueDuTour[index];
        Fighter* utilisateur = get_fighter(action.utilisateurEquipe, action.utilisateurNum);
        Fighter* cible = get_fighter(action.cibleEquipe, action.cibleNum);

        if (utilisateur && cible && action.idAttaque >= 0 && action.idAttaque < NB_ATTAQUES_TOTAL) {
            fonctions_attaques[action.idAttaque](utilisateur, cible);
        } else {
            SDL_Log("Erreur : attaque id %d invalide ou cible/utilisateur manquant", action.idAttaque);
        }

    }    
    

}











