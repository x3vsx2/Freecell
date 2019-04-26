//
// Created by kamilcaglar on 26/04/19.
//
#include"FenetrePrincipale.h"
#include"pch.h"
#include "FenetrePrincipale.h"
#include "PileCarte.h"
#include "Bouton.h"
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace cimg_library;

void FenetrePrincipale::lancerJeu(bool nouvellePartie) {
    initialiserFond();
    dessinerEmplacementPiles();
    initialiserCartes();

    //Boucle Principale, ferme la fenetre si ESC or Q key is hit
    bool click_hold = false;
    int memoirePile = 0;
    if (nouvellePartie) {
        initialiserPiles(true);
    } else {
        initialiserPiles(true);
    }
    Bouton bQuitter("Quitter", disp->width() - 85, disp->height() - 100,
                    "icones_et_boutons/miniQuitter.png");

    while (!disp->is_closed() && !disp->is_keyESC() && !disp->is_keyQ()) {

        //Recuperation positions de la souris
        //mx = position souris en x, my = position souris en y
        const int mx = disp->mouse_x() * (*fond_).width() / disp->width(),
                my = disp->mouse_y() * (*fond_).height() / disp->height();

        majAffichage();
        bQuitter.dessinerBouton(visu_);
        // Mouvement souris suite à un déplacement
        if (disp->button()) {//Test si clique ET clique sur une carte
            if (!click_hold) {
                //Déplacement des cartes dans la pile pileDeplacement
                if (estSaisieValide(mx, my)) {
                    cout << "Clic Bloqué" << endl;
                    memoirePile = getClicPositions(mx, my)[0];
                    deplacerPile(mx, my);
                    //On recupere la pile qui a été cliquée, réutilisation si le mouvement n'est pas valide
                    click_hold = true; //on bloque le clic, seulement si il est valide
                }

            } else {//Dépot de la pile pileDeplacement
                cout << "Clic Débloqué" << endl;
                if (estDepotValide(mx, my)) {
                    int pileCliquee = getClicPositions(mx, my)[0]; //numéro de la pile sur laquelle il y a eu un clic
                    pileDeplacement->inverserListeCartes();
                    int nbCartesAEnlever = pileDeplacement->getTaille();
                    //On dépose la carte sur une pile
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        piles_[pileCliquee]->deplacerCartePile(pileDeplacement);
                    }
                    click_hold = false;
                } else {//si le mouvement n'est pas valide, on remet la carte ou la pile sur la position de départ
                    pileDeplacement->inverserListeCartes();
                    int nbCartesAEnlever = pileDeplacement->getTaille();
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        if (memoirePile == -1)cout << "c'est ici putain" << endl;
                        piles_[memoirePile]->deplacerCartePile(pileDeplacement);
                    }
                }
                click_hold = false;
            }
            if (bQuitter.estCliquee(mx, my)) {
                break;
            }
        }

        if (click_hold && pileDeplacement->getTaille() != 0) {
            pileDeplacement->changerPositionPile(mx, my); //Met à jour la position de la pileDeplacement
        }

        visu_->display(*disp);
        disp->wait();

    }

}

/*!
 *Initialise le plateau, le fond et visu
 */
void FenetrePrincipale::initialiserFond() {
    //declare le plateau de jeu avec longeurXlargeur
    plateau_ = new CImg<unsigned char>(1280, 720, 1, 1, 0);
    fond_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(), 1, 3, 0);
    colorierImage(*fond_, 26, 83, 92);
    visu_ = new CImg<unsigned char>(*fond_);
}

void FenetrePrincipale::effacerFond() {
    //declare le plateau de jeu avec longeurXlargeur
    delete plateau_;
    delete fond_;
    delete visu_;
}

int FenetrePrincipale::afficherMenu() {
    initialiserFond();

    Bouton boutonNouvellePartie("BoutonNouvellePartie", disp->width() / 2 - 150, 100,
                                "icones_et_boutons/bouton_nouvellePartie.png");
    boutonNouvellePartie.dessinerBouton(visu_);

    Bouton boutonChargerPartie("boutonChargerPartie", disp->width() / 2 - 150, 250,
                               "icones_et_boutons/bouton_chargerPartie.png");
    boutonChargerPartie.dessinerBouton(visu_);

    Bouton boutonQuitter("boutonQuitter", disp->width() / 2 - 150, 400, "icones_et_boutons/bouton_quitter.png");
    boutonQuitter.dessinerBouton(visu_);

    visu_->display(*disp);
    disp->wait();
    do {
        if (disp->button()) {//Test si clique
            //Recuperation positions de la souris
            //mx = position souris en x, my = position souris en y
            const int mx = disp->mouse_x() * (*fond_).width() / disp->width(),
                    my = disp->mouse_y() * (*fond_).height() / disp->height();
            if (mx >= boutonNouvellePartie.getpositionX() &&
                mx <= boutonNouvellePartie.getpositionX() + boutonNouvellePartie.getTailleX()
                && my >= boutonNouvellePartie.getpositionY() &&
                my <= boutonNouvellePartie.getpositionY() + boutonNouvellePartie.getTailleY()) {
                return 0;
            } else if (mx >= boutonChargerPartie.getpositionX() &&
                       mx <= boutonChargerPartie.getpositionX() + boutonChargerPartie.getTailleX()
                       && my >= boutonChargerPartie.getpositionY() &&
                       my <= boutonChargerPartie.getpositionY() + boutonChargerPartie.getTailleY()) {
                return 1;
            } else if (mx >= boutonQuitter.getpositionX() &&
                       mx <= boutonQuitter.getpositionX() + boutonQuitter.getTailleX()
                       && my >= boutonQuitter.getpositionY() &&
                       my <= boutonQuitter.getpositionY() + boutonQuitter.getTailleY()) {
                return 2;
            }
        }
    } while (true);

}

void FenetrePrincipale::dessinerEmplacementPiles() {
    unsigned char couleurBlanche[3] = {255, 255, 255};
    unsigned char couleurGrise[3] = {125, 125, 125};
    int p1 = 99;
    for (unsigned int i = 0; i < 8; i++) {
        //fond_->draw_rectangle(x1, y1, x2, y2, couleur, 1, ~0U);
        //Piles Jeu
        fond_->draw_rectangle(p1 + (135 * i), 299, p1 + (135 * i) + 72, 299 + 97, couleurGrise, 1, ~0U);
    }
    p1 = 99;
    int p2 = 1279 - 500;
    for (unsigned int i = 0; i < 4; i++) {
        //Piles Libres
        fond_->draw_rectangle(p1 + (100 * i), 49, p1 + (100 * i) + 72, 50 + 97, couleurBlanche, 1, ~0U);
        //Piles Valide
        fond_->draw_rectangle(p2 + (100 * i), 49, p2 + (100 * i) + 72, 50 + 97, couleurBlanche, 1, ~0U);
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
        int nbCarteADeplacer = piles_[i]->getTaille();
        for (unsigned int j = 0; j < nbCarteADeplacer; ++j) {
            visu_->draw_image(piles_[i]->getCarte(j)->getPosX(), piles_[i]->getCarte(j)->getPosY(),
                              piles_[i]->getCarte(j)->getImg());
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
    pileMelange->ajouterCarte(new Carte(1, Coeur, As, "imageCarte/h01.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(2, Coeur, Deux, "imageCarte/h02.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(3, Coeur, Trois, "imageCarte/h03.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(4, Coeur, Quatre, "imageCarte/h04.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(5, Coeur, Cinq, "imageCarte/h05.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(6, Coeur, Six, "imageCarte/h06.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(7, Coeur, Sept, "imageCarte/h07.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(8, Coeur, Huit, "imageCarte/h08.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(9, Coeur, Neuf, "imageCarte/h09.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(10, Coeur, Dix, "imageCarte/h10.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(11, Coeur, Valet, "imageCarte/h11.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(12, Coeur, Dame, "imageCarte/h12.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(13, Coeur, Roi, "imageCarte/h13.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(14, Trefle, As, "imageCarte/c01.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(15, Trefle, Deux, "imageCarte/c02.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(16, Trefle, Trois, "imageCarte/c03.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(17, Trefle, Quatre, "imageCarte/c04.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(18, Trefle, Cinq, "imageCarte/c05.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(19, Trefle, Six, "imageCarte/c06.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(20, Trefle, Sept, "imageCarte/c07.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(21, Trefle, Huit, "imageCarte/c08.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(22, Trefle, Neuf, "imageCarte/c09.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(23, Trefle, Dix, "imageCarte/c10.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(24, Trefle, Valet, "imageCarte/c11.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(25, Trefle, Dame, "imageCarte/c12.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(26, Trefle, Roi, "imageCarte/c13.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(27, Carreau, As, "imageCarte/d01.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(28, Carreau, Deux, "imageCarte/d02.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(29, Carreau, Trois, "imageCarte/d03.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(30, Carreau, Quatre, "imageCarte/d04.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(31, Carreau, Cinq, "imageCarte/d05.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(32, Carreau, Six, "imageCarte/d06.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(33, Carreau, Sept, "imageCarte/d07.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(34, Carreau, Huit, "imageCarte/d08.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(35, Carreau, Neuf, "imageCarte/d09.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(36, Carreau, Dix, "imageCarte/d10.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(37, Carreau, Valet, "imageCarte/d11.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(38, Carreau, Dame, "imageCarte/d12.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(39, Carreau, Roi, "imageCarte/d13.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(40, Pique, As, "imageCarte/s01.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(41, Pique, Deux, "imageCarte/s02.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(42, Pique, Trois, "imageCarte/s03.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(43, Pique, Quatre, "imageCarte/s04.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(44, Pique, Cinq, "imageCarte/s05.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(45, Pique, Six, "imageCarte/s06.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(46, Pique, Sept, "imageCarte/s07.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(47, Pique, Huit, "imageCarte/s08.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(48, Pique, Neuf, "imageCarte/s09.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(49, Pique, Dix, "imageCarte/s10.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(50, Pique, Valet, "imageCarte/s11.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(51, Pique, Dame, "imageCarte/s12.ppm", pileMelange));
    pileMelange->ajouterCarte(new Carte(52, Pique, Roi, "imageCarte/s13.ppm", pileMelange));
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