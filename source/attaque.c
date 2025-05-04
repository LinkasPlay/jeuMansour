// ----- attaque.c -----
#include <stdio.h>
#include <string.h>
#include "attaque.h"
#include "data.h"

typedef void (*FonctionAttaque)(Fighter*, Fighter*);

FonctionAttaque fonctions_attaques[NB_ATTAQUES_TOTAL] = {
    [ATQ_AFFUTAGE_MORTAL]       = attaque_affutage_mortal,
    [ATQ_ASSAUT_TRANCHANT]      = attaque_assaut_tranchant,
    [ATQ_EVEIL_SABRE]           = attaque_eveil_du_sabre,
    [ATQ_FLAMMES_SOLAIRES]      = attaque_flammes_solaires,
    [ATQ_EXPLOSION_ARDENTE]     = attaque_explosion_ardente,
    [ATQ_ESPRIT_FLAMBOYANT]     = attaque_esprit_flamboyant,
    [ATQ_PRISON_DE_GIVRE]       = attaque_prison_de_givre,
    [ATQ_BLIZZARD]              = attaque_blizzard,
    [ATQ_GLACE_CURATIVE]        = attaque_glace_curative,
    [ATQ_LIEN_DE_SANG]          = attaque_lien_de_sang,
    [ATQ_VAGUE_GUERISSEUSE]     = attaque_vague_guerisseuse,
    [ATQ_EVEIL_LUNAIRE]         = attaque_eveil_lunaire,
    [ATQ_CREPUSCULE]            = attaque_crepuscule,
    [ATQ_HURLEMENT_NOIR]        = attaque_hurlement_noir,
    [ATQ_BRUME_PROTECTRICE]     = attaque_brume_protectrice,
    [ATQ_DANSE_DU_VENT]         = attaque_danse_du_vent,
    [ATQ_VENT_PERCANT]          = attaque_vent_percant,
    [ATQ_SOUFFLE_DE_VIE]        = attaque_souffle_de_vie,
    [ATQ_FULGURANCE]            = attaque_fulgurance,
    [ATQ_FOUDRE_ENCHAINEE]      = attaque_foudre_enchainee,
    [ATQ_EXECUTION_RAPIDE]      = attaque_execution_rapide,
    [ATQ_MUR_VIVANT]            = attaque_mur_vivant,
    [ATQ_BARRIERE_DE_PIERRE]    = attaque_barriere_de_pierre,
    [ATQ_RUGISSEMENT_D_ACIER]   = attaque_rugissement_d_acier
};


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


void executer_attaque(int id, Fighter* utilisateur, Fighter* cible) {
    switch (id) {
        case 0:
            attaque_feu(utilisateur, cible);
            break;
        case 1:
            attaque_soin(utilisateur, cible);
            break;
        case 2:
            attaque_paralyse(utilisateur, cible);
            break;
        // Ajoute d'autres attaques ici
        default:
            SDL_Log("ID d'attaque inconnu : %d", id);
            break;
    }
}

void attaque_affutage_mortal(Fighter* u, Fighter* c) {
    SDL_Log("affutage mortal utilisé");
}

void attaque_X(Fighter* utilisateur, Fighter* cible);
