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
            bQuitter.reload(coeffX_, coeffY_);
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
        visu_->draw_rectangle(piles_[i]->getPosX(), piles_[i]->getPosY(), piles_[i]->getPosX() + tailleX,
                              piles_[i]->getPosY() + tailleY, couleurPiles, 1);
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

    bQuitter.dessinerBouton(visu_, disp->width() - bQuitter.getTailleX(),
                            disp->height() - bQuitter.getTailleY());
    if (postResize) {
        for (unsigned int i = 0; i < piles_.size(); ++i) {
			for (unsigned int j = 0; j < piles_[i]->getTaille(); ++j) {
				piles_[i]->getCarte(j)->reload(coeffX_, coeffY_);
			}
        }
        pileJeu1->setPositions(0.10 * disp->width(), 0.40 * disp->height());
        pileJeu2->setPositions(0.20 * disp->width(), 0.40 * disp->height());
        pileJeu3->setPositions(0.30 * disp->width(), 0.40 * disp->height());
        pileJeu4->setPositions(0.40 * disp->width(), 0.40 * disp->height());
        pileJeu5->setPositions(0.50 * disp->width(), 0.40 * disp->height());
        pileJeu6->setPositions(0.60 * disp->width(), 0.40 * disp->height());
        pileJeu7->setPositions(0.70 * disp->width(), 0.40 * disp->height());
        pileJeu8->setPositions(0.80 * disp->width(), 0.40 * disp->height());
        pileLibre1->setPositions(0.08 * disp->width(), 0.10 * disp->height());
        pileLibre2->setPositions(0.18 * disp->width(), 0.10 * disp->height());
        pileLibre3->setPositions(0.28 * disp->width(), 0.10 * disp->height());
        pileLibre4->setPositions(0.38 * disp->width(), 0.10 * disp->height());
        pileValide1->setPositions(0.52 * disp->width(), 0.10 * disp->height());
        pileValide2->setPositions(0.62 * disp->width(), 0.10 * disp->height());
        pileValide3->setPositions(0.72 * disp->width(), 0.10 * disp->height());
        pileValide4->setPositions(0.82 * disp->width(), 0.10 * disp->height());
        for (unsigned int i = 0; i < piles_.size(); i++) {
            for (unsigned int j = 0; j < piles_[i]->getTaille(); j++) {
                piles_[i]->getCarte(j)->setPosX(piles_[i]->getPosX());
                piles_[i]->getCarte(j)->setPosY(piles_[i]->getPosY() + 20 * coeffY_ * j);
            }
        }
    }
    dessinerEmplacementPiles();

    //On affiche les différentes piles_
    for (unsigned int i = 0; i < piles_.size(); ++i) {
		if (i >= 11 && piles_[i]->getTaille()>0) { // si c'est une pile valide on affiche que la dernière carte
			int j = piles_[i]->getTaille()-1 ;
			piles_[i]->getCarte(j)->dessinerCarte(visu_);
		}
		else {
			for (unsigned int j = 0; j < piles_[i]->getTaille(); ++j) {
				piles_[i]->getCarte(j)->dessinerCarte(visu_);
			}
		}
    }
    for (unsigned int k = 0; k < pileDeplacement->getTaille(); k++) {
        pileDeplacement->getCarte(k)->dessinerCarte(visu_);
    }
    visu_->display(*disp);
}

/*!
 * Initialise les cartes et ajout dans pileMelange
 */
void FenetrePrincipale::initialiserCartes() {
    pileMelange = new PileCarte(0, 0, melange);
    pileMelange->ajouterCarte(
            new Carte(1, Coeur, As, "imageCarte/h01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(2, Coeur, Deux, "imageCarte/h02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(3, Coeur, Trois, "imageCarte/h03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(4, Coeur, Quatre, "imageCarte/h04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(5, Coeur, Cinq, "imageCarte/h05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(6, Coeur, Six, "imageCarte/h06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(7, Coeur, Sept, "imageCarte/h07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(8, Coeur, Huit, "imageCarte/h08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(9, Coeur, Neuf, "imageCarte/h09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(10, Coeur, Dix, "imageCarte/h10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(11, Coeur, Valet, "imageCarte/h11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(12, Coeur, Dame, "imageCarte/h12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(13, Coeur, Roi, "imageCarte/h13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(14, Trefle, As, "imageCarte/c01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(15, Trefle, Deux, "imageCarte/c02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(16, Trefle, Trois, "imageCarte/c03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(17, Trefle, Quatre, "imageCarte/c04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(18, Trefle, Cinq, "imageCarte/c05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(19, Trefle, Six, "imageCarte/c06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(20, Trefle, Sept, "imageCarte/c07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(21, Trefle, Huit, "imageCarte/c08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(22, Trefle, Neuf, "imageCarte/c09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(23, Trefle, Dix, "imageCarte/c10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(24, Trefle, Valet, "imageCarte/c11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(25, Trefle, Dame, "imageCarte/c12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(26, Trefle, Roi, "imageCarte/c13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(27, Carreau, As, "imageCarte/d01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(28, Carreau, Deux, "imageCarte/d02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(29, Carreau, Trois, "imageCarte/d03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(30, Carreau, Quatre, "imageCarte/d04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(31, Carreau, Cinq, "imageCarte/d05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(32, Carreau, Six, "imageCarte/d06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(33, Carreau, Sept, "imageCarte/d07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(34, Carreau, Huit, "imageCarte/d08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(35, Carreau, Neuf, "imageCarte/d09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(36, Carreau, Dix, "imageCarte/d10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(37, Carreau, Valet, "imageCarte/d11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(38, Carreau, Dame, "imageCarte/d12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(39, Carreau, Roi, "imageCarte/d13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(40, Pique, As, "imageCarte/s01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(41, Pique, Deux, "imageCarte/s02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(42, Pique, Trois, "imageCarte/s03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(43, Pique, Quatre, "imageCarte/s04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(44, Pique, Cinq, "imageCarte/s05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(45, Pique, Six, "imageCarte/s06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(46, Pique, Sept, "imageCarte/s07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(47, Pique, Huit, "imageCarte/s08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(48, Pique, Neuf, "imageCarte/s09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(49, Pique, Dix, "imageCarte/s10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(50, Pique, Valet, "imageCarte/s11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(51, Pique, Dame, "imageCarte/s12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(52, Pique, Roi, "imageCarte/s13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));

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
    attendre();
    disp->resize();
    tailleFenX_ = disp->width();
    tailleFenY_ = disp->height();
    coeffX_ = float(tailleFenX_) / float(tailleFenOriginaleX_);
    coeffY_ = float(tailleFenY_) / float(tailleFenOriginaleY_);
    quitterFenetre();
    initialiserFond();
}


