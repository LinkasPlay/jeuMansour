#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personnage.h"

Fighter personnage[8];

// Création d'une attaque spéciale
AttaqueSpecial* creer_attaqueSpe(const char* nom, const char* desc, int degats, StatutEffet effets[], int nb_effets, int tour) {
    AttaqueSpecial* attaque = malloc(sizeof(AttaqueSpecial));
    if (!attaque) return NULL;
    strncpy(attaque->nom, nom, MAX_NOM_ATTAQUE);
    attaque->nom[MAX_NOM_ATTAQUE - 1] = '\0';
    strncpy(attaque->description, desc, MAX_DESCRIPTION);
    attaque->description[MAX_DESCRIPTION - 1] = '\0';
    attaque->degats = degats;
    attaque->nb_effets = nb_effets;
    attaque->tour = tour;
    for (int i = 0; i < nb_effets; i++) {
        attaque->effets[i] = effets[i];
    }
    return attaque;
}

// Création d'un personnage avec agilité et élément
Fighter creer_fighter(const char* nom, int actu_pv, int max_pv, int attaque, int defense, int agilite, int vitesse, ElementType element, AttaqueSpecial** attaques) {
    Fighter f;
    strncpy(f.nom, nom, MAX_NOM_PERSO);
    f.nom[MAX_NOM_PERSO - 1] = '\0';
    f.actu_pv = actu_pv;
    f.max_pv = max_pv;
    f.attaque = attaque;
    f.defense = defense;
    f.agilite = agilite;
    f.vitesse = vitesse;
    f.element = element;
    for (int i = 0; i < MAX_SPECIAL; i++) {
        f.spe_atq[i] = attaques[i];
    }
    return f;
}

