#include <stdio.h>
#include <string.h>
#include "fighter.h"

Fighter personnage[8];

//Creation des attaques spe//
AttaqueSpecial* creer_attaqueSpe(const char* nom,const char* desc,int degats,StatutEffect effet, int tour){
    AttaqueSpecial* attaque = malloc(sizeof(AttaqueSpecial)); // On alloue bine l'espace pour chaque attaque spe
    if(!attaque){
        return NULL;
    }
    strncpy(attaque->nom,nom,MAX_NOM_ATTAQUE);
    strncpy(attaque->description, desc,MAX_DESCRIPTION);
    attaque->degats = degats;
    attaque->statu_effet = effet;
    attaque->tour = tour;
    return attaque;
}

//creation d'un personnage//
Fighter creer_fighter(const char* nom, float actu_pv;float max_pv,float attaque,float defense,float vitesse,AttaqueSpecial** attaques){
    Fighter f;
    strncpy(f.nom,nom,MAX_NOM_PERSO);
    f.actu_pv = actu_pv;
    f.max_pv = max_pv;
    f.attaque = attaque;
    f.defense = defense;
    f.vitesse = vitesse;
    for(int i=0; i<MAX_SPECIAL;i++){
        f.spe_atq[i] = attaques[i];
    }
    return f;
}