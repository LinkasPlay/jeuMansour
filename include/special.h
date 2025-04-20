#ifndef SPECIAL_H //Permets de faire une seule lecture du fichier special depuis les autres
#define SPECIAL_H
#include "statu_effet.h"
#define MAX_NOM_ATTAQUE 50
#define MAX_DESCRIPTION 200
#define MAX_SPECIAL 3
typedef struct{
    char nom[MAX_NOM_ATTAQUE];
    char description[MAX_DESCRIPTION];
    int degats;
    StatutEffet statu_effet;
    int tour;
}AttaqueSpecial;

#endif