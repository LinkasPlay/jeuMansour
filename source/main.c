#include <stdio.h>
#include "langue.h"
#include "menu.h"

int main() {
    // Charge les textes depuis le fichier francais.txt
    charger_langue("ressource/langue/francais.txt");

    // Lance le menu principal
    afficher_menu();

    return 0;
}
