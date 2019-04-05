//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"
#include "pileCarte.h"
#include "CarteKamil.h"

using namespace std;
using namespace cimg_library;

//TODO creer l'affichage principal
FenetrePrincipale::FenetrePrincipale() {

    initialiserFond();

    CarteKamil carteTest(Trefle, As, "../imageCarte/c01.ppm");

    //Declare un display pour afficher le fond
    CImgDisplay disp(*fond_, "FreeCell", 0, false, false);

    //Centrer la fenetre
    disp.move((CImgDisplay::screen_width() - disp.width()) / 2,
              (CImgDisplay::screen_height() - disp.height()) / 2);

    initialiserCartes();
    placerCartes();

    //Boucle Principale, ferme la fenetre si ESC or Q key is hit

    while (!disp.is_closed() && !disp.is_keyESC() && !disp.is_keyQ()) {

        //mx = position souris en x, my = position souris en y
        const int mx = disp.mouse_x() * (*fond_).width() / disp.width(),
                my = disp.mouse_y() * (*fond_).height() / disp.height();

        // Mouvement souris suite à un déplacement //TODO gérer le clique
        if (!disp.button()) {
        }

        visu_->display(disp);
        disp.wait();


    }
}

/*!
 *Initialise le plateau, le fond et visu
 */
void FenetrePrincipale::initialiserFond() {
    //declare le plateau de jeu avec longeurxlargeur
    plateau_ = new CImg<unsigned char>(1280, 720, 1, 1, 0);
    fond_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(), 1, 3, 0);
    colorierImage(*fond_, 26, 83, 92);
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

void FenetrePrincipale::testClicCarte() {

}

//TODO mise a jour de la position des cartes
void FenetrePrincipale::afficherCartes() {
    //for(unsigned int i = 0; i<toutesLesCartes.size();i++){
    //visu_->draw_image()
    //}
}

void FenetrePrincipale::placerCartes() {
    //TODO positionner les cartes correctement au départ, idées : créer des positons prédéfinies

    //Définitions des piles
    pileJeu1 = new pileCarte(100, 500);
    pileJeu2 = new pileCarte(200, 500);
    pileJeu3 = new pileCarte(300, 500);
    pileJeu4 = new pileCarte(400, 500);
    pileJeu5 = new pileCarte(500, 500);
    pileJeu6 = new pileCarte(600, 500);
    pileJeu7 = new pileCarte(700, 500);
    pileJeu8 = new pileCarte(800, 500);

    //Les cartes sont déja mélangés, repartition dans les listes de jeu
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



    //On affiche les différentes piles
    for (unsigned int i = 0; i < 6; ++i) {
        visu_->draw_image(pileJeu1->getPosX(), pileJeu1->getPosY() + i * 20, pileJeu1->getImg(i));
        visu_->draw_image(pileJeu2->getPosX(), pileJeu2->getPosY() + i * 20, pileJeu2->getImg(i));
        visu_->draw_image(pileJeu3->getPosX(), pileJeu3->getPosY() + i * 20, pileJeu3->getImg(i));
        visu_->draw_image(pileJeu4->getPosX(), pileJeu4->getPosY() + i * 20, pileJeu4->getImg(i));
        visu_->draw_image(pileJeu5->getPosX(), pileJeu5->getPosY() + i * 20, pileJeu5->getImg(i));
        visu_->draw_image(pileJeu6->getPosX(), pileJeu6->getPosY() + i * 20, pileJeu6->getImg(i));
        visu_->draw_image(pileJeu7->getPosX(), pileJeu7->getPosY() + i * 20, pileJeu7->getImg(i));
        visu_->draw_image(pileJeu8->getPosX(), pileJeu8->getPosY() + i * 20, pileJeu8->getImg(i));
    }

    visu_->draw_image(pileJeu1->getPosX(), pileJeu1->getPosY() + 6 * 20, pileJeu1->getImg(6));
    visu_->draw_image(pileJeu2->getPosX(), pileJeu2->getPosY() + 6 * 20, pileJeu2->getImg(6));
    visu_->draw_image(pileJeu3->getPosX(), pileJeu3->getPosY() + 6 * 20, pileJeu3->getImg(6));
    visu_->draw_image(pileJeu4->getPosX(), pileJeu4->getPosY() + 6 * 20, pileJeu4->getImg(6));

}

