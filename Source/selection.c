#include <stdio.h>
#include "selection.h"

// Permet de choisir les personnages pour une équipe
void selectionner_personnages(Equipe* equipe) {
    int choix;
    initialiser_equipe(equipe);

    printf("Sélectionnez %d personnages pour votre équipe :\n", NB_PERSOS_EQUIPE);
    for (int i = 0; i < NB_PERSOS_EQUIPE; i++) {
        printf("\nListe des personnages disponibles :\n");
        for (int j = 0; j < 8; j++) {
            printf("%d - %s\n", j, personnage[j].nom);
        }

        printf("\nEntrez le numéro du personnage %d : ", i + 1);
        scanf("%d", &choix);

        if (choix >= 0 && choix < 8) {
            ajouter_personnage_equipe(equipe, &personnage[choix]);
            printf("Ajouté : %s\n", personnage[choix].nom);
        } else {
            printf("Choix invalide. Réessayez.\n");
            i--; // Refaire ce tour
        }
    }
    
    
    
    /*

	tuto comment l'utiliser dans le main pour mansour : 
	
	#include "selection.h"

Equipe equipe1, equipe2;

int main() {
    printf("Equipe 1, faites votre sélection :\n");
    selectionner_personnages(&equipe1);

    printf("\nEquipe 2, faites votre sélection :\n");
    selectionner_personnages(&equipe2);

    return 0;
}

	*/
}