#include "equipe.h"
#include "fighter.h"

// Fonction pour calculer la vitesse moyenne d'une équipe
float calculer_vitesse_moyenne(const Equipe* equipe) {
    int somme_vitesse = 0;

    // Ajouter la vitesse de chaque personnage dans l'équipe
    for (int i = 0; i < NB_PERSOS_EQUIPE; i++) {
        if (equipe->persos[i] != NULL) {
            somme_vitesse += equipe->persos[i]->vitesse;
        }
    }

    // Retourner la vitesse moyenne
    return (float)somme_vitesse / NB_PERSOS_EQUIPE;
}

// Fonction pour déterminer l'ordre d'attaque des équipes
void determiner_ordre_attaque(Equipe* equipe1, Equipe* equipe2) {
    // Calculer la vitesse moyenne des deux équipes
    float vitesse_moyenne_equipe1 = calculer_vitesse_moyenne(equipe1);
    float vitesse_moyenne_equipe2 = calculer_vitesse_moyenne(equipe2);

    // Comparer les vitesses moyennes pour déterminer qui attaque en premier
    if (vitesse_moyenne_equipe1 > vitesse_moyenne_equipe2) {
        printf("L'équipe 1 attaque en premier.\n");
    } else if (vitesse_moyenne_equipe1 < vitesse_moyenne_equipe2) {
        printf("L'équipe 2 attaque en premier.\n");
    } else {
        printf("Les deux équipes ont la même vitesse moyenne. Tirage au sort !\n");
        // Si les vitesses moyennes sont égales, tu peux faire un tirage au sort pour déterminer l'ordre
        if (rand() % 2 == 0) {
            printf("L'équipe 1 attaque en premier.\n");
        } else {
            printf("L'équipe 2 attaque en premier.\n");
        }
    }
}

// Fonction principale du gameplay : exécute les actions du combat
void commencer_combat(Equipe* equipe1, Equipe* equipe2) {
    // Déterminer l'ordre d'attaque des équipes
    determiner_ordre_attaque(equipe1, equipe2);

    // Logique du combat à ajouter ici (ex : tours de combat, attaque, défense, etc.)
}
