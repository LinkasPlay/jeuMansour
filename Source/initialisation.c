#include "selection.h"
#include "generation_maps.h"
#include "maps.h"
#include "fighter.h"
#include "equipe.h"

// Fonction pour initialiser les équipes, générer une carte et appliquer les buffs
void initialiser_jeu(Equipe* equipe1, Equipe* equipe2) {
    // Sélection des personnages pour l'équipe 1
    printf("Equipe 1, faites votre sélection :\n");
    selectionner_personnages(equipe1);

    // Sélection des personnages pour l'équipe 2
    printf("\nEquipe 2, faites votre sélection :\n");
    selectionner_personnages(equipe2);

    // Générer une carte aléatoire
    MapType map_actuelle = generer_map_aleatoire();
    afficher_nom_map(map_actuelle);  // Afficher le nom de la map

    // Appliquer les buffs des maps sur les personnages de chaque équipe
    for (int i = 0; i < NB_PERSOS_EQUIPE; i++) {
        Fighter* perso1 = equipe1->persos[i];
        Fighter* perso2 = equipe2->persos[i];

        // Appliquer les buffs pour chaque personnage de l'équipe 1
        BonusMap bonus1 = obtenir_bonus_map(map_actuelle, perso1->element);
        appliquer_buffs(perso1, bonus1);  // Appliquer les buffs pour perso1

        // Appliquer les buffs pour chaque personnage de l'équipe 2
        BonusMap bonus2 = obtenir_bonus_map(map_actuelle, perso2->element);
        appliquer_buffs(perso2, bonus2);  // Appliquer les buffs pour perso2
    }
}
