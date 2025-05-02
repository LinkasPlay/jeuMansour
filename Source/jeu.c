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

void actionPerso(SDL_Renderer* renderer, int persoActuel) {
    TTF_Font* font = TTF_OpenFont("./Ressource/langue/Police", 32);
    if (!font) {
        SDL_Log("Erreur chargement police: %s", TTF_GetError());
        return;
    }


    Button btnPlay = {{screenWidth/2 - 150, screenHeight/2 - 100, 300, 60},{
        60, 60, 60, 255}, {120, 120, 120, 255}, false, "Jouer"};

    Button btnOptions = {{screenWidth/2 - 150, screenHeight/2, 300, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, "Options"};

    Button btnQuit = {{screenWidth/2 - 150, screenHeight/2 + 100, 300, 60},
        {60, 60, 60, 255}, {120, 120, 120, 255}, false, "Quitter"};

        
    

    bool quit = false;
    SDL_Event event;

    // Track hover précédent
    bool lastHoverPlay = false, lastHoverOptions = false, lastHoverQuit = false;

    //SDL_WarpMouseInWindow(window, screenWidth / 2, screenHeight / 2);

    while (!quit) {
        int mx, my;
        SDL_GetMouseState(&mx, &my);

        // Mise à jour des états hover
        btnPlay.hovered = isMouseOver(&btnPlay, mx, my);
        btnOptions.hovered = isMouseOver(&btnOptions, mx, my);
        btnQuit.hovered = isMouseOver(&btnQuit, mx, my);

      

        // Mise à jour des états précédents
        lastHoverPlay = btnPlay.hovered;
        lastHoverOptions = btnOptions.hovered;
        lastHoverQuit = btnQuit.hovered;

        // Affichage
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        drawButton(renderer, &btnPlay, font);
        drawButton(renderer, &btnOptions, font);
        drawButton(renderer, &btnQuit, font);
        SDL_RenderPresent(renderer);

        // Événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                //if (sonClose) Mix_PlayChannel(CHANNEL_CLOSE, sonClose, 0);
                SDL_Delay(300);
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN &&
                    event.button.button == SDL_BUTTON_LEFT) {
                if (btnPlay.hovered) {
                    //if (sonClick) Mix_PlayChannel(CHANNEL_CLICK, sonClick, 0);
                    //Mix_HaltMusic();
                    //afficherMenuSecondaire(renderer);
                    //if (menuMusic) Mix_PlayMusic(menuMusic, -1);
                } else if (btnOptions.hovered) {
                    //if (sonClick) Mix_PlayChannel(CHANNEL_CLICK, sonClick, 0);
                   // afficherOptions(renderer);
                } else if (btnQuit.hovered) {
                    quit = true;
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

    /*
    Affichage SDL
    
    */

    actionPerso(rendu,0);
    

}











