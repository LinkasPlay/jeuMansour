#ifndef MAPS_H
#define MAPS_H

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
    MAP_TEMPS,   // Map sans élément
    MAP_MYSTERE,  // Map sans élément
    NB_MAPS       // Total = 9 maps
} MapType;

// ==== Définition des types élémentaires des personnages ====
typedef enum {
    ELEMENT_NONE = 0,
    ELEMENT_CRISTAL,
    ELEMENT_GLACE,
    ELEMENT_FEU,
    ELEMENT_ECLAIR,
    ELEMENT_VENT,
    ELEMENT_EAU,
    ELEMENT_OMBRE
} ElementType;

// ==== Structure pour définir les bonus de map ====
typedef struct {
    int bonus_attaque;   // % bonus attaque
    int bonus_defense;   // % bonus défense
    int bonus_vitesse;   // % bonus vitesse
    int bonus_agilite;   // % bonus agilité (chance esquive)
    int bonus_pv;        // % bonus PV ou soins
} BonusMap;

// ==== Fonction pour savoir si un personnage est boosté sur la map actuelle ====
int booste_sur_map(ElementType element_perso, MapType map_actuelle);

// ==== Fonction pour récupérer les bonus si applicable ====
BonusMap obtenir_bonus_map(MapType map_actuelle, ElementType element_perso);

#endif