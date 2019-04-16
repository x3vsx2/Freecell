//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"
#include "PileCarte.h"


using namespace std;
using namespace cimg_library;

FenetrePrincipale::FenetrePrincipale() {

    initialiserFond();

    //Declare un display pour afficher le fond
    CImgDisplay disp(*fond_, "FreeCell", 0, false, false);

    //Centrer la fenetre
    disp.move((CImgDisplay::screen_width() - disp.width()) / 2,
              (CImgDisplay::screen_height() - disp.height()) / 2);

    initialiserCartes();
    placerCartes();

    //Boucle Principale, ferme la fenetre si ESC or Q key is hit

    bool click_hold = false;
    while (!disp.is_closed() && !disp.is_keyESC() && !disp.is_keyQ()) {

        //Recuperation positions de la souris
        //mx = position souris en x, my = position souris en y
        const int mx = disp.mouse_x() * (*fond_).width() / disp.width(),
                my = disp.mouse_y() * (*fond_).height() / disp.height();

        majAffichage();

        // Mouvement souris suite à un déplacement
        if (disp.button()) {//Test si clique ET clique sur une carte

            //On recupere la pile qui a été cliquée, réutilisation si le mouvement n'est pas valide
            int temp = testClicCarteFenetre(mx, my)[0];
            if (click_hold == false) {
                cout << "Clic Bloqué" << endl;

                //Déplacement des cartes dans la pile pileDeplacement
				if(estSaisieValide(mx,my))
                deplacerPile(mx, my);

                click_hold = true;
            } else {//Dépot de la pile pileDeplacement
                cout << "Clic Débloqué" << endl;
                if (estDepotValide(mx, my)) {
                    int pileCliquee = testClicCarteFenetre(mx, my)[0]; //numéro de la pile sur laquelle il y a eu un clic
                    pileDeplacement->inverserListeCartes();
                    int nbCartesAEnlever = pileDeplacement->getTaille();
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        (*pilesJeu)[pileCliquee]->deplacerCartePile(pileDeplacement);
                    }
                    click_hold = false;
                } //else {//si le mouvement n'est pas valide, on remet au départ //non car tu ne sais pas d'où viennent les cartes
                //pileDeplacement->inverserListeCartes();
                //int nbCartesAEnlever = pileDeplacement->getTaille();
                //  for (unsigned int i = 0; i < pileDeplacement->getTaille(); i++) {
                //      (*pilesJeu)[temp]->deplacerCartePile(pileDeplacement);
                //  }
                //}
                //click_hold = false;
            }
        }

        if (click_hold && pileDeplacement->getTaille() != 0) {
            pileDeplacement->changerPositionPile(mx, my); //Met à jour la position de la pileDeplacement
        }

        visu_->display(disp);
        disp.wait();
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
    unsigned char coleurBlanche[3] = {255, 255, 255};
    /*
     *x0	X-coordinate of the upper-left rectangle corner.
     *y0	Y-coordinate of the upper-left rectangle corner.
     *x1	X-coordinate of the lower-right rectangle corner.
     *y1	Y-coordinate of the lower-right rectangle corner.
     *color	Pointer to spectrum() consecutive values of type T, defining the drawing color.
     *opacity	Drawing opacity.
     * patern
     */
    int p1 = 100;
    int p2 = 1280 - 100;
    for (unsigned int i = 0; i < 4; i++) {
        fond_->draw_rectangle(p1 + (100 * i), 50, p1 + (100 * i) + 74, 50 + 99, coleurBlanche, 1, ~0U);
        fond_->draw_rectangle(p2 - (100 * i), 50, p2 - (100 * i) - 74, 50 + 99, coleurBlanche, 1, ~0U);
    }
    visu_ = new CImg<unsigned char>(*fond_);
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
vector<int> FenetrePrincipale::testClicCarteFenetre(int mx, int my) {

    vector<int> positions;
    positions.push_back(-1);
    positions.push_back(-1);

    for (unsigned int i = 0; i < pilesJeu->size(); i++) {
        positions[1] = (*pilesJeu)[i]->testClicCarte(mx, my);
        if (positions[1] != -1) {
            positions[0] = i;
            break;
        }
    }
    return positions;
}

/*!
 * Initialise les piles et répartie les cartes entre les différentes piles
 */
void FenetrePrincipale::placerCartes() {

    //Initialisation des piles
    pilesJeu = new vector<PileCarte *>;
    pileDeplacement = new PileCarte(0, 0, deplacement);

    pileJeu1 = new PileCarte(100, 300, jeu1);
    pileJeu2 = new PileCarte(235, 300, jeu2);
    pileJeu3 = new PileCarte(370, 300, jeu3);
    pileJeu4 = new PileCarte(505, 300, jeu4);
    pileJeu5 = new PileCarte(640, 300, jeu5);
    pileJeu6 = new PileCarte(775, 300, jeu6);
    pileJeu7 = new PileCarte(910, 300, jeu7);
    pileJeu8 = new PileCarte(1045, 300, jeu8);

    pilesJeu->push_back(pileJeu1);
    pilesJeu->push_back(pileJeu2);
    pilesJeu->push_back(pileJeu3);
    pilesJeu->push_back(pileJeu4);
    pilesJeu->push_back(pileJeu5);
    pilesJeu->push_back(pileJeu6);
    pilesJeu->push_back(pileJeu7);
    pilesJeu->push_back(pileJeu8);

    //Les cartes sont mélangés, repartition dans les listes de jeu
	pileMelange->brassagePile();

    for (unsigned int i = 0; i < 6; i++) { //TODO gérer les cas sept et six
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

}

/*!
 * Redessine chaque carte selon sa position
 */
void FenetrePrincipale::majAffichage() {
    visu_->draw_image(*fond_);

    //On affiche les différentes piles
    for (unsigned int i = 0; i < (*pilesJeu).size(); ++i) {
        for (unsigned int j = 0; j < (*pilesJeu)[i]->getTaille(); ++j) {
            visu_->draw_image((*pilesJeu)[i]->getCarte(j)->getPosX(), (*pilesJeu)[i]->getCarte(j)->getPosY(),
                              (*pilesJeu)[i]->getCarte(j)->getImg());
        }
    }
    for (unsigned int k = 0; k < pileDeplacement->getTaille(); k++) {
        visu_->draw_image(pileDeplacement->getCarte(k)->getPosX(), pileDeplacement->getCarte(k)->getPosY(),
                          pileDeplacement->getCarte(k)->getImg());
    }

}

/*!
 * Initialise les cartes et ajout dans pileMelange
 */
void FenetrePrincipale::initialiserCartes() {
    pileMelange = new PileCarte(0, 0, melange);

    auto *H01 = new Carte(Coeur, As, "imageCarte/h01.ppm", pileMelange);
    auto *H02 = new Carte(Coeur, Deux, "imageCarte/h02.ppm", pileMelange);
    auto *H03 = new Carte(Coeur, Trois, "imageCarte/h03.ppm", pileMelange);
    auto *H04 = new Carte(Coeur, Quatre, "imageCarte/h04.ppm", pileMelange);
    auto *H05 = new Carte(Coeur, Cinq, "imageCarte/h05.ppm", pileMelange);
    auto *H06 = new Carte(Coeur, Six, "imageCarte/h06.ppm", pileMelange);
    auto *H07 = new Carte(Coeur, Sept, "imageCarte/h07.ppm", pileMelange);
    auto *H08 = new Carte(Coeur, Huit, "imageCarte/h08.ppm", pileMelange);
    auto *H09 = new Carte(Coeur, Neuf, "imageCarte/h09.ppm", pileMelange);
    auto *H10 = new Carte(Coeur, Dix, "imageCarte/h10.ppm", pileMelange);
    auto *H11 = new Carte(Coeur, Valet, "imageCarte/h11.ppm", pileMelange);
    auto *H12 = new Carte(Coeur, Dame, "imageCarte/h12.ppm", pileMelange);
    auto *H13 = new Carte(Coeur, Roi, "imageCarte/h13.ppm", pileMelange);
    auto *C01 = new Carte(Trefle, As, "imageCarte/c01.ppm", pileMelange);
    auto *C02 = new Carte(Trefle, Deux, "imageCarte/c02.ppm", pileMelange);
    auto *C03 = new Carte(Trefle, Trois, "imageCarte/c03.ppm", pileMelange);
    auto *C04 = new Carte(Trefle, Quatre, "imageCarte/c04.ppm", pileMelange);
    auto *C05 = new Carte(Trefle, Cinq, "imageCarte/c05.ppm", pileMelange);
    auto *C06 = new Carte(Trefle, Six, "imageCarte/c06.ppm", pileMelange);
    auto *C07 = new Carte(Trefle, Sept, "imageCarte/c07.ppm", pileMelange);
    auto *C08 = new Carte(Trefle, Huit, "imageCarte/c08.ppm", pileMelange);
    auto *C09 = new Carte(Trefle, Neuf, "imageCarte/c09.ppm", pileMelange);
    auto *C10 = new Carte(Trefle, Dix, "imageCarte/c10.ppm", pileMelange);
    auto *C11 = new Carte(Trefle, Valet, "imageCarte/c11.ppm", pileMelange);
    auto *C12 = new Carte(Trefle, Dame, "imageCarte/c12.ppm", pileMelange);
    auto *C13 = new Carte(Trefle, Roi, "imageCarte/c13.ppm", pileMelange);

    auto *D01 = new Carte(Carreau, As, "imageCarte/d01.ppm", pileMelange);
    auto *D02 = new Carte(Carreau, Deux, "imageCarte/d02.ppm", pileMelange);
    auto *D03 = new Carte(Carreau, Trois, "imageCarte/d03.ppm", pileMelange);
    auto *D04 = new Carte(Carreau, Quatre, "imageCarte/d04.ppm", pileMelange);
    auto *D05 = new Carte(Carreau, Cinq, "imageCarte/d05.ppm", pileMelange);
    auto *D06 = new Carte(Carreau, Six, "imageCarte/d06.ppm", pileMelange);
    auto *D07 = new Carte(Carreau, Sept, "imageCarte/d07.ppm", pileMelange);
    auto *D08 = new Carte(Carreau, Huit, "imageCarte/d08.ppm", pileMelange);
    auto *D09 = new Carte(Carreau, Neuf, "imageCarte/d09.ppm", pileMelange);
    auto *D10 = new Carte(Carreau, Dix, "imageCarte/d10.ppm", pileMelange);
    auto *D11 = new Carte(Carreau, Valet, "imageCarte/d11.ppm", pileMelange);
    auto *D12 = new Carte(Carreau, Dame, "imageCarte/d12.ppm", pileMelange);
    auto *D13 = new Carte(Carreau, Roi, "imageCarte/d13.ppm", pileMelange);
    auto *S01 = new Carte(Pique, As, "imageCarte/s01.ppm", pileMelange);
    auto *S02 = new Carte(Pique, Deux, "imageCarte/s02.ppm", pileMelange);
    auto *S03 = new Carte(Pique, Trois, "imageCarte/s03.ppm", pileMelange);
    auto *S04 = new Carte(Pique, Quatre, "imageCarte/s04.ppm", pileMelange);
    auto *S05 = new Carte(Pique, Cinq, "imageCarte/s05.ppm", pileMelange);
    auto *S06 = new Carte(Pique, Six, "imageCarte/s06.ppm", pileMelange);
    auto *S07 = new Carte(Pique, Sept, "imageCarte/s07.ppm", pileMelange);
    auto *S08 = new Carte(Pique, Huit, "imageCarte/s08.ppm", pileMelange);
    auto *S09 = new Carte(Pique, Neuf, "imageCarte/s09.ppm", pileMelange);
    auto *S10 = new Carte(Pique, Dix, "imageCarte/s10.ppm", pileMelange);
    auto *S11 = new Carte(Pique, Valet, "imageCarte/s11.ppm", pileMelange);
    auto *S12 = new Carte(Pique, Dame, "imageCarte/s12.ppm", pileMelange);
    auto *S13 = new Carte(Pique, Roi, "imageCarte/s13.ppm", pileMelange);

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

    pileMelange->melangerCartes();
}

/*!
 * Deplace un certain nombre de cartes dans la pile pileDeplacement selon la position de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 */
void FenetrePrincipale::deplacerPile(int mx, int my) {
    //récupère la position d'une carte dans les piles
    //Si vector = -1 -1 alors aucune carte n'a été cliquée
    vector<int> positions = testClicCarteFenetre(mx, my);

    //on change les cartes de pile si on a cliqué sur une carte
    if (positions[0] != -1) {
        //déplacement d'une ou de plusieurs cartes dans la pile déplacée
        int nbCarteAEnlever = (*pilesJeu)[positions[0]]->getTaille() - positions[1];
        for (unsigned int i = 0; i < nbCarteAEnlever; i++) {
            pileDeplacement->deplacerCartePile((*pilesJeu)[positions[0]]);
        }
        pileDeplacement->inverserListeCartes();
    }
}



bool FenetrePrincipale::estSaisieValide(int mx, int my) {

	vector<int> positionsCartecliquee = testClicCarteFenetre(mx, my);
	if (positionsCartecliquee[0] == -1) { return false; }
	else {
		if (positionsCartecliquee[1] == (*pilesJeu)[positionsCartecliquee[0]]->getTaille()) { return true; }// si il y a une seul carte return true
		else {
			//return true;// a retirer quand les carte seront mélangées
			bool validite = true;
			for (unsigned int k = (*pilesJeu)[positionsCartecliquee[0]]->getTaille() - 1; k > positionsCartecliquee[1]; k--) {
				validite &= (*pilesJeu)[positionsCartecliquee[0]]->precedentEstValide(k);
			}
			return(validite);
		}
	}
}

bool FenetrePrincipale::estDepotValide(int mx, int my) {
	vector<int> positionsCartecliquee = testClicCarteFenetre(mx, my);
	if (positionsCartecliquee[0] != -1) {
		return true;
	}
	else {
		return false;
	}
}


bool FenetrePrincipale::mouvementValide(int mx, int my) {
    //TODO ajouter les fonctions qui vérifient si le moouvement de pile est autorisé

    
	vector<int> positionsCartecliquee = testClicCarteFenetre(mx, my);
	//if (positionsCartecliquee[0] == -1) { return false; }
	//else {
	//	if (positionsCartecliquee[1] == (*pilesJeu)[positionsCartecliquee[0]]->getTaille()) { return true; }
	//	else {
	//		//return true;// a retirer quand les carte seront mélangées
	//		bool validite = true;
	//		for (unsigned int k = (*pilesJeu)[positionsCartecliquee[1]]->getTaille() - 1; k > positionsCartecliquee[1]; k--) {
	//			validite &= (*pilesJeu)[positionsCartecliquee[1]]->precedentEstValide(k);
	//		}
	//		return(validite);
	//	}
	//}

    if (positionsCartecliquee[0] != -1) {
        return true;
    } else {
        return false;
    }
}


