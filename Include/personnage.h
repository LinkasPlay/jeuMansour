#ifndef PERSONNAGES_H
#define PERSONNAGES_H


#include "maps.h"    // Pour identifier l'element afin de buff le perso selon la map 
// ==== Définition des effets ====
typedef enum {
    Aucun = 0,
    BRULE,
    PARALYSIE,
    GEL,
    SAIGNEMENT,
    BOOST_DEF,
    BOOST_PV,
    BOOST_VIT,
    BOOST_ATT,
    NERF_VIT,
    NERF_DEF
} TypeEffet;

typedef struct {
    TypeEffet type;
    int valeur;  // dégâts ou pourcentage en entier (ex : 5 pour dégâts fixes, 25 pour 25%)
    int duree;   // durée de l'effet en nombre de tours
} StatutEffet;

// ==== Définition des attaques spéciales ====

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
    int tour; // cooldown
} AttaqueSpecial;

// ==== Définition des personnages ====

#define MAX_NOM_PERSO 50

typedef struct {
    char nom[MAX_NOM_PERSO];
    int actu_pv;
    int max_pv;
    int attaque;
    int defense;
    int agilite;  // <-- NOUVEAU : agilité ajoutée j'avais zappé mb
    int vitesse; // determinera l'odre de passage dans l'equipe celui qui a la plus grande vitesse sera le premier à attaquer
    ElementType element;  // <--- UPDATE : element du perso
    AttaqueSpecial* spe_atq[MAX_SPECIAL];
} Fighter;

// ==== Variables globales ====
extern Fighter personnage[8];

// ==== Fonctions pour créer personnages et attaques ====
extern AttaqueSpecial* creer_attaqueSpe(const char* nom, const char* desc, int degats, StatutEffet effets[], int nb_effets, int tour);
extern Fighter creer_fighter(const char* nom, int actu_pv, int max_pv, int attaque, int defense, int agilite, int vitesse, ElementType element, AttaqueSpecial** attaques);

appliquer_buffs(perso1, bonus1);

#endif
