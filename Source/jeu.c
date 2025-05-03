#include "attaque.h"
#include "data.h"
#include "interface.h"
#include "logic.h"


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>



void renduJeu(SDL_Renderer* rendu) {
    TTF_Font* font = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 32);
    if (!font) {
        SDL_Log("Erreur police: %s", TTF_GetError());
        return;
    }

    SDL_SetRenderDrawColor(rendu, 20, 20, 20, 255);
    SDL_RenderClear(rendu);

    const int largeur_perso = 100;
    const int hauteur_perso = 100;
    const int espacement = 30;

    // Position Y fixe au centre vertical
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
        SDL_Rect dest = {x, y_perso, largeur_perso, hauteur_perso};

        char path[128];
        snprintf(path, sizeof(path), "Ressource/image/Personnages_pixel/%s.png", perso1[i]->nom);
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
        SDL_Rect dest = {x, y_perso, largeur_perso, hauteur_perso};

        char path[128];
        snprintf(path, sizeof(path), "Ressource/image/Personnages_pixel/%s_reverse.png", perso2[i]->nom);
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
}

Fighter choisirCible(SDL_Renderer* rendu, int equipeAdverse){
    
    bool choisi=false;
    SDL_Event event;
    int selection;
    
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
    TTF_Font* font = TTF_OpenFont("Ressource/langue/Police/arial.ttf", 32);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", TTF_GetError());
        return;
    }


    Button btnAttaque = {{20, screenHeight - 100, 150, 60},{
        60, 60, 60, 255}, {120, 120, 120, 255}, false, "Attaque"};

    Button btnDefense = {{40+btnAttaque.rect.w, screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, "Options"};

    Button btnComp1 = {{screenWidth-(btnAttaque.rect.w + 20), screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, "Quitter"};
    
    Button btnComp2 = {{screenWidth-(btnAttaque.rect.w*2 + 40), screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, "Quitter"};
        
    Button btnComp3 = {{screenWidth-(btnAttaque.rect.w*3 + 60), screenHeight - 100, 150, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, "Quitter"};

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
                    //if (sonClick) Mix_PlayChannel(CHANNEL_CLICK, sonClick, 0);
                   // afficherOptions(renderer);
                } else if (btnComp1.hovered) {
                    
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

    renduJeu(rendu);

    /*
    Affichage SDL
    
    */

    actionPerso(rendu,partieActuelle.joueur1.fighter1,2);
    

}











