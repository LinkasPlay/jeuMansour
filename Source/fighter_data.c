#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "personnages.h" 
//test
Fighter personnage[8];

// Création d'une attaque spéciale
AttaqueSpecial* creer_attaqueSpe(const char* nom, const char* desc, float degats, StatutEffet effet, int tour) {
    AttaqueSpecial* attaque = malloc(sizeof(AttaqueSpecial));
    if (!attaque) {
        return NULL;
    }
    strncpy(attaque->nom, nom, MAX_NOM_ATTAQUE);
    attaque->nom[MAX_NOM_ATTAQUE - 1] = '\0'; // Sécuriser la fin de chaîne
    strncpy(attaque->description, desc, MAX_DESCRIPTION);
    attaque->description[MAX_DESCRIPTION - 1] = '\0'; 
    attaque->degats = degats;
    attaque->statu_effet = effet;
    attaque->tour = tour; //tour de rechargement genre le cooldown quoi
    return attaque;
}

// Création d'un personnage
Fighter creer_fighter(const char* nom, float actu_pv, float max_pv, float attaque, float defense, float vitesse, AttaqueSpecial** attaques) {
    Fighter f;
    strncpy(f.nom, nom, MAX_NOM_PERSO);
    f.nom[MAX_NOM_PERSO - 1] = '\0'; 
    f.actu_pv = actu_pv;
    f.max_pv = max_pv;
    f.attaque = attaque;
    f.defense = defense;
    f.vitesse = vitesse;
    for (int i = 0; i < MAX_SPECIAL; i++) {
        f.spe_atq[i] = attaques[i];
    }
    return f;
}


void initialisation_personnages(){
    //Création des attaques spe//
    AttaqueSpecial* attaque1 = creer_attaqueSpe("Lance Cristalline","Attaque tranchante à mi-distance",30.0,(StatutEffet){SAIGNEMENT,0.98,4},4);
    AttaqueSpecial* attaque2 = creer_attaqueSpe("Barrière de Gemmes","Augmente la défense de son utilisateur pendant 1 tour",0.0,(StatutEffet){BOOST_DEF,1.1,0},0);
    AttaqueSpecial* attaque3 = creer_attaqueSpe("Explosion de Pierres","Attaque de surface touche 2 adversaire sur 3",15.0,(StatutEffet){AUCUN,0.0,0},3);


    //Tableau des attaques
    AttaqueSpecial* attaques_perso1[MAX_SPECIAL] = {attaque1,attaque2,attaque3};

    //Crétion de Incassable 
    personnage[0] = creer_fighter(
        "Incassable", //Nom
        200.0f, // Pv actuel
        200.0f, // Pv max
        10.0f, //Attaque
        25.0f, //Defense
        3.0f, // Vitesse
        attaques_perso1 //Attaques Spe
    );
    
}
//TEST MANSOUR//