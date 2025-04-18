#ifndef LANGUE_H
#define LANGUE_H

// Charge les textes à partir d’un fichier (ex : "ressource/langue/fr.txt")
void charger_langue(const char* chemin);

// Retourne le texte correspondant à une clé (ex : "START" → "JOUER")
const char* get_texte(const char* cle);

#endif
