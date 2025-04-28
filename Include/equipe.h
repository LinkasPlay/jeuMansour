#ifndef EQUIPE_H
#define EQUIPE_H

#include "personnages.h"  // Car une équipe contient des personnages

#define NB_PERSOS_EQUIPE 3

typedef struct {
    Fighter* persos[NB_PERSOS_EQUIPE]; // Pointeurs vers les personnages sélectionnés
} Equipe;

// Fonction pour initialiser une équipe à vide
void initialiser_equipe(Equipe* equipe);

// Fonction pour ajouter un personnage à l'équipe
int ajouter_personnage_equipe(Equipe* equipe, Fighter* perso);

// Fonction pour afficher les persos d'une équipe (facultatif pour debug)
void afficher_equipe(const Equipe* equipe);

#endif