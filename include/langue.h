#ifndef LANGUE_H
#define LANGUE_H

typedef enum {
    LANGUE_FR,
    LANGUE_EN,
    LANGUE_ES,
    LANGUE_DE,
    LANGUE_JP
} Langue;

extern Langue langue_actuelle;

void changerLangue(Langue nouvelle_langue);
const char* getTexte(const char* identifiant);

#endif