void initialisation_personnages() {
    // ===== Incassable =====
    StatutEffet effets1_i[] = { {SAIGNEMENT, 1, 4} };
    AttaqueSpecial* attaque1_i = creer_attaqueSpe("Lance Cristalline", "Attaque tranchante à mi-distance", 30, effets1_i, 1, 4);

    StatutEffet effets2_i[] = { {BOOST_DEF, 10, 1} };
    AttaqueSpecial* attaque2_i = creer_attaqueSpe("Barrière de Gemmes", "Augmente la défense de son utilisateur", 0, effets2_i, 1, 0);

    StatutEffet effets3_i[] = { {Aucun, 0, 0} };
    AttaqueSpecial* attaque3_i = creer_attaqueSpe("Explosion de Pierres", "Attaque de surface", 15, effets3_i, 1, 3);

    AttaqueSpecial* attaques_perso1[MAX_SPECIAL] = { attaque1_i, attaque2_i, attaque3_i };

    personnage[0] = creer_fighter("Incassable", 200, 200, 10, 25, 5, 3, ELEMENT_CRISTAL, attaques_perso1);

    // ===== Kirua =====
    StatutEffet effets1_k[] = { {PARALYSIE, 0, 1} };
    AttaqueSpecial* attaque1_k = creer_attaqueSpe("Griffes Foudroyantes", "Attaque paralysante", 20, effets1_k, 1, 4);

    StatutEffet effets2_k[] = { {BOOST_VIT, 20, 2} };
    AttaqueSpecial* attaque2_k = creer_attaqueSpe("Déplacement Éclair", "Boost de vitesse", 0, effets2_k, 1, 3);

    StatutEffet effets3_k[] = { {Aucun, 0, 0} };
    AttaqueSpecial* attaque3_k = creer_attaqueSpe("Frappe Voltique", "Attaque de zone", 25, effets3_k, 1, 2);

    AttaqueSpecial* attaques_perso2[MAX_SPECIAL] = { attaque1_k, attaque2_k, attaque3_k };

    personnage[1] = creer_fighter("Kirua", 150, 150, 10, 8, 12, 14, ELEMENT_ECLAIR, attaques_perso2);

    // ===== Temari =====
    StatutEffet effets1_t[] = { {Aucun, 0, 0} };
    AttaqueSpecial* attaque1_t = creer_attaqueSpe("Lame Vent", "Diminue la défense", 22, effets1_t, 1, 2);

    StatutEffet effets2_t[] = { {Aucun, 0, 0} };
    AttaqueSpecial* attaque2_t = creer_attaqueSpe("Rafale Tranchante", "Attaque de zone", 26, effets2_t, 1, 3);

    StatutEffet effets3_t[] = { {NERF_VIT, 1, 1} };
    AttaqueSpecial* attaque3_t = creer_attaqueSpe("Tourbillon Violent", "Réduit la vitesse", 15, effets3_t, 1, 1);

    AttaqueSpecial* attaques_perso3[MAX_SPECIAL] = { attaque1_t, attaque2_t, attaque3_t };

   personnage[2] = creer_fighter("Temari", 160, 160, 10, 10, 11, 10, ELEMENT_VENT, attaques_perso3);


    // ===== Katara =====
    StatutEffet effets1_ka[] = { {NERF_VIT, 2, 1} };
    AttaqueSpecial* attaque1_ka = creer_attaqueSpe("Fouet Aquatique", "Réduit la vitesse", 20, effets1_ka, 1, 2);

    StatutEffet effets2_ka[] = { {BOOST_PV, 20, 1}, {BOOST_DEF, 10, 1} };
    AttaqueSpecial* attaque2_ka = creer_attaqueSpe("Vague Curative", "Soigne et boost défense", 0, effets2_ka, 2, 4);

    StatutEffet effets3_ka[] = { {BOOST_DEF, 15, 2} };
    AttaqueSpecial* attaque3_ka = creer_attaqueSpe("Bouclier Aqueux", "Boost de défense", 0, effets3_ka, 1, 5);

    AttaqueSpecial* attaques_perso4[MAX_SPECIAL] = { attaque1_ka, attaque2_ka, attaque3_ka };

    personnage[3] = creer_fighter("Katara", 150, 150, 10, 12, 14, 9, ELEMENT_EAU, attaques_perso4);

    // ===== Rengoku =====
    StatutEffet effets1_r[] = { {BRULE, 2, 3} };
    AttaqueSpecial* attaque1_r = creer_attaqueSpe("Flamme Infernale", "Attaque de feu qui brûle l'adversaire", 30, effets1_r, 1, 3);

    StatutEffet effets2_r[] = { {BOOST_DEF, 2, 1}, {BOOST_VIT, 2, 1} };
    AttaqueSpecial* attaque2_r = creer_attaqueSpe("Posture Ardente", "Boost sa défense et sa vitesse", 0, effets2_r, 2, 3);

    StatutEffet effets3_r[] = { {BRULE, 4, 2} };
    AttaqueSpecial* attaque3_r = creer_attaqueSpe("Explosion Pourfendeuse", "Attaque de zone qui brûle plusieurs adversaires", 20, effets3_r, 1, 3);

    AttaqueSpecial* attaques_perso5[MAX_SPECIAL] = { attaque1_r, attaque2_r, attaque3_r };

    personnage[4] = creer_fighter("Rengoku", 180, 180, 12, 14, 8, 12, ELEMENT_FEU, attaques_perso5);
    
    // ===== DarkShadow =====
    StatutEffet effets1_d[] = {{SAIGNEMENT,1,2}} ;
    AttaqueSpecial* attaque1_d = creer_attaqueSpe("Griffe Nocturne","Inflige de la saigné a son adversair", 24, effets1_d,1,2);
    
    StatutEffet effets2_d[] = {{BOOST_DEF,4,1}} ;
    AttaqueSpecial* attaque2_d = creer_attaqueSpe("Ombre Protectrice","Augmente la défense de son utilisateur", 0, effets2_d,1,2);
    
    StatutEffet effets3_d[] = {{PARALYSIE, 0, 1}} ;
    AttaqueSpecial* attaque3_d = creer_attaqueSpe("Hurlement Obscur","Hurlement qui paralyse son ennemi", 20, effets3_d, 1,4);
    
    AttaqueSpecial* attaques_perso6[MAX_SPECIAL] = { attaque1_d, attaque2_d, attaque3_d };
    
    personnage[5] = creer_fighter("DarkShadow", 170, 170, 10, 13, 7, 10, ELEMENT_OMBRE, attaques_perso6);
    
    // ===== Hitsugaya =====
    StatutEffet effets1_h[] = {{NERF_VIT, 5,1 },{PARALYSIE, 0,1}} ;
    AttaqueSpecial* attaque1_h = creer_attaqueSpe("Hyorinmaru","Attaque qui ralentie la vitesse et paralyse l'adversaire", 20, effets1_h, 2, 4);
    
    StatutEffet effets2_h[] = { {BOOST_DEF, 10,1 }, {NERF_VIT, 3, 1} } ;
    AttaqueSpecial* attaque2_h = creer_attaqueSpe("Armure de Glace","Augmente la defense mais perds de sa vitesse", 0, effets2_h, 2, 4);
    
    StatutEffet effets3_h[] = {{NERF_VIT, 2,1 }} ;
    AttaqueSpecial* attaque3_h = creer_attaqueSpe("Tempete Blanche","Attaque de zone qui ralentie la vitesse des adversaires", 20, effets3_h, 1, 2);
    
    AttaqueSpecial* attaques_perso7[MAX_SPECIAL] = { attaque1_h, attaque2_h, attaque3_h };
    
   personnage[6] = creer_fighter("Hitsugaya", 160, 160, 10, 13, 10, 12, ELEMENT_GLACE, attaques_perso7);
    
    // ===== Zoro =====
    StatutEffet effets1_z[] = {{SAIGNEMENT,4,3}} ;
    AttaqueSpecial* attaque1_z = creer_attaqueSpe("Santoryu-Oni Giri","Tranche l'ennemi et lui fais perdre beaucoup de sang", 30, effets1_z, 1, 3);
    
    StatutEffet effets2_z[] = {{BOOST_DEF,5,1} , {BOOST_ATT,5,1}} ;
    AttaqueSpecial* attaque2_z = creer_attaqueSpe("Haki de l'armement","Augmente la défense de Zoro", 0, effets2_z, 2, 5);
       
    StatutEffet effets3_z[] = {{SAIGNEMENT,2,2}} ;
    AttaqueSpecial* attaque3_z = creer_attaqueSpe("Tornado Slash","Attaque de zone qui fait saigner les adversairs", 25, effets3_z, 1, 2);
    
    AttaqueSpecial* attaques_perso8[MAX_SPECIAL] = {attaque1_z, attaque2_z, attaque3_z } ;
    
    personnage[7] = creer_fighter("Zoro", 170, 170, 10, 14, 6, 11, ELEMENT_NONE, attaques_perso8);
    
    
}