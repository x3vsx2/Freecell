//
// Created by kamilcaglar on 26/04/19.
//


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

        majAffichageJeu(false, bQuitter);

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
            bQuitter.reload(coeffX_, coeffY_, facteurEchelleBoutons_);
            majAffichageJeu(true, bQuitter);

        }
        if (click_hold && pileDeplacement->getTaille() != 0) {
            pileDeplacement->changerPositionPile(mx, my); //Met à jour la position de la pileDeplacement
        }
        attendre();
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
void FenetrePrincipale::majAffichageJeu(bool postResize, Bouton &bQuitter) {
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
    bQuitter.dessinerBouton(visu_, disp->width() - bQuitter.getTailleX() * 1.1,
                            disp->height() - bQuitter.getTailleY() * 1.1);
    if (postResize) {
        dessinerEmplacementPiles();
    }
    visu_->display(*disp);

}

/*!
 * Initialise les cartes et ajout dans pileMelange
 */
void FenetrePrincipale::initialiserCartes() {
    pileMelange = new PileCarte(0, 0, melange);
    pileMelange->ajouterCarte(new Carte(1, Coeur, As, "imageCarte/h01.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(2, Coeur, Deux, "imageCarte/h02.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(3, Coeur, Trois, "imageCarte/h03.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(4, Coeur, Quatre, "imageCarte/h04.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(5, Coeur, Cinq, "imageCarte/h05.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(6, Coeur, Six, "imageCarte/h06.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(7, Coeur, Sept, "imageCarte/h07.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(8, Coeur, Huit, "imageCarte/h08.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(9, Coeur, Neuf, "imageCarte/h09.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(10, Coeur, Dix, "imageCarte/h10.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(11, Coeur, Valet, "imageCarte/h11.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(12, Coeur, Dame, "imageCarte/h12.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(13, Coeur, Roi, "imageCarte/h13.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(14, Trefle, As, "imageCarte/c01.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(15, Trefle, Deux, "imageCarte/c02.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(16, Trefle, Trois, "imageCarte/c03.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(17, Trefle, Quatre, "imageCarte/c04.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(18, Trefle, Cinq, "imageCarte/c05.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(19, Trefle, Six, "imageCarte/c06.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(20, Trefle, Sept, "imageCarte/c07.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(21, Trefle, Huit, "imageCarte/c08.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(22, Trefle, Neuf, "imageCarte/c09.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(23, Trefle, Dix, "imageCarte/c10.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(24, Trefle, Valet, "imageCarte/c11.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(25, Trefle, Dame, "imageCarte/c12.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(26, Trefle, Roi, "imageCarte/c13.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(27, Carreau, As, "imageCarte/d01.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(28, Carreau, Deux, "imageCarte/d02.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(29, Carreau, Trois, "imageCarte/d03.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(30, Carreau, Quatre, "imageCarte/d04.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(31, Carreau, Cinq, "imageCarte/d05.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(32, Carreau, Six, "imageCarte/d06.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(33, Carreau, Sept, "imageCarte/d07.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(34, Carreau, Huit, "imageCarte/d08.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(35, Carreau, Neuf, "imageCarte/d09.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(36, Carreau, Dix, "imageCarte/d10.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(37, Carreau, Valet, "imageCarte/d11.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(38, Carreau, Dame, "imageCarte/d12.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(39, Carreau, Roi, "imageCarte/d13.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(40, Pique, As, "imageCarte/s01.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(41, Pique, Deux, "imageCarte/s02.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(42, Pique, Trois, "imageCarte/s03.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(43, Pique, Quatre, "imageCarte/s04.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(44, Pique, Cinq, "imageCarte/s05.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(45, Pique, Six, "imageCarte/s06.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(46, Pique, Sept, "imageCarte/s07.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(47, Pique, Huit, "imageCarte/s08.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(48, Pique, Neuf, "imageCarte/s09.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(49, Pique, Dix, "imageCarte/s10.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(50, Pique, Valet, "imageCarte/s11.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(51, Pique, Dame, "imageCarte/s12.png", pileMelange, facteurEchelleCartes_));
    pileMelange->ajouterCarte(new Carte(52, Pique, Roi, "imageCarte/s13.png", pileMelange, facteurEchelleCartes_));

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
    float ancienneTailleX = disp->width();
    float ancienneTailleY = disp->height();
    disp->resize();
    tailleFenX_ = disp->width();
    tailleFenY_ = disp->height();
    coeffX_ = tailleFenX_ / ancienneTailleX;
    coeffY_ = tailleFenY_ / ancienneTailleY;

    quitterFenetre();
    initialiserFond();
    //sauverFichierSettings(tailleFenX_, tailleFenY_, facteurEchelleCartes_, facteurEchelleBoutons_);
    //if (!piles_.empty()) {
    //    for (unsigned int i = 0; i < piles_.size(); ++i) {
    //        unsigned int nbCarteADeplacer = piles_[i]->getTaille();
    //        for (unsigned int j = 0; j < nbCarteADeplacer; ++j) {
    //            piles_[i]->getCarte(j)->resize(coefX, coefY);
    //        }
    //    }
    //}
}


