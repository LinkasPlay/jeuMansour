// ----- attaque.c -----
#include <stdio.h>
#include <string.h>
#include "attaque.h"
#include "data.h"

void attaque_classique(Combattant *attaquant, Combattant *cible) {
    int degats = attaquant->attaque * 2 - cible->defense;
    if (degats < 0) degats = 0;

    cible->actu_pv -= degats;
    if (cible->actu_pv < 0) cible->actu_pv = 0;

    printf("%s attaque %s (-%d PV)\n", attaquant->nom, cible->nom, degats);
}



