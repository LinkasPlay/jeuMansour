#include <stdio.h>

#include "fighter.h"
#include "equipe.h"
#include "gameplay.h"
#include "generation_maps.h"
#include "maps.h"
#include "personnage.h"
#include "selection.h"

// Initialise une équipe vide
void initialiser_equipe(Equipe* equipe) {
    for (int i = 0; i < NB_PERSOS_EQUIPE; i++) {
        equipe->persos[i] = NULL;
    }
}

// Ajoute un personnage dans l'équipe (renvoie 1 si réussi, 0 si plein)
int ajouter_personnage_equipe(Equipe* equipe, Fighter* perso) {
    for (int i = 0; i < NB_PERSOS_EQUIPE; i++) {
        if (equipe->persos[i] == NULL) {
            equipe->persos[i] = perso;
            return 1; // Succès
        }
    }
    return 0; // Équipe déjà pleine
}

// Affiche les personnages de l'équipe
void afficher_equipe(const Equipe* equipe) {
    for (int i = 0; i < NB_PERSOS_EQUIPE; i++) {
        if (equipe->persos[i]) {
            printf("Perso %d : %s\n", i, equipe->persos[i]->nom);
        }
    }
}
