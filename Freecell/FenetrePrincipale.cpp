//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"
#include "PileCarte.h"
#include "Bouton.h"
#include <fstream>

using namespace std;
using namespace cimg_library;

FenetrePrincipale::FenetrePrincipale() : tableauxIdentifiants(15, vector<int>(0)) {
    initialiserFond();
    //Declare un display pour afficher le fond
    disp = new CImgDisplay(*fond_, "FreeCell", 0, false, false);

    //Centrer la fenetre
    disp->move((CImgDisplay::screen_width() - disp->width()) / 2,
               (CImgDisplay::screen_height() - disp->height()) / 2);

    int choix;
    do {
        choix = afficherMenu();
        effacerFond();
        switch (choix) {
            case 0: {
                lancerJeu(true);
                disp->wait();
                sauvegarderPartie();
                quitterPartie();
                break;
            }

            case 1: {
                chargerPartie();
                lancerJeu(false);
                sauvegarderPartie();
                quitterPartie();

                disp->wait();
                break;
            }
            case 2:
                break;
        }
    } while (choix != 2 && !disp->is_closed() && !disp->is_keyESC() && !disp->is_keyQ());


}

void FenetrePrincipale::lancerJeu(bool nouvellePartie) {
    initialiserFond();
    dessinerEmplacementPiles();
    initialiserCartes();
    //Boucle Principale, ferme la fenetre si ESC or Q key is hit
    bool click_hold = false;
    int memoirePile = 0;
    if (!nouvellePartie) {
        initialiserPilesPostSauvegarde();
        traitementPostChargement();
        delete pileMelange;
    } else {
        initialiserPiles();
    }
    while (!disp->is_closed() && !disp->is_keyESC() && !disp->is_keyQ()) {

        //Recuperation positions de la souris
        //mx = position souris en x, my = position souris en y
        const int mx = disp->mouse_x() * (*fond_).width() / disp->width(),
                my = disp->mouse_y() * (*fond_).height() / disp->height();

        majAffichage();

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
                        (*piles)[pileCliquee]->deplacerCartePile(pileDeplacement);
                    }
                    click_hold = false;
                } else {//si le mouvement n'est pas valide, on remet la carte ou la pile sur la position de départ
                    pileDeplacement->inverserListeCartes();
                    int nbCartesAEnlever = pileDeplacement->getTaille();
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        if (memoirePile == -1)cout << "c'est ici putain" << endl;
                        (*piles)[memoirePile]->deplacerCartePile(pileDeplacement);
                    }
                }
                click_hold = false;
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
 *Renvoie un vecteur avec le numero de la pile suivie du numéro de la carte selon la position du ponteur de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 * @return vector<int> numero pile et numero carte
 */
vector<int> FenetrePrincipale::getClicPositions(int mx, int my) {

    vector<int> positions;
    positions.push_back(-1);
    positions.push_back(-1);

    //Cherche si il y a une carte qui correspond à la position de la souris dans les piles de Jeu
    for (unsigned int i = 0; i < piles->size(); i++) {
        positions[1] = (*piles)[i]->getClicPositionCarte(mx, my);
        if (positions[1] != -1) {
            positions[0] = i;
            return positions;
        }
    }

    //==================Partie utilisée dans le cas d'un dépôt  de carte=================================
    //Cherche si il y a une position Libre qui correspond à la position de la souris dans les piles Jeu
    for (unsigned int i = 0; i < piles->size(); i++) {
        int pileX1 = (*piles)[i]->getPosX();
        int pileX2 = (*piles)[i]->getPosX() + 74;
        int pileY1 = (*piles)[i]->getPosY();
        int pileY2 = (*piles)[i]->getPosY() + 99;
        if (mx >= pileX1 && mx <= pileX2 && my >= pileY1 && my <= pileY2) {
            positions[0] = i;
            positions[1] = -2;
            return positions;
        }
    }
    return positions;
}

/*!
 * Initialise les piles et répartie les cartes entre les différentes piles
 */
void FenetrePrincipale::initialiserPiles() {

    //Initialisation des piles
    piles = new vector<PileCarte *>;

    pileDeplacement = new PileCarte(0, 0, deplacement);

    pileJeu1 = new PileCarte(100, 300, jeu1);
    pileJeu2 = new PileCarte(235, 300, jeu2);
    pileJeu3 = new PileCarte(370, 300, jeu3);
    pileJeu4 = new PileCarte(505, 300, jeu4);
    pileJeu5 = new PileCarte(640, 300, jeu5);
    pileJeu6 = new PileCarte(775, 300, jeu6);
    pileJeu7 = new PileCarte(910, 300, jeu7);
    pileJeu8 = new PileCarte(1045, 300, jeu8);

    piles->push_back(pileJeu1);
    piles->push_back(pileJeu2);
    piles->push_back(pileJeu3);
    piles->push_back(pileJeu4);
    piles->push_back(pileJeu5);
    piles->push_back(pileJeu6);
    piles->push_back(pileJeu7);
    piles->push_back(pileJeu8);

    //Les cartes sont mélangés, repartition dans les listes de jeu
    pileMelange->brassagePile();

    for (unsigned int i = 0; i < 6; i++) {
        pileJeu1->deplacerCartePile(pileMelange);
        pileJeu2->deplacerCartePile(pileMelange);
        pileJeu3->deplacerCartePile(pileMelange);
        pileJeu4->deplacerCartePile(pileMelange);
        pileJeu5->deplacerCartePile(pileMelange);
        pileJeu6->deplacerCartePile(pileMelange);
        pileJeu7->deplacerCartePile(pileMelange);
        pileJeu8->deplacerCartePile(pileMelange);
    }
    pileJeu1->deplacerCartePile(pileMelange);
    pileJeu2->deplacerCartePile(pileMelange);
    pileJeu3->deplacerCartePile(pileMelange);
    pileJeu4->deplacerCartePile(pileMelange);

    pileLibre1 = new PileCarte(100, 50, libre1);
    pileLibre2 = new PileCarte(200, 50, libre2);
    pileLibre3 = new PileCarte(300, 50, libre3);
    pileLibre4 = new PileCarte(400, 50, libre4);

    pileValide1 = new PileCarte(780, 50, valide1);
    pileValide2 = new PileCarte(880, 50, valide2);
    pileValide3 = new PileCarte(980, 50, valide3);
    pileValide4 = new PileCarte(1080, 50, valide4);

    piles->push_back(pileLibre1);
    piles->push_back(pileLibre2);
    piles->push_back(pileLibre3);
    piles->push_back(pileLibre4);

    piles->push_back(pileValide1);
    piles->push_back(pileValide2);
    piles->push_back(pileValide3);
    piles->push_back(pileValide4);

    delete pileMelange;
}

void FenetrePrincipale::initialiserPilesPostSauvegarde() {
    //TODO Simplifier avec initialiser piles (ajotuer un parametre de chargement)
    //Initialisation des piles
    piles = new vector<PileCarte *>;
    pileDeplacement = new PileCarte(0, 0, deplacement);

    pileJeu1 = new PileCarte(100, 300, jeu1);
    pileJeu2 = new PileCarte(235, 300, jeu2);
    pileJeu3 = new PileCarte(370, 300, jeu3);
    pileJeu4 = new PileCarte(505, 300, jeu4);
    pileJeu5 = new PileCarte(640, 300, jeu5);
    pileJeu6 = new PileCarte(775, 300, jeu6);
    pileJeu7 = new PileCarte(910, 300, jeu7);
    pileJeu8 = new PileCarte(1045, 300, jeu8);

    piles->push_back(pileJeu1);
    piles->push_back(pileJeu2);
    piles->push_back(pileJeu3);
    piles->push_back(pileJeu4);
    piles->push_back(pileJeu5);
    piles->push_back(pileJeu6);
    piles->push_back(pileJeu7);
    piles->push_back(pileJeu8);

    pileLibre1 = new PileCarte(100, 50, libre1);
    pileLibre2 = new PileCarte(200, 50, libre2);
    pileLibre3 = new PileCarte(300, 50, libre3);
    pileLibre4 = new PileCarte(400, 50, libre4);

    pileValide1 = new PileCarte(780, 50, valide1);
    pileValide2 = new PileCarte(880, 50, valide2);
    pileValide3 = new PileCarte(980, 50, valide3);
    pileValide4 = new PileCarte(1080, 50, valide4);

    piles->push_back(pileLibre1);
    piles->push_back(pileLibre2);
    piles->push_back(pileLibre3);
    piles->push_back(pileLibre4);

    piles->push_back(pileValide1);
    piles->push_back(pileValide2);
    piles->push_back(pileValide3);
    piles->push_back(pileValide4);


}

/*!
 * Redessine chaque carte selon sa position
 */
void FenetrePrincipale::majAffichage() {
    visu_->draw_image(*fond_);

    //On affiche les différentes piles
    for (unsigned int i = 0; i < (*piles).size(); ++i) {
        int nbCarteADeplacer = (*piles)[i]->getTaille();
        for (unsigned int j = 0; j < nbCarteADeplacer; ++j) {
            visu_->draw_image((*piles)[i]->getCarte(j)->getPosX(), (*piles)[i]->getCarte(j)->getPosY(),
                              (*piles)[i]->getCarte(j)->getImg());
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

    auto *H01 = new Carte(1, Coeur, As, "imageCarte/h01.ppm", pileMelange);
    auto *H02 = new Carte(2, Coeur, Deux, "imageCarte/h02.ppm", pileMelange);
    auto *H03 = new Carte(3, Coeur, Trois, "imageCarte/h03.ppm", pileMelange);
    auto *H04 = new Carte(4, Coeur, Quatre, "imageCarte/h04.ppm", pileMelange);
    auto *H05 = new Carte(5, Coeur, Cinq, "imageCarte/h05.ppm", pileMelange);
    auto *H06 = new Carte(6, Coeur, Six, "imageCarte/h06.ppm", pileMelange);
    auto *H07 = new Carte(7, Coeur, Sept, "imageCarte/h07.ppm", pileMelange);
    auto *H08 = new Carte(8, Coeur, Huit, "imageCarte/h08.ppm", pileMelange);
    auto *H09 = new Carte(9, Coeur, Neuf, "imageCarte/h09.ppm", pileMelange);
    auto *H10 = new Carte(10, Coeur, Dix, "imageCarte/h10.ppm", pileMelange);
    auto *H11 = new Carte(11, Coeur, Valet, "imageCarte/h11.ppm", pileMelange);
    auto *H12 = new Carte(12, Coeur, Dame, "imageCarte/h12.ppm", pileMelange);
    auto *H13 = new Carte(13, Coeur, Roi, "imageCarte/h13.ppm", pileMelange);

    auto *C01 = new Carte(14, Trefle, As, "imageCarte/c01.ppm", pileMelange);
    auto *C02 = new Carte(15, Trefle, Deux, "imageCarte/c02.ppm", pileMelange);
    auto *C03 = new Carte(16, Trefle, Trois, "imageCarte/c03.ppm", pileMelange);
    auto *C04 = new Carte(17, Trefle, Quatre, "imageCarte/c04.ppm", pileMelange);
    auto *C05 = new Carte(18, Trefle, Cinq, "imageCarte/c05.ppm", pileMelange);
    auto *C06 = new Carte(19, Trefle, Six, "imageCarte/c06.ppm", pileMelange);
    auto *C07 = new Carte(20, Trefle, Sept, "imageCarte/c07.ppm", pileMelange);
    auto *C08 = new Carte(21, Trefle, Huit, "imageCarte/c08.ppm", pileMelange);
    auto *C09 = new Carte(22, Trefle, Neuf, "imageCarte/c09.ppm", pileMelange);
    auto *C10 = new Carte(23, Trefle, Dix, "imageCarte/c10.ppm", pileMelange);
    auto *C11 = new Carte(24, Trefle, Valet, "imageCarte/c11.ppm", pileMelange);
    auto *C12 = new Carte(25, Trefle, Dame, "imageCarte/c12.ppm", pileMelange);
    auto *C13 = new Carte(26, Trefle, Roi, "imageCarte/c13.ppm", pileMelange);

    auto *D01 = new Carte(27, Carreau, As, "imageCarte/d01.ppm", pileMelange);
    auto *D02 = new Carte(28, Carreau, Deux, "imageCarte/d02.ppm", pileMelange);
    auto *D03 = new Carte(29, Carreau, Trois, "imageCarte/d03.ppm", pileMelange);
    auto *D04 = new Carte(30, Carreau, Quatre, "imageCarte/d04.ppm", pileMelange);
    auto *D05 = new Carte(31, Carreau, Cinq, "imageCarte/d05.ppm", pileMelange);
    auto *D06 = new Carte(32, Carreau, Six, "imageCarte/d06.ppm", pileMelange);
    auto *D07 = new Carte(33, Carreau, Sept, "imageCarte/d07.ppm", pileMelange);
    auto *D08 = new Carte(34, Carreau, Huit, "imageCarte/d08.ppm", pileMelange);
    auto *D09 = new Carte(35, Carreau, Neuf, "imageCarte/d09.ppm", pileMelange);
    auto *D10 = new Carte(36, Carreau, Dix, "imageCarte/d10.ppm", pileMelange);
    auto *D11 = new Carte(37, Carreau, Valet, "imageCarte/d11.ppm", pileMelange);
    auto *D12 = new Carte(38, Carreau, Dame, "imageCarte/d12.ppm", pileMelange);
    auto *D13 = new Carte(39, Carreau, Roi, "imageCarte/d13.ppm", pileMelange);

    auto *S01 = new Carte(40, Pique, As, "imageCarte/s01.ppm", pileMelange);
    auto *S02 = new Carte(41, Pique, Deux, "imageCarte/s02.ppm", pileMelange);
    auto *S03 = new Carte(42, Pique, Trois, "imageCarte/s03.ppm", pileMelange);
    auto *S04 = new Carte(43, Pique, Quatre, "imageCarte/s04.ppm", pileMelange);
    auto *S05 = new Carte(44, Pique, Cinq, "imageCarte/s05.ppm", pileMelange);
    auto *S06 = new Carte(45, Pique, Six, "imageCarte/s06.ppm", pileMelange);
    auto *S07 = new Carte(46, Pique, Sept, "imageCarte/s07.ppm", pileMelange);
    auto *S08 = new Carte(47, Pique, Huit, "imageCarte/s08.ppm", pileMelange);
    auto *S09 = new Carte(48, Pique, Neuf, "imageCarte/s09.ppm", pileMelange);
    auto *S10 = new Carte(49, Pique, Dix, "imageCarte/s10.ppm", pileMelange);
    auto *S11 = new Carte(51, Pique, Valet, "imageCarte/s11.ppm", pileMelange);
    auto *S12 = new Carte(52, Pique, Dame, "imageCarte/s12.ppm", pileMelange);
    auto *S13 = new Carte(53, Pique, Roi, "imageCarte/s13.ppm", pileMelange);

    pileMelange->ajouterCarte(H01);
    pileMelange->ajouterCarte(H02);
    pileMelange->ajouterCarte(H03);
    pileMelange->ajouterCarte(H04);
    pileMelange->ajouterCarte(H05);
    pileMelange->ajouterCarte(H06);
    pileMelange->ajouterCarte(H07);
    pileMelange->ajouterCarte(H08);
    pileMelange->ajouterCarte(H09);
    pileMelange->ajouterCarte(H10);
    pileMelange->ajouterCarte(H11);
    pileMelange->ajouterCarte(H12);
    pileMelange->ajouterCarte(H13);

    pileMelange->ajouterCarte(D01);
    pileMelange->ajouterCarte(D02);
    pileMelange->ajouterCarte(D03);
    pileMelange->ajouterCarte(D04);
    pileMelange->ajouterCarte(D05);
    pileMelange->ajouterCarte(D06);
    pileMelange->ajouterCarte(D07);
    pileMelange->ajouterCarte(D08);
    pileMelange->ajouterCarte(D09);
    pileMelange->ajouterCarte(D10);
    pileMelange->ajouterCarte(D11);
    pileMelange->ajouterCarte(D12);
    pileMelange->ajouterCarte(D13);

    pileMelange->ajouterCarte(C01);
    pileMelange->ajouterCarte(C02);
    pileMelange->ajouterCarte(C03);
    pileMelange->ajouterCarte(C04);
    pileMelange->ajouterCarte(C05);
    pileMelange->ajouterCarte(C06);
    pileMelange->ajouterCarte(C07);
    pileMelange->ajouterCarte(C08);
    pileMelange->ajouterCarte(C09);
    pileMelange->ajouterCarte(C10);
    pileMelange->ajouterCarte(C11);
    pileMelange->ajouterCarte(C12);
    pileMelange->ajouterCarte(C13);

    pileMelange->ajouterCarte(S01);
    pileMelange->ajouterCarte(S02);
    pileMelange->ajouterCarte(S03);
    pileMelange->ajouterCarte(S04);
    pileMelange->ajouterCarte(S05);
    pileMelange->ajouterCarte(S06);
    pileMelange->ajouterCarte(S07);
    pileMelange->ajouterCarte(S08);
    pileMelange->ajouterCarte(S09);
    pileMelange->ajouterCarte(S10);
    pileMelange->ajouterCarte(S11);
    pileMelange->ajouterCarte(S12);
    pileMelange->ajouterCarte(S13);
}

/*!
 * Deplace un certain nombre de cartes dans la pile pileDeplacement selon la position de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 */
void FenetrePrincipale::deplacerPile(int mx, int my) {
    //récupère la position d'une carte dans les piles
    //Si vector = -1 -1 alors aucune carte n'a été cliquée
    vector<int> positions = getClicPositions(mx, my);

    //On change les cartes de pile si on a cliqué sur une carte
    if (positions[0] != -1) {
        //déplacement d'une ou de plusieurs cartes dans la pile déplacée
        int nbCarteAEnlever = (*piles)[positions[0]]->getTaille() - positions[1];
        for (unsigned int i = 0; i < nbCarteAEnlever; i++) {
            pileDeplacement->deplacerCartePile((*piles)[positions[0]]);
        }
        pileDeplacement->inverserListeCartes();
    }
}

bool FenetrePrincipale::estSaisieValide(int mx, int my) {

    vector<int> positionsCartecliquee = getClicPositions(mx, my);
    //On verifie si on a clique sur une pile qui serait vide, c'est à dire qu'il n'y a plus de cartes dedans
    //Laisser ce test en PREMIER, sinon on cherche à accéder à des éléments non existants

    if (positionsCartecliquee[0] == -1)return false;
    if (positionsCartecliquee[1] == -2 || positionsCartecliquee[0] == -1) {
        //La pile est VIDE (JEU ou LIBRES), on ne peut pas prendre de carte
        //OU
        //Aucune carte ne correspond à la position de la souris
        return false;
    } else {
        if (positionsCartecliquee[1] ==
            (*piles)[positionsCartecliquee[0]]->getTaille()) { return true; }// si il y a une seul carte return true
        else {
            bool validite = true;
            for (unsigned int k = (*piles)[positionsCartecliquee[0]]->getTaille() - 1;
                 k > positionsCartecliquee[1]; k--) {
                validite &= (*piles)[positionsCartecliquee[0]]->precedentEstValide(k);
            }
            return (validite);
        }
    }
	return false;
}

bool FenetrePrincipale::estDepotValide(int mx, int my) {
    //TODO -gérer le fait qu'on ne peut déposer qu'une seule carte sur les piles Libres
    vector<int> positionsCiblee = getClicPositions(mx, my);
    //bool validite = false;
    if (positionsCiblee[0] == -1) { return false; }
    else {
        //return true;//teste
        if ((*piles)[positionsCiblee[0]]->getType() > 1 && (*piles)[positionsCiblee[0]]->getType() < 10) {
            //si c'est une pile jeu
            if (pileDeplacement->getCarte(0)->getCouleur() % 2 !=
                (*piles)[positionsCiblee[0]]->getCarte((*piles)[positionsCiblee[0]]->getTaille() - 1)->getCouleur() %
                2 && pileDeplacement->getCarte(0)->getHauteur() == (*piles)[positionsCiblee[0]]->getCarte(
                    (*piles)[positionsCiblee[0]]->getTaille() - 1)->getHauteur() - 1) {
                // condition 1 : les couleurs sont oppsées
                // condition 2 : les hauteurs se suivent dans le bon ordre
                return true;
            } else { return false; }
        }
        if ((*piles)[positionsCiblee[0]]->getType() >= 10 && (*piles)[positionsCiblee[0]]->getType() <= 13) {
            // si c'est une pile libre
            if (pileDeplacement->getTaille() == 1 && (*piles)[positionsCiblee[0]]->getTaille() == 0) {
                return true;
            } else {
                return false;
            }

        }
        if ((*piles)[positionsCiblee[0]]->getType() >= 14 && (*piles)[positionsCiblee[0]]->getType() <= 17) {
            // si c'est une pile valide
            if (pileDeplacement->getTaille() == 1) {
                //si pris une seul carte
                if ((*piles)[positionsCiblee[0]]->getTaille() == 0) {
                    // si pile valide vide alors on accepte que des as
                    if (pileDeplacement->getCarte(0)->getHauteur() == As) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (pileDeplacement->getCarte(0)->getHauteur() == (*piles)[positionsCiblee[0]]->getCarte(
                            (*piles)[positionsCiblee[0]]->getTaille() - 1)->getHauteur() + 1 &&
                        pileDeplacement->getCarte(0)->getCouleur() == (*piles)[positionsCiblee[0]]->getCarte(
                                (*piles)[positionsCiblee[0]]->getTaille() - 1)->getCouleur()) {
                        //condition 1 : les hauteurs se succèdent
                        //condition 2 : les cartes sont de meme couleur
                        return true;
                    } else {
                        return false;
                    }
                }
            } else {
                return false;
            }
        }
		return false;
    }
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

void FenetrePrincipale::sauvegarderPartie() {
    //ESSAI SAUVEGARDE
    ofstream ofs("essai.txt");
    for (unsigned int i = 0; i < piles->size(); i++) {
        ofs << "PILE" << endl;
        ofs << (*piles)[i]->getTaille() << endl;
        for (unsigned int j = 0; j < (*piles)[i]->getTaille(); j++) {
            ofs << (*piles)[i]->getCarte(j)->getIdentifiant() << " ";
        }
        if ((*piles)[i]->getTaille() == 0) {
            ofs << 0 << " ";
        }
        ofs << endl;
    }
    ofs.close();
}

void FenetrePrincipale::chargerPartie() {
    ifstream ifs("essai.txt");
    ifs.seekg(0, std::ios::beg);//Debut du fichier
    string contenu;
    for (unsigned int i = 0; i < 15; i++) {
        if (!tableauxIdentifiants[i].empty()) {
            tableauxIdentifiants[i].clear();
        }
        getline(ifs, contenu);
        int taillePile;
        if (contenu == "PILE") {
            ifs >> taillePile;
            int iDcarte;
            for (unsigned int j = 0; j < taillePile; j++) {
                    ifs >> iDcarte;
                    tableauxIdentifiants[i].push_back(iDcarte);
            }
            if (taillePile == 0) {
                ifs >> iDcarte;//on balance dans le vide
            }
            ifs.ignore();
            ifs.ignore();
        }
    }
    ifs.close();
}

void FenetrePrincipale::traitementPostChargement() {
    for (unsigned int i = 0; i < 15; i++) {
        for (unsigned int j = 0; j < tableauxIdentifiants[i].size(); j++) {
            int idAchercher = tableauxIdentifiants[i][j];
            if (idAchercher == 0) {
                break;
            }
            int posPileMelange = -1;
            //On regarde dans la pile Melange pour trouver sa position
            posPileMelange = pileMelange->trouverPosCarteId(idAchercher);
            (*piles)[i]->deplacerCartePileAvecPosition((*piles)[i]->getTaille(), posPileMelange, pileMelange);
            etatChargement();
        }
    }
}

void FenetrePrincipale::etatChargement() {
//Debug
    //Liste souhaitée
    for (unsigned int x = 0; x < tableauxIdentifiants.size(); x++) {
        for (unsigned int y = 0; y < tableauxIdentifiants[x].size(); y++) {
            cout << tableauxIdentifiants[x][y] << " ";
        }
    }
    cout << endl;
    //Liste actuelle
    for (unsigned int k = 0; k < piles->size(); k++) {
        for (unsigned int l = 0; l < (*piles)[k]->getTaille(); l++) {
            cout << (*piles)[k]->getCarte(l)->getIdentifiant() << " ";
        }
    }
    cout << endl;
    cout << endl;
}

void FenetrePrincipale::quitterPartie() {
    delete visu_;
    delete plateau_;
    delete fond_;
    for (vector<PileCarte *>::iterator itPile = piles->begin(); itPile != piles->end(); ++itPile) {
        delete *itPile;
    }
    delete pileDeplacement;
}

