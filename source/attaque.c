// ----- attaque.c -----
#include <stdio.h>
#include <string.h>
#include "attaque.h"
#include "data.h"



//Attque classique 
void attaqueClassique(Fighter attaquant, Fighter cible) {
    int degats = attaquant.attaque * 2 - cible.defense;
    //SDL_Log("Salope");
    
    if (degats < 0) degats = 0;

    cible.actu_pv -= degats;
    if (cible.actu_pv < 0) cible.actu_pv = 0;

    printf("%s attaque %s (-%d PV)\n", attaquant.nom, cible.nom, degats);

}




// Effet de soin
void soin_effet(Fighter lanceur, Fighter cible, int quantite) {
    int avant = cible.actu_pv;
    int apres = avant + quantite;

    if (apres > cible.max_pv)
        apres = cible.max_pv;

    cible.actu_pv = apres;

    printf("%s soigne %s (+%d PV)\n", lanceur.nom, cible.nom, apres - avant);
}

// Effet de défense
void defense_effet(Fighter lanceur, Fighter cible, int bonus) {
    int ancienne_def = cible.defense;
    cible.defense += bonus;

    printf("%s augmente la défense de %s (+%d DEF)\n", lanceur.nom, cible.nom, cible.defense - ancienne_def);
}


