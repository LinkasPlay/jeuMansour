// Include/data.h
#ifndef DATA_H
#define DATA_H

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>




extern SDL_Window* fenetre;


// ==== Définition des maps disponibles ====
typedef enum {
    MAP_CRISTAL = 0,
    MAP_GLACE,
    MAP_FEU,
    MAP_ECLAIR,
    MAP_VENT,
    MAP_EAU,
    MAP_OMBRE,
    MAP_NEUTRE,
    MAP_TEMPS,
    MAP_MYSTERE,
    NB_MAPS
} MapType;

// ==== Définition des éléments ====
typedef enum {
    ELEMENT_NONE,
    ELEMENT_CRISTAL,
    ELEMENT_GLACE,
    ELEMENT_FEU,
    ELEMENT_ECLAIR,
    ELEMENT_VENT,
    ELEMENT_EAU,
    ELEMENT_OMBRE
} ElementType;

// ==== Bonus de map ====
typedef struct {
    int bonus_attaque;
    int bonus_defense;
    int bonus_vitesse;
    int bonus_agilite;
    int bonus_pv;
} BonusMap;

// Prototypes map logic
int booste_sur_map(ElementType element_perso, MapType map_actuelle);
BonusMap obtenir_bonus_map(MapType map_actuelle, ElementType element_perso);

// ==== Statuts d'effet ====
typedef enum {
    Aucun = 0,
    BRULE,
    PARALYSIE,
    GEL,
    SAIGNEMENT,
    BOOST_DEF,
    BOOST_PV,
    BOOST_VIT
} StatutEffet;

// ==== Attaques spéciales ====
#define MAX_NOM_ATTAQUE 50
#define MAX_DESCRIPTION 300
#define MAX_SPECIAL 3
#define MAX_EFFETS 3

typedef struct {
    char nom[MAX_NOM_ATTAQUE];
    char description[MAX_DESCRIPTION];
    int degats;
    StatutEffet effets[MAX_EFFETS];
    int nb_effets;
    int tour;
} AttaqueSpecial;

// ==== Fighters ====
#define MAX_NOM_PERSO 50
typedef struct {
    char nom[MAX_NOM_PERSO];
    int actu_pv;
    int max_pv;
    int attaque;
    int defense;
    int agilite;
    int vitesse;
    ElementType element;
    AttaqueSpecial* spe_atq[MAX_SPECIAL];
} Fighter;



typedef struct {
    Fighter fighter1;
    Fighter fighter2;
    Fighter fighter3;

} Joueur;



typedef struct{
    Joueur joueur1;
    Joueur joueur2;

    int perso_actif; 
    int tour;
    bool fin;

} Partie;



typedef struct {
    SDL_Rect rect;
    SDL_Color baseColor;
    SDL_Color hoverColor;
    bool hovered;
    const char* text;
} Button;


extern Fighter zoro;
extern Joueur equipe1;
extern Partie partieActuelle;
extern Fighter persoChoisi[];

void runGame(SDL_Renderer* rendu);

AttaqueSpecial* creer_attaqueSpe(const char* nom, const char* desc, int degats,
                                 StatutEffet effets[], int nb_effets, int tour);
Fighter        creer_fighter   (const char* nom, int actu_pv, int max_pv, int attaque,
                                int defense, int agilite, int vitesse, ElementType element,
                                AttaqueSpecial** attaques);
void           appliquer_buffs (Fighter* perso, BonusMap bonus);

#endif // DATA_H
