#ifndef GENERATION_MAP_H
#define GENERATION_MAP_H

#include "maps.h" // Pour pouvoir utiliser MapType

// Fonction qui génère une map aléatoire
MapType generer_map_aleatoire(void);

// Fonction utilitaire pour afficher le nom de la map (facultatif mais stylé)
void afficher_nom_map(MapType map);

#endif