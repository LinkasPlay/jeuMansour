#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "generation_maps.h"
#include "maps.h"


// Fonction pour générer une map aléatoire
MapType generer_map_aleatoire(void) {
    static int deja_initialise = 0;
    if (!deja_initialise) {
        srand(time(NULL)); // Initialiser srand UNE seule fois
        deja_initialise = 1;
    }

    int tirage = rand() % NB_MAPS; // 9 maps au total
    return (MapType)tirage;
}

// Fonction pour afficher le nom de la map tirée (pratique pour debug et immersion)
void afficher_nom_map(MapType map) {
    switch (map) {
        case MAP_CRISTAL:
            printf("La map tirée est : Temple du Cristal\n");
            break;
        case MAP_GLACE:
            printf("La map tirée est : Vallée de Glace\n");
            break;
        case MAP_FEU:
            printf("La map tirée est : Volcan du Feu Eternel\n");
            break;
        case MAP_ECLAIR:
            printf("La map tirée est : Plaine des Eclairs\n");
            break;
        case MAP_VENT:
            printf("La map tirée est : Cime des Vents\n");
            break;
        case MAP_EAU:
            printf("La map tirée est : Cascade Perpetuelle \n");
            break;
        case MAP_OMBRE:
            printf("La map tirée est : Abysses de l'Ombre\n");
            break;
        case MAP_NEUTRE:
            printf("La map tirée est : Arène Neutre\n");
            break;
        case MAP_MYSTERE:
            printf("La map tirée est : Monde Mystère\n");
            break;
        default:
            printf("Map inconnue.\n");
            break;
    }
}