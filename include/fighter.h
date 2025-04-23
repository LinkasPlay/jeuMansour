#ifndef FIGHTER_H
#define FIGHTER_H

// === SDL2 ===
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

// === Définitions générales ===
#define LARGEUR_FENETRE 1024
#define HAUTEUR_FENETRE 640

// === Types de pages pour navigation ===
typedef enum {
    PAGE_MENU,
    PAGE_HISTOIRE,
    PAGE_JEU,
    PAGE_QUITTER
} Page;


// === Statuts & Effets ===

typedef enum {
    Aucun = 0,
    BRULE,
    PARALYSIE,
    GEL,
    SAIGNEMENT,
    BOOST_DEF,
    BOOST_PV,
    NERF_DEF
} TypeEffet;

typedef struct {
    TypeEffet type;
    float valeur; // ex : 0.25 = -25% ; ou 10 = +10 PV
    int duree;    // en nombre de tours
} StatutEffet;

// === Attaques spéciales ===

#define MAX_NOM_ATTAQUE 50
#define MAX_DESCRIPTION 300
#define MAX_SPECIAL 3

typedef struct {
    char nom[MAX_NOM_ATTAQUE];
    char description[MAX_DESCRIPTION];
    int degats;
    StatutEffet statu_effet;
    int tour;
} AttaqueSpecial;


// === Fonctions générales ===
void afficher_menu_simple(SDL_Renderer *rendu);
void afficher_chargement(SDL_Renderer *rendu);
Page afficher_intro(SDL_Renderer* rendu, SDL_Window* fenetre);
Page afficher_menu(SDL_Renderer* rendu, SDL_Window* fenetre);

// === Audio ===
void jouer_musique(const char* chemin, int boucle);
void arreter_musique(void);

// === Texte ===
SDL_Texture* generer_texte(SDL_Renderer* rendu, const char* texte, TTF_Font* police);
SDL_Texture* generer_texte_couleur(SDL_Renderer* rendu, const char* texte, TTF_Font* police, SDL_Color couleur);

// === Langue ===
char* charger_texte_depuis_fichier(const char* chemin, const char* etiquette);
void charger_langue(const char* chemin);

#endif
