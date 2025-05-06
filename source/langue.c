#include <string.h>
#include "langue.h"

Langue langue_actuelle = LANGUE_FR;

void changerLangue(Langue nouvelle_langue) {
    langue_actuelle = nouvelle_langue;
    // Tu peux aussi charger un fichier texte ici si besoin
}

const char* getTexte(const char* id) {
    if (strcmp(id, "titre_menu") == 0) {
        switch (langue_actuelle) {
            case LANGUE_EN: return "Main Menu";
            case LANGUE_ES: return "Menú Principal";
            case LANGUE_DE: return "Hauptmenü";
            case LANGUE_JP: return "メインメニュー";
            default:        return "Menu Principal";
        }
    }

    if (strcmp(id, "credit") == 0) {
        switch (langue_actuelle) {
            case LANGUE_EN: return "Credit";
            case LANGUE_ES: return "Crédito";
            case LANGUE_DE: return "Impressum";
            case LANGUE_JP: return "クレジット";
            default:        return "Crédit";
        }
    }

    if (strcmp(id, "langue") == 0) {
        switch (langue_actuelle) {
            case LANGUE_EN: return "Language";
            case LANGUE_ES: return "Idioma";
            case LANGUE_DE: return "Sprache";
            case LANGUE_JP: return "言語";
            default:        return "Langue";
        }
    }

    if (strcmp(id, "volume") == 0) {
        switch (langue_actuelle) {
            case LANGUE_EN: return "Volume";
            case LANGUE_ES: return "Volumen";
            case LANGUE_DE: return "Lautstärke";
            case LANGUE_JP: return "音量";
            default:        return "Volume";
        }
    }

    if (strcmp(id, "musique") == 0) {
        switch (langue_actuelle) {
            case LANGUE_EN: return "Music";
            case LANGUE_ES: return "Música";
            case LANGUE_DE: return "Musik";
            case LANGUE_JP: return "音楽";
            default:        return "Musique";
        }
    }

    return id; // fallback
}
