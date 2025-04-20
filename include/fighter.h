#ifndef FIGHTER_H
#define FIGHTER_H
#include "special.h"
#define MAX_NOM_PERSO 50
#define MAX_SPECIAL 3


typedef struct{
    char nom[MAX_NOM_PERSO];
    float actu_pv;
    float max_pv;
    float attaque;
    float defense;
    float vitesse;
    const AttaqueSpecial* spe_atq[MAX_SPECIAL];

}Fighter;


#endif