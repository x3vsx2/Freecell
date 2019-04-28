//
// Created by kamilcaglar on 26/04/19.
//
#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

#include"pch.h"
#include "FenetrePrincipale.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace cimg_library;

void FenetrePrincipale::lancerJeu(bool nouvellePartie) {
    initialiserFond();
    initialiserCartes();
    bool click_hold = false;
    int memoirePile = 0;
    initialiserPiles(nouvellePartie);//initialise les piles selon le mode de jeu

    Bouton bQuitter("Quitter", "icones_et_boutons/miniQuitter.png", facteurEchelleBoutons_ / 2);

    while (!commandeFermerFenetre()) {
        int mx = getPosSourisX();
        int my = getPosSourisY();

        majAffichage();
        bQuitter.dessinerBouton(visu_, disp->width() - bQuitter.getTailleX() * 1.1,
                                disp->height() - bQuitter.getTailleY() * 1.1);

        // Mouvement souris suite à un déplacement
        if (disp->button()) {//Test si clique ET clique sur une carte
            if (!click_hold) {
                //Déplacement des cartes dans la pile pileDeplacement
                if (estSaisieValide(mx, my)) {
                    memoirePile = getClicPositions(mx, my)[0];
                    deplacerPile(mx, my);
                    //On recupere la pile qui a été cliquée, réutilisation si le mouvement n'est pas valide
                    click_hold = true; //on bloque le clic, seulement si il est valide
                }

            } else {//Dépot de la pile pileDeplacement
                if (estDepotValide(mx, my)) {
                    int pileCliquee = getClicPositions(mx, my)[0]; //numéro de la pile sur laquelle il y a eu un clic
                    pileDeplacement->inverserListeCartes();
                    unsigned int nbCartesAEnlever = pileDeplacement->getTaille();
                    //On dépose la carte sur une pile
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        piles_[pileCliquee]->deplacerCartePile(pileDeplacement);
                    }
                    click_hold = false;
                } else {//si le mouvement n'est pas valide, on remet la carte ou la pile sur la position de départ
                    pileDeplacement->inverserListeCartes();
                    unsigned int nbCartesAEnlever = pileDeplacement->getTaille();
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        if (memoirePile == -1)cout << "c'est ici putain" << endl;
                        piles_[memoirePile]->deplacerCartePile(pileDeplacement);
                    }
                }
                click_hold = false;
            }
            if (PartieEstGagnee()) {// TODO Afficher Partie gagne !
                cout << "Le joueur a remporté la partie" << endl;
            }
            if (bQuitter.estCliquee(mx, my)) {
                break;
            }
        }
        if (disp->is_resized()) {
            majFenetre();
        }
        if (click_hold && pileDeplacement->getTaille() != 0) {
            pileDeplacement->changerPositionPile(mx, my); //Met à jour la position de la pileDeplacement
        }
        visu_->display(*disp);
        disp->wait();
    }
    quitterFenetre();
}

/*!
 *Initialise le plateau, le fond et visu
 */
void FenetrePrincipale::initialiserFond() {
    //declare le plateau de jeu avec longeurXlargeur
    plateau_ = new CImg<unsigned char>(tailleFenX_, tailleFenY_, 1, 1, 0);
    fond_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(), 1, 3, 0);
    colorierImage(*fond_, couleurFond[0], couleurFond[1], couleurFond[2]);
    visu_ = new CImg<unsigned char>(*fond_);
}

/*!
 *Initialise le plateau, le fond et visu
 * @return int, 1 pour nouvelle partie, 2 pour charger partie, 3 pour quitter
 */
int FenetrePrincipale::afficherMenu() {
    initialiserFond();

    Bouton boutonNouvellePartie("BoutonNouvellePartie", "icones_et_boutons/bouton_nouvellePartie.png",
                                facteurEchelleBoutons_);
    boutonNouvellePartie.dessinerBouton(visu_, disp->width() / 2 - boutonNouvellePartie.getTailleX() / 2,
                                        disp->height() * 0.10);

    Bouton boutonChargerPartie("boutonChargerPartie", "icones_et_boutons/bouton_chargerPartie.png",
                               facteurEchelleBoutons_);
    boutonChargerPartie.dessinerBouton(visu_, disp->width() / 2 - boutonChargerPartie.getTailleX() / 2,
                                       disp->height() * 0.40);

    Bouton boutonQuitter("boutonQuitter", "icones_et_boutons/bouton_quitter.png", facteurEchelleBoutons_);
    boutonQuitter.dessinerBouton(visu_, disp->width() / 2 - boutonQuitter.getTailleX() / 2,
                                 disp->height() * 0.70);

    Bouton boutonParametres("boutonParametres", "icones_et_boutons/parametres.png", facteurEchelleBoutons_);
    boutonParametres.dessinerBouton(visu_, disp->width() - boutonParametres.getTailleX() * 1.1,
                                    disp->height() - boutonParametres.getTailleY() * 1.1);

    visu_->display(*disp);
    disp->wait();
    do {
        if (disp->button()) {//Test si clique
            int mx = getPosSourisX();
            int my = getPosSourisY();
            if (boutonNouvellePartie.estCliquee(mx, my)) {
                return 0;
            } else if (boutonChargerPartie.estCliquee(mx, my)) {
                return 1;
            } else if (boutonParametres.estCliquee(mx, my)) {
                return 2;
            } else if (boutonQuitter.estCliquee(mx, my)) {
                return 3;
            }
        }
        if (disp->is_resized()) {
            majFenetre();
        }
        attendre();
    } while (true);
}

void FenetrePrincipale::FenetresParametres() {
    initialiserFond();

    Bouton binstructionsParametres("instructionsParametres", "icones_et_boutons/instructionsParametres.png",
                                   facteurEchelleBoutons_);
    binstructionsParametres.dessinerBouton(visu_, disp->width() / 2 - binstructionsParametres.getTailleX() / 2,
                                           disp->height() / 2 - binstructionsParametres.getTailleY() / 2);
    visu_->display(*disp);

    system(CLEAR);
    cout << "Entrez la nouvelle longeur de la fenetre" << endl;
    int newTailleFenX;
    cin >> newTailleFenX;

    system(CLEAR);
    cout << "Entrez la nouvelle largeur de la fenetre" << endl;
    int newTailleFenY;
    cin >> newTailleFenY;

    system(CLEAR);
    cout << "Entrez la nouvelle echelle de la carte" << endl;
    float newCardsScale;
    cin >> newCardsScale;

    system(CLEAR);
    cout << "Entrez la nouvelle echelle des boutons" << endl;
    float newButtonScale;
    cin >> newButtonScale;

    cout << "Pour utiliser les nouveaux parametres, veuillez relancer FreeCell" << endl;

    sauverFichierSettings(newTailleFenX, newTailleFenY, newCardsScale, newButtonScale);
    quitterFenetre();

}

void FenetrePrincipale::dessinerEmplacementPiles() {
    int tailleX;
    int tailleY;
    int c = 0;
    while (true) {//trouve ua moins une carte et récupère sa taille
        if (piles_[c]->getTaille() !=
            0) { // on vérifie que la pile contient des cartes avant de faire un get taille de la première carte
            if (piles_[c]->getCarte(0)->getTailleX() != 0) {
                tailleX = piles_[c]->getCarte(0)->getTailleX();
                tailleY = piles_[c]->getCarte(0)->getTailleY();
                break;
            }
        }
        c++;// lol mdr
    }
    for (unsigned int i = 0; i < 16; i++) {
        //Piles Jeu
        fond_->draw_rectangle(piles_[i]->getPosX(), piles_[i]->getPosY(), piles_[i]->getPosX() + tailleX,
                              piles_[i]->getPosY() + tailleY,
                              couleurBlanche, 1, ~0U);
    }

}

/*!
 *Colorie une image
 * @param img - l'image que l'on veut colorier
 * @param r - couleur rouge 0 à 255
 * @param g - couleur verte 0 à 255
 * @param b - couleur bleu 0 à 255
 * @return vide
 */
void FenetrePrincipale::colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b) {

    cimg_forXY(img, x, y)
    {
        //Rouge
        img(x, y, 0, 0) = r;
        //Vert
        img(x, y, 0, 1) = g;
        //Bleu
        img(x, y, 0, 2) = b;

    }
}

/*!
 * Redessine chaque carte selon sa position
 */
void FenetrePrincipale::majAffichage() {
    visu_->draw_image(*fond_);

    //On affiche les différentes piles_
    for (unsigned int i = 0; i < piles_.size(); ++i) {
        unsigned int nbCarteADeplacer = piles_[i]->getTaille();
        for (unsigned int j = 0; j < nbCarteADeplacer; ++j) {
            piles_[i]->getCarte(j)->dessinerCarte(visu_);
        }
    }
    int nbCarteADeplacer = pileDeplacement->getTaille();
    for (unsigned int k = 0; k < nbCarteADeplacer; k++) {
        visu_->draw_image(pileDeplacement->getCarte(k)->getPosX(), pileDeplacement->getCarte(k)->getPosY(),
                          pileDeplacement->getCarte(k)->getImg());
    }

}

/*!
 * Initialise les cartes et ajout dans pileMelange
 */
