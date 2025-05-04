// ----- src/data.c -----
#include "data.h"
#include "logic.h"
#include "interface.h"
#include <stdlib.h>
#include <string.h>



// Le tableau global de tous les personnages

AttaqueSpecial Test1 = {
    .nom = "Bonjour",
    .description = "J fais kk dans d avioli",
    .id = 1,
    .cout = 3,
};

AttaqueSpecial Test2 = {
    .nom = "Bonjour69",
    .description = "J fais kk dans d avioli",
    .id = 1,
    .cout = 3,
};

AttaqueSpecial Test3 = {
    .nom = "Bonjour3",
    .description = "J fais kk dans d avioli",
    .id = 1,
    .cout = 3,
};


Fighter zoro={
    .nom ="zoro",
    .actu_pv =300,
    .max_pv =300,
    .attaque = 30,
    .defense = 15,
    .agilite = 20,
    .vitesse = 10,
    .element = ELEMENT_NONE
};

Fighter rengoku={
    .nom = "rengoku",
    .actu_pv = 280,
    .max_pv =300,
    .attaque = 20,
    .defense = 35,
    .agilite = 10,
    .vitesse = 30,
    .element = ELEMENT_FEU
};

Fighter hitsugaya={
    .nom = "hitsugaya",
    .actu_pv = 270,
    .max_pv =270,
    .attaque = 20,
    .defense = 30,
    .agilite = 15,
    .vitesse = 30,
    .element = ELEMENT_GLACE
};

Fighter katara={
    .nom = "katara",
    .actu_pv = 230,
    .max_pv =230,
    .attaque = 20,
    .defense = 20,
    .agilite = 15,
    .vitesse = 50,
    .element = ELEMENT_EAU
};

Fighter dark_shadow={
    .nom = "dark_shadow",
    .actu_pv = 240,
    .max_pv =240,
    .attaque = 20,
    .defense = 20,
    .agilite = 20,
    .vitesse = 35,
    .element = ELEMENT_OMBRE
};

Fighter temari={
    .nom = "temari",
    .actu_pv = 220,
    .max_pv =220,
    .attaque = 15,
    .defense = 20,
    .agilite = 40,
    .vitesse = 50,
    .element = ELEMENT_VENT
};

Fighter kirua={
    .nom = "kirua",
    .actu_pv = 240,
    .max_pv =240,
    .attaque = 30,
    .defense = 10,
    .agilite = 25,
    .vitesse = 50,
    .element = ELEMENT_ECLAIR
};

Fighter incassable={
    .nom = "incassable",
    .actu_pv = 300,
    .max_pv =300,
    .attaque = 10,
    .defense = 40,
    .agilite = 10,
    .vitesse = 30,
    .element = ELEMENT_CRISTAL
};


Joueur equipe1;
Partie partieActuelle;


// Applique un bonus de map à un fighter
void appliquer_buffs(Fighter* perso, BonusMap bonus) {
    perso->attaque += perso->attaque * bonus.bonus_attaque / 100;
    perso->defense += perso->defense * bonus.bonus_defense / 100;
    perso->vitesse += perso->vitesse * bonus.bonus_vitesse / 100;
    perso->agilite += perso->agilite * bonus.bonus_agilite / 100;
    perso->max_pv  += perso->max_pv  * bonus.bonus_pv      / 100;
    // On rétablit les PV actuels au max après buff
    perso->actu_pv = perso->max_pv;
}

/*
// Retourne 1 si l’élément du perso est avantageux sur la map, 0 sinon
int booste_sur_map(ElementType element_perso, MapType map_actuelle) {
    switch (map_actuelle) {
        case MAP_CRISTAL:  return element_perso == ELEMENT_CRISTAL;
        case MAP_GLACE:    return element_perso == ELEMENT_GLACE;
        case MAP_FEU:      return element_perso == ELEMENT_FEU;
        case MAP_ECLAIR:   return element_perso == ELEMENT_ECLAIR;
        case MAP_VENT:     return element_perso == ELEMENT_VENT;
        case MAP_EAU:      return element_perso == ELEMENT_EAU;
        case MAP_OMBRE:    return element_perso == ELEMENT_OMBRE;
        default:           return 0;
    }
}

// Calcule et renvoie le bonus de map pour un perso donné
BonusMap obtenir_bonus_map(MapType map_actuelle, ElementType element_perso) {
    BonusMap bonus = {0, 0, 0, 0, 0};
    // Si élément aligné → +20% attaque
    if (booste_sur_map(element_perso, map_actuelle)) {
        bonus.bonus_attaque = 20;
    }
    // Exemples de buffs supplémentaires selon la map
    switch (map_actuelle) {
        case MAP_GLACE:
            bonus.bonus_defense = 15;  // +15% défense sur Glace
            break;
        case MAP_FEU:
            bonus.bonus_vitesse = 10;  // +10% vitesse sur Feu
            break;
        case MAP_EAU:
            bonus.bonus_pv     = 25;   // +25% PV sur Eau
            break;
        case MAP_OMBRE:
            bonus.bonus_agilite = 20;  // +20% esquive sur Ombre
            break;
        // Ajoutez d’autres cas si besoin…
        default:
            break;
    }
    return bonus;
}
*/