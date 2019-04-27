// Freecell.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "pch.h"
#include <iostream>
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

int main() {
    FenetrePrincipale fen;
    int choix;
    do {
        choix = fen.afficherMenu();
        fen.quitterFenetre();
        switch (choix) {
            case 0: {
                fen.lancerJeu(true);
                fen.attendre();
                fen.fenetreSauvegarde();
                break;
            }
            case 1: {
                if (fen.fenetreChargement()) {
                    fen.lancerJeu(false); // out of range
                    fen.attendre();
                    fen.fenetreSauvegarde();
                }
                break;
            }
            case 2: {
                break;
            }
        }
    } while (choix != 2 && !fen.commandeFermerFenetre());

    return (0);
}

