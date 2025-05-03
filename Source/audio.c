#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string.h>

#include "audio.h"

Mix_Music* musique_actuelle = NULL;

void jouer_musique(const char* chemin, int volume) {
    if (musique_actuelle) {
        Mix_HaltMusic();
        Mix_FreeMusic(musique_actuelle);
        musique_actuelle = NULL;
    }

    musique_actuelle = Mix_LoadMUS(chemin);
    if (!musique_actuelle) {
        fprintf(stderr, "Erreur chargement musique : %s\n", Mix_GetError());
        return;
    }

    Mix_VolumeMusic(volume);
    Mix_PlayMusic(musique_actuelle, -1); // -1 : boucle infinie
}

void arreter_musique() {
    if (musique_actuelle) {
        Mix_HaltMusic();
        Mix_FreeMusic(musique_actuelle);
        musique_actuelle = NULL;
    }
}
