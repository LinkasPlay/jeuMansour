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




//Statue effect de degat
void effect_degat(Fighter attaquant, Fighter cible) {
    int degats = attaquant.attaque * 2 - cible.defense;
    if (degats < 0) degats = 0;

    cible.actu_pv -= degats;
    if (cible.actu_pv < 0) cible.actu_pv = 0;

    printf("%s attaque %s (-%d PV)\n", attaquant.nom, cible.nom, degats);
}



//Statue effect de soin
void soin_effet(Fighter lanceur, Fighter cible, int quantite) {
    int pv_avant = cible.actu_pv;

    cible.actu_pv += quantite;
    if (cible.actu_pv > cible.max_pv) {
        cible.actu_pv = cible.max_pv;
    }

    printf("%s soigne %s (+%d PV)\n", lanceur.nom, cible.nom, cible.actu_pv - pv_avant);
}




//Statue effect de defense
void defense_effet(Fighter lanceur, Fighter cible, int bonus) {
    cible.defense += bonus;

    printf("%s augmente la défense de %s (+%d DEF)\n", lanceur.nom, cible.nom, bonus);
}




