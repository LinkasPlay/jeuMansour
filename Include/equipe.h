#ifndef EQUIPE_H
#define EQUIPE_H

#include "personnage.h" 
#include "maps.h" 


#define NB_PERSOS_EQUIPE 3

typedef struct {
    Fighter* persos[NB_PERSOS_EQUIPE]; // Pointeurs vers les personnages sélectionnés
} Equipe;

typedef struct {
    Equipe equipe1;
    Equipe equipe2;
    ElementType element_map;
    int id_map; 
} Partie;

// Fonction pour initialiser une équipe à vide
void initialiser_equipe(Equipe* equipe);

// Fonction pour ajouter un personnage à l'équipe
int ajouter_personnage_equipe(Equipe* equipe, Fighter* perso);

// Fonction pour afficher les persos d'une équipe (facultatif pour debug)
void afficher_equipe(const Equipe* equipe);

#endif