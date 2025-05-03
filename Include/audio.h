#ifndef AUDIO_H
#define AUDIO_H

// Joue une musique depuis un fichier avec volume (0–128)
void jouer_musique(const char* chemin, int volume);

// Arrête la musique en cours et libère les ressources
void arreter_musique();

#endif
