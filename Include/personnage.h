#ifndef PERSONNAGES_H
#define PERSONNAGES_H

// ==== Définition des effets ====
//Je vais ajouter plus tard un autre .h pour les maps
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
    float valeur; // ex : 5.5 dégâts ou 0.25 pour -25%
    int duree;    // durée de l'effet en nombre de tours
} StatutEffet;

// ==== Définition des attaques spéciales ====

#define MAX_NOM_ATTAQUE 50
#define MAX_DESCRIPTION 300
#define MAX_SPECIAL 3

typedef struct {
    char nom[MAX_NOM_ATTAQUE];
    char description[MAX_DESCRIPTION];
    float degats;
    StatutEffet statu_effet;
    int tour;
} AttaqueSpecial;

// ==== Définition des personnages ====

#define MAX_NOM_PERSO 50

typedef struct {
    char nom[MAX_NOM_PERSO];
    float actu_pv;
    float max_pv;
    float attaque;
    float defense;
    float vitesse;
    AttaqueSpecial* spe_atq[MAX_SPECIAL];
} Fighter;

// ==== Variables globales ====
extern Fighter personnage[8];

// ==== Fonctions pour créer personnages et attaques ====
AttaqueSpecial* creer_attaqueSpe(const char* nom, const char* desc, int degats, StatutEffet effet, int tour);
Fighter creer_fighter(const char* nom, float actu_pv, float max_pv, float attaque, float defense, float vitesse, AttaqueSpecial** attaques);

#endif
