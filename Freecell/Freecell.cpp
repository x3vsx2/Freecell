// Freecell.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
#include "pch.h"
#include <iostream>
#include "FenetrePrincipale.h"

using namespace std;

/*!
 *Initialise les valeur de taille de la fenetre et du facteur d'échelle des boutons
 * @param int &dispX futur longueur de la fenetre
 * @param int &dispY futur largeur de la fenetre
 * @param float &factorScallingCards rapport de taille des cartes par rapport à leur taille originale
 * @param float &factorScallingButton rapport de taille des boutons par rapport à leur taille originale
 * */
void initFreecellSettings(int &dispX, int &dispY, float &factorScallingCards, float &factorScallingButton) {
    ifstream ifs("settings.txt");
    if (ifs.fail()) {
        //Le fichier n'existe pas, on le crée
        ofstream ofs("settings.txt");
        dispX = 1280;
        dispY = 720;
        factorScallingCards = 0.2;
        factorScallingButton = 0.5;
        ofs << dispX << endl; //Longueur de la fenetre
        ofs << dispY << endl;
        ofs << factorScallingCards << endl;
        ofs << factorScallingButton << endl;
        if (!ofs.good()) cout << "Erreur d'écriture" << endl;
        else cout << "Création du fichier settings" << endl;
        ofs.close();

    } else {
        //Le fichier de settings existe
        ifs.seekg(0, std::ios::beg);//Debut du fichier
        string contenu;
        ifs >> dispX;
        ifs.ignore();
        ifs >> dispY;
        ifs.ignore();
        ifs >> factorScallingCards;
        ifs.ignore();
        ifs >> factorScallingButton;
        if (!ifs.good()) cerr << "Erreur de lecture du fichier settings.txt" << endl;
        else {
            cout << "Chargement des paramètre réussi : " << dispX << "x" << dispY << endl;
            cout << "Facteur d'echelle cartes : " << factorScallingCards << endl << "Facteur d'echelle boutons : "
                 << factorScallingButton << endl;
        }
        ifs.close();
    }

}

/*!
 *Fonction main du jeu
 * */
int main() {
    int dispX_, dispY_;
    float factorScallingButton_, factorScallingCards_;
    initFreecellSettings(dispX_, dispY_, factorScallingCards_, factorScallingButton_);
    FenetrePrincipale fen(dispX_, dispY_, factorScallingCards_, factorScallingButton_);
    int choix;
    bool victoire = false;
    do {
        choix = fen.afficherMenu();
        fen.quitterFenetre();
        switch (choix) {
            case 0: {
                victoire = fen.lancerJeu(true);
                fen.attendre();
                if (!victoire) {
                    fen.fenetreSauvegarde();
                }

                break;
            }
            case 1: {
                if (fen.fenetreChargement()) {
                    victoire = fen.lancerJeu(false); // out of range
                    fen.attendre();
                    if (!victoire) {
                        fen.fenetreSauvegarde();
                    }
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

