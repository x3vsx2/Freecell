// Freecell.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "pch.h"
#include <iostream>
#include "FenetrePrincipale.h"

using namespace std;

void initFreecellSettings(int &dispX, int &dispY, float &factorScallingCards, float &factorScallingButton) {
    ifstream ifs("settings.txt");
    ifs.seekg(0, std::ios::beg);//Debut du fichier
    string contenu;
    ifs >> dispX;
    ifs.ignore();
    ifs >> dispY;
    ifs.ignore();
    ifs >> factorScallingCards;
    ifs.ignore();
    ifs >> factorScallingButton;
    ifs.close();
}

int main() {
    int dispX_, dispY_;
    float factorScallingButton_, factorScallingCards_;
    initFreecellSettings(dispX_, dispY_, factorScallingCards_, factorScallingButton_);
    FenetrePrincipale fen(dispX_, dispY_, factorScallingCards_, factorScallingButton_);
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
                fen.FenetresParametres();
            }
            case 3: {
                break;
            }
        }
    } while (choix != 3 && !fen.commandeFermerFenetre());

    return (0);
}

