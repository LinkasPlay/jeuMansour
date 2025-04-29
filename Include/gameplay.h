#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "equipe.h"
#include "fighter.h"

// Fonction pour appliquer les buffs à un personnage
void appliquer_buffs(Fighter* perso, BonusMap bonus);

// Fonction principale pour démarrer le jeu
void debuter_jeu();

#endif // GAMEPLAY_H