void FenetrePrincipale::initialiserCartes() {
    pileMelange = new PileCarte(0, 0, melange);
    pileMelange->ajouterCarte(new Carte(1, Coeur, As, "imageCarte/h01.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(2, Coeur, Deux, "imageCarte/h02.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(3, Coeur, Trois, "imageCarte/h03.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(4, Coeur, Quatre, "imageCarte/h04.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(5, Coeur, Cinq, "imageCarte/h05.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(6, Coeur, Six, "imageCarte/h06.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(7, Coeur, Sept, "imageCarte/h07.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(8, Coeur, Huit, "imageCarte/h08.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(9, Coeur, Neuf, "imageCarte/h09.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(10, Coeur, Dix, "imageCarte/h10.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(11, Coeur, Valet, "imageCarte/h11.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(12, Coeur, Dame, "imageCarte/h12.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(13, Coeur, Roi, "imageCarte/h13.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(14, Trefle, As, "imageCarte/c01.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(15, Trefle, Deux, "imageCarte/c02.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(16, Trefle, Trois, "imageCarte/c03.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(17, Trefle, Quatre, "imageCarte/c04.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(18, Trefle, Cinq, "imageCarte/c05.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(19, Trefle, Six, "imageCarte/c06.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(20, Trefle, Sept, "imageCarte/c07.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(21, Trefle, Huit, "imageCarte/c08.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(22, Trefle, Neuf, "imageCarte/c09.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(23, Trefle, Dix, "imageCarte/c10.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(24, Trefle, Valet, "imageCarte/c11.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(25, Trefle, Dame, "imageCarte/c12.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(26, Trefle, Roi, "imageCarte/c13.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(27, Carreau, As, "imageCarte/d01.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(28, Carreau, Deux, "imageCarte/d02.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(29, Carreau, Trois, "imageCarte/d03.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(30, Carreau, Quatre, "imageCarte/d04.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(31, Carreau, Cinq, "imageCarte/d05.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(32, Carreau, Six, "imageCarte/d06.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(33, Carreau, Sept, "imageCarte/d07.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(34, Carreau, Huit, "imageCarte/d08.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(35, Carreau, Neuf, "imageCarte/d09.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(36, Carreau, Dix, "imageCarte/d10.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(37, Carreau, Valet, "imageCarte/d11.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(38, Carreau, Dame, "imageCarte/d12.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(39, Carreau, Roi, "imageCarte/d13.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(40, Pique, As, "imageCarte/s01.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(41, Pique, Deux, "imageCarte/s02.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(42, Pique, Trois, "imageCarte/s03.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(43, Pique, Quatre, "imageCarte/s04.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(44, Pique, Cinq, "imageCarte/s05.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(45, Pique, Six, "imageCarte/s06.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(46, Pique, Sept, "imageCarte/s07.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(47, Pique, Huit, "imageCarte/s08.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(48, Pique, Neuf, "imageCarte/s09.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(49, Pique, Dix, "imageCarte/s10.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(50, Pique, Valet, "imageCarte/s11.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(51, Pique, Dame, "imageCarte/s12.svg", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(52, Pique, Roi, "imageCarte/s13.svg", pileMelange, facteurEchelleCartes_));

}

/*!
 * Deplace un certain nombre de cartes dans la pile pileDeplacement selon la position de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 */
void FenetrePrincipale::deplacerPile(int mx, int my) {
    //récupère la position d'une carte dans les piles_
    //Si vector = -1 -1 alors aucune carte n'a été cliquée
    vector<int> positions = getClicPositions(mx, my);

    //On change les cartes de pile si on a cliqué sur une carte
    if (positions[0] != -1) {
        //déplacement d'une ou de plusieurs cartes dans la pile déplacée
        int nbCarteAEnlever = piles_[positions[0]]->getTaille() - positions[1];
        for (unsigned int i = 0; i < nbCarteAEnlever; i++) {
            pileDeplacement->deplacerCartePile(piles_[positions[0]]);
        }
        pileDeplacement->inverserListeCartes();
    }
}

void FenetrePrincipale::majFenetre() {
    int coefX = disp->width();
    int coefY = disp->height();

    disp->resize();
    tailleFenX_ = disp->window_width();
    tailleFenY_ = disp->window_height();
    coefX = (tailleFenX_ / coefX);
    coefY = (tailleFenY_ / coefY);

    sauverFichierSettings(tailleFenX_, tailleFenY_, facteurEchelleCartes_, facteurEchelleBoutons_);
    if (!piles_.empty()) {
        for (unsigned int i = 0; i < piles_.size(); ++i) {
            unsigned int nbCarteADeplacer = piles_[i]->getTaille();
            for (unsigned int j = 0; j < nbCarteADeplacer; ++j) {
                piles_[i]->getCarte(j)->resize(coefX, coefY);
            }
        }
    }
    //facteurEchelleBoutons_ = (coefX * facteurEchelleBoutons_) / tailleFenX_;
    //facteurEchelleCartes_ = (coefX* facteurEchelleCartes_)/tailleFenX_;
}