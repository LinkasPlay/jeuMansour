// ----- src/data.c -----
#include "data.h"
#include "logic.h"
#include "interface.h"
#include "son.h"

#include <stdlib.h>
#include <string.h>



// Le tableau global de tous les personnages

AttaqueSpecial Test1 = {
    .nom = "Bonjour",
    .description = "J fais kk dans d avioli",
    .id = 0,
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
    .id = 2,
    .cout = 3,
};

AttaqueSpecial affutageMortal = {
    .nom = "affûtage mortal",
    .description = "Applique Saignement sur attaques normales pendant 3 tours.",
    .id = 1,
    .cout = 5,
};


AttaqueSpecial assautTranchant ={
    .nom = "assaut tranchant",
    .description = "2 frappes à 60 pourcent chacune.",
    .id = 2,
    .cout = 4,
};

AttaqueSpecial eveilDuSabre ={
    .nom = "éveil du sabre",
    .description = "+ 25 pourcent attaque pour 2 tours.",
    .id = 3,
    .cout = 6,
};

AttaqueSpecial flammesSolaires ={
    .nom = "flammes solaires",
    .description = "Change le cycle en Jour",
    .id = 1,
    .cout = 5,
};

AttaqueSpecial explosionArdente ={
    .nom = "explosion ardente",
    .description = "150 pourcent attaque magique + Brûlure.",
    .id = 2,
    .cout = 8,
};

AttaqueSpecial espritFlamboyant ={
    .nom = "esprit flamboyant",
    .description = "Boost attaque/défense alliées +25 pourcent pour 2 tours.",
    .id = 3,
    .cout = 7,
};

AttaqueSpecial prisonDeGivre ={
    .nom = "Prison de givre",
    .description = "Gel : -30 pourcent défense/agilité d'un ennemi pour 2 tours.",
    .id = 1,
    .cout = 5,
};

AttaqueSpecial blizzard ={
    .nom = "Blizzard",
    .description = "AoE physique (30 pourcent puissance) + 50 pourcent chance de Gel.",
    .id = 2,
    .cout = 7,
};

AttaqueSpecial glaceCurative ={
    .nom = "Glace curative",
    .description = "Soigne un allié de 20 pourcent PV max.",
    .id = 3,
    .cout = 4,
};

AttaqueSpecial lienDeSang ={
    .nom = "Lien de Sang",
    .description = "Immobilise un ennemi tant qu'il n'est pas blessé. Katara aussi.",
    .id = 1,
    .cout = 6,
};

AttaqueSpecial vague guerisseuse ={
    .nom = "Vague guérisseuse",
    .description = "Restaure 20 pourcent PV max à un allié.",
    .id = 2,
    .cout = 4,
};

AttaqueSpecial eveil lunaire ={
    .nom = "Éveil lunaire",
    .description = "Change le cycle en Nuit",
    .id = 3,
    .cout = 5,
};

AttaqueSpecial crepuscule ={
    .nom = "Éveil lunaire",
    .description = "Change le cycle en Nuit",
    .id = 1,
    .cout = 5,
};

AttaqueSpecial hurlementNoir ={
    .nom = "Hurlement noir",
    .description = "AoE magique (70 pourcent magie).",
    .id = 2,
    .cout = 6,
};

AttaqueSpecial brumeProtectrice ={
    .nom = "Brume protectrice",
    .description = "Protège un allié (réduction dégâts -30 pourcent, 2 tours).",
    .id = 3,
    .cout = 4,
};


AttaqueSpecial danseDuVent ={
    .nom = "Danse du vent",
    .description = "Réduit l'attaque ennemie de 25 pourcent pour 2 tours.",
    .id = 1,
    .cout = 5,
};

AttaqueSpecial sentPercant ={
    .nom = "Vent perçant",
    .description = "AoE magique (70 pourcent magie)",
    .id = 2,
    .cout = 5,
};

AttaqueSpecial souffleDeVie ={
    .nom = "Souffle de vie",
    .description = "Restaure 20 pourcent PV max à un allié.",
    .id = 3,
    .cout = 4,
};

AttaqueSpecial fulgurance ={
    .nom = "Fulgurance",
    .description = "Ignore 50 pourcent de la défense sur l'attaque.",
    .id = 1,
    .cout = 5,
};

AttaqueSpecial foudreEnchainee ={
    .nom = "Foudre enchaînée",
    .description = "AoE physique (40 pourcent attaque)",
    .id = 2,
    .cout = 6,
};

AttaqueSpecial executionRapide ={
    .nom = "Exécution rapide",
    .description = "Inflige 200 pourcent attaque si cible <30 pourcent PV.",
    .id = 3,
    .cout = 7,
};

AttaqueSpecial murVivant ={
    .nom = "Mur vivant",
    .description = "Protège un allié : subit 100 pourcent de ses dégâts.",
    .id = 1,
    .cout = 5,
};

AttaqueSpecial barriereDePierre ={
    .nom = "Barrière de pierre",
    .description = "Augmente sa propre défense de 50 pourcent pour 2 tours.",
    .id = 2,
    .cout = 4,
};

AttaqueSpecial rugissementDacier ={
    .nom = "Rugissement d'acier",
    .description = "Boost défense alliée +25 pourcent pour 2 tours.",
    .id = 3,
    .cout = 5,
};

Fighter zoro={
    .nom ="zoro",
    .actu_pv =250,
    .max_pv =250,
    .attaque = 30,
    .defense = 15,
    .agilite = 20,
    .vitesse = 10,
    .element = ELEMENT_NONE
};

Fighter rengoku={
    .nom = "rengoku",
    .actu_pv = 280,
    .max_pv =280,
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

Fighter darkshadow={
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

Fighter lukas={
    .nom = "LoukasCocasse",
    .actu_pv = 69696969,
    .max_pv =69696969,
    .attaque = 69696969,
    .defense = 69696969,
    .agilite = 69696969,
    .vitesse = 69696969,
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