void FenetrePrincipale::initialiserCartes() {
    pileMelange = new pileCarte();

    CarteKamil H01(Coeur, As, "../imageCarte/h01.ppm");
    CarteKamil H02(Coeur, Deux, "../imageCarte/h02.ppm");
    CarteKamil H03(Coeur, Trois, "../imageCarte/h03.ppm");
    CarteKamil H04(Coeur, Quatre, "../imageCarte/h04.ppm");
    CarteKamil H05(Coeur, Cinq, "../imageCarte/h05.ppm");
    CarteKamil H06(Coeur, Six, "../imageCarte/h06.ppm");
    CarteKamil H07(Coeur, Sept, "../imageCarte/h07.ppm");
    CarteKamil H08(Coeur, Huit, "../imageCarte/h08.ppm");
    CarteKamil H09(Coeur, Neuf, "../imageCarte/h09.ppm");
    CarteKamil H10(Coeur, Dix, "../imageCarte/h10.ppm");
    CarteKamil H11(Coeur, Valet, "../imageCarte/h11.ppm");
    CarteKamil H12(Coeur, Dame, "../imageCarte/h12.ppm");
    CarteKamil H13(Coeur, Roi, "../imageCarte/h13.ppm");

    CarteKamil C01(Trefle, As, "../imageCarte/c01.ppm");
    CarteKamil C02(Trefle, Deux, "../imageCarte/c02.ppm");
    CarteKamil C03(Trefle, Trois, "../imageCarte/c03.ppm");
    CarteKamil C04(Trefle, Quatre, "../imageCarte/c04.ppm");
    CarteKamil C05(Trefle, Cinq, "../imageCarte/c05.ppm");
    CarteKamil C06(Trefle, Six, "../imageCarte/c06.ppm");
    CarteKamil C07(Trefle, Sept, "../imageCarte/c07.ppm");
    CarteKamil C08(Trefle, Huit, "../imageCarte/c08.ppm");
    CarteKamil C09(Trefle, Neuf, "../imageCarte/c09.ppm");
    CarteKamil C10(Trefle, Dix, "../imageCarte/c10.ppm");
    CarteKamil C11(Trefle, Valet, "../imageCarte/c11.ppm");
    CarteKamil C12(Trefle, Dame, "../imageCarte/c12.ppm");
    CarteKamil C13(Trefle, Roi, "../imageCarte/c13.ppm");

    CarteKamil D01(Carreau, As, "../imageCarte/d01.ppm");
    CarteKamil D02(Carreau, Deux, "../imageCarte/d02.ppm");
    CarteKamil D03(Carreau, Trois, "../imageCarte/d03.ppm");
    CarteKamil D04(Carreau, Quatre, "../imageCarte/d04.ppm");
    CarteKamil D05(Carreau, Cinq, "../imageCarte/d05.ppm");
    CarteKamil D06(Carreau, Six, "../imageCarte/d06.ppm");
    CarteKamil D07(Carreau, Sept, "../imageCarte/d07.ppm");
    CarteKamil D08(Carreau, Huit, "../imageCarte/d08.ppm");
    CarteKamil D09(Carreau, Neuf, "../imageCarte/d09.ppm");
    CarteKamil D10(Carreau, Dix, "../imageCarte/d10.ppm");
    CarteKamil D11(Carreau, Valet, "../imageCarte/d11.ppm");
    CarteKamil D12(Carreau, Dame, "../imageCarte/d12.ppm");
    CarteKamil D13(Carreau, Roi, "../imageCarte/d13.ppm");

    CarteKamil S01(Pique, As, "../imageCarte/s01.ppm");
    CarteKamil S02(Pique, Deux, "../imageCarte/s02.ppm");
    CarteKamil S03(Pique, Trois, "../imageCarte/s03.ppm");
    CarteKamil S04(Pique, Quatre, "../imageCarte/s04.ppm");
    CarteKamil S05(Pique, Cinq, "../imageCarte/s05.ppm");
    CarteKamil S06(Pique, Six, "../imageCarte/s06.ppm");
    CarteKamil S07(Pique, Sept, "../imageCarte/s07.ppm");
    CarteKamil S08(Pique, Huit, "../imageCarte/s08.ppm");
    CarteKamil S09(Pique, Neuf, "../imageCarte/s09.ppm");
    CarteKamil S10(Pique, Dix, "../imageCarte/s10.ppm");
    CarteKamil S11(Pique, Valet, "../imageCarte/s11.ppm");
    CarteKamil S12(Pique, Dame, "../imageCarte/s12.ppm");
    CarteKamil S13(Pique, Roi, "../imageCarte/s13.ppm");

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