#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "audio.h"

void jouer_musique(const char* chemin, int boucle) {
    Mix_Music* musique = Mix_LoadMUS(chemin);
    if (!musique) {
        SDL_Log("Erreur chargement musique (%s) : %s", chemin, Mix_GetError());
        return;
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME);
    if (Mix_PlayMusic(musique, boucle) < 0) {
        SDL_Log("Erreur lecture musique : %s", Mix_GetError());
        Mix_FreeMusic(musique);
        return;
    }
}
