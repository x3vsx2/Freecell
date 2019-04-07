//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"
#include "pileCarte.h"

using namespace std;
using namespace cimg_library;

//TODO creer l'affichage principal
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
    unsigned  char coleurBlanche[3]={255,255,255};
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
    int p2 = 1280-100;
    for(unsigned int i = 0; i< 4; i++){
        fond_->draw_rectangle(p1+(100*i),50,p1+(100*i)+74,50+99,coleurBlanche, 1,  ~0U);
        fond_->draw_rectangle(p2-(100*i),50,p2-(100*i)-74,50+99,coleurBlanche, 1,  ~0U);
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
    pileJeu1 = new pileCarte(100, 300);
    pileJeu2 = new pileCarte(235, 300);
    pileJeu3 = new pileCarte(370, 300);
    pileJeu4 = new pileCarte(505, 300);
    pileJeu5 = new pileCarte(640, 300);
    pileJeu6 = new pileCarte(775, 300);
    pileJeu7 = new pileCarte(910, 300);
    pileJeu8 = new pileCarte(1045, 300);

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

    ////On affiche les différentes piles
    for (unsigned int i = 0; i < 6; ++i) {
        visu_->draw_image(pileJeu1->getCarte(i)->getPosX(), pileJeu1->getCarte(i)->getPosY(), pileJeu1->getCarte(i)->getImg());
        visu_->draw_image(pileJeu2->getCarte(i)->getPosX(), pileJeu2->getCarte(i)->getPosY(), pileJeu2->getCarte(i)->getImg());
        visu_->draw_image(pileJeu3->getCarte(i)->getPosX(), pileJeu3->getCarte(i)->getPosY(), pileJeu3->getCarte(i)->getImg());
        visu_->draw_image(pileJeu4->getCarte(i)->getPosX(), pileJeu4->getCarte(i)->getPosY(), pileJeu4->getCarte(i)->getImg());
        visu_->draw_image(pileJeu5->getCarte(i)->getPosX(), pileJeu5->getCarte(i)->getPosY(), pileJeu5->getCarte(i)->getImg());
        visu_->draw_image(pileJeu6->getCarte(i)->getPosX(), pileJeu6->getCarte(i)->getPosY(), pileJeu6->getCarte(i)->getImg());
        visu_->draw_image(pileJeu7->getCarte(i)->getPosX(), pileJeu7->getCarte(i)->getPosY(), pileJeu7->getCarte(i)->getImg());
//
    }
    visu_->draw_image(pileJeu1->getCarte(6)->getPosX(), pileJeu1->getCarte(6)->getPosY(), pileJeu1->getCarte(6)->getImg());
    visu_->draw_image(pileJeu2->getCarte(6)->getPosX(), pileJeu2->getCarte(6)->getPosY(), pileJeu2->getCarte(6)->getImg());
    visu_->draw_image(pileJeu3->getCarte(6)->getPosX(), pileJeu3->getCarte(6)->getPosY(), pileJeu3->getCarte(6)->getImg());
    visu_->draw_image(pileJeu4->getCarte(6)->getPosX(), pileJeu4->getCarte(6)->getPosY(), pileJeu4->getCarte(6)->getImg());

}

void FenetrePrincipale::initialiserCartes() {
    pileMelange = new pileCarte();

   auto *H01 = new CarteKamil(Coeur, As, "../imageCarte/h01.ppm", pileMelange);
   auto *H02 = new CarteKamil(Coeur, Deux, "../imageCarte/h02.ppm", pileMelange);
   auto *H03 = new CarteKamil(Coeur, Trois, "../imageCarte/h03.ppm", pileMelange);
   auto *H04 = new CarteKamil(Coeur, Quatre, "../imageCarte/h04.ppm", pileMelange);
   auto *H05 = new CarteKamil(Coeur, Cinq, "../imageCarte/h05.ppm", pileMelange);
   auto *H06 = new CarteKamil(Coeur, Six, "../imageCarte/h06.ppm", pileMelange);
   auto *H07 = new CarteKamil(Coeur, Sept, "../imageCarte/h07.ppm", pileMelange);
   auto *H08 = new CarteKamil(Coeur, Huit, "../imageCarte/h08.ppm", pileMelange);
   auto *H09 = new CarteKamil(Coeur, Neuf, "../imageCarte/h09.ppm", pileMelange);
   auto *H10 = new CarteKamil(Coeur, Dix, "../imageCarte/h10.ppm", pileMelange);
   auto *H11 = new CarteKamil(Coeur, Valet, "../imageCarte/h11.ppm", pileMelange);
   auto *H12 = new CarteKamil(Coeur, Dame, "../imageCarte/h12.ppm", pileMelange);
   auto *H13 = new CarteKamil(Coeur, Roi, "../imageCarte/h13.ppm", pileMelange);
   auto *C01 = new CarteKamil(Trefle, As, "../imageCarte/c01.ppm", pileMelange);
   auto *C02 = new CarteKamil(Trefle, Deux, "../imageCarte/c02.ppm", pileMelange);
   auto *C03 = new CarteKamil(Trefle, Trois, "../imageCarte/c03.ppm", pileMelange);
   auto *C04 = new CarteKamil(Trefle, Quatre, "../imageCarte/c04.ppm", pileMelange);
   auto *C05 = new CarteKamil(Trefle, Cinq, "../imageCarte/c05.ppm", pileMelange);
   auto *C06 = new CarteKamil(Trefle, Six, "../imageCarte/c06.ppm", pileMelange);
   auto *C07 = new CarteKamil(Trefle, Sept, "../imageCarte/c07.ppm", pileMelange);
   auto *C08 = new CarteKamil(Trefle, Huit, "../imageCarte/c08.ppm", pileMelange);
   auto *C09 = new CarteKamil(Trefle, Neuf, "../imageCarte/c09.ppm", pileMelange);
   auto *C10 = new CarteKamil(Trefle, Dix, "../imageCarte/c10.ppm", pileMelange);
   auto *C11 = new CarteKamil(Trefle, Valet, "../imageCarte/c11.ppm", pileMelange);
   auto *C12 = new CarteKamil(Trefle, Dame, "../imageCarte/c12.ppm", pileMelange);
   auto *C13 = new CarteKamil(Trefle, Roi, "../imageCarte/c13.ppm", pileMelange);

    auto *D01 = new CarteKamil(Carreau, As, "../imageCarte/d01.ppm", pileMelange);
    auto *D02 = new CarteKamil(Carreau, Deux, "../imageCarte/d02.ppm", pileMelange);
    auto *D03 = new CarteKamil(Carreau, Trois, "../imageCarte/d03.ppm", pileMelange);
    auto *D04 = new CarteKamil(Carreau, Quatre, "../imageCarte/d04.ppm", pileMelange);
    auto *D05 = new CarteKamil(Carreau, Cinq, "../imageCarte/d05.ppm", pileMelange);
    auto *D06 = new CarteKamil(Carreau, Six, "../imageCarte/d06.ppm", pileMelange);
    auto *D07 = new CarteKamil(Carreau, Sept, "../imageCarte/d07.ppm", pileMelange);
    auto *D08 = new CarteKamil(Carreau, Huit, "../imageCarte/d08.ppm", pileMelange);
    auto *D09 = new CarteKamil(Carreau, Neuf, "../imageCarte/d09.ppm", pileMelange);
    auto *D10 = new CarteKamil(Carreau, Dix, "../imageCarte/d10.ppm", pileMelange);
    auto *D11 = new CarteKamil(Carreau, Valet, "../imageCarte/d11.ppm", pileMelange);
    auto *D12 = new CarteKamil(Carreau, Dame, "../imageCarte/d12.ppm", pileMelange);
    auto *D13 = new CarteKamil(Carreau, Roi, "../imageCarte/d13.ppm", pileMelange);
    auto *S01 = new CarteKamil(Pique, As, "../imageCarte/s01.ppm", pileMelange);
    auto *S02 = new CarteKamil(Pique, Deux, "../imageCarte/s02.ppm", pileMelange);
    auto *S03 = new CarteKamil(Pique, Trois, "../imageCarte/s03.ppm", pileMelange);
    auto *S04 = new CarteKamil(Pique, Quatre, "../imageCarte/s04.ppm", pileMelange);
    auto *S05 = new CarteKamil(Pique, Cinq, "../imageCarte/s05.ppm", pileMelange);
    auto *S06 = new CarteKamil(Pique, Six, "../imageCarte/s06.ppm", pileMelange);
    auto *S07 = new CarteKamil(Pique, Sept, "../imageCarte/s07.ppm", pileMelange);
    auto *S08 = new CarteKamil(Pique, Huit, "../imageCarte/s08.ppm", pileMelange);
    auto *S09 = new CarteKamil(Pique, Neuf, "../imageCarte/s09.ppm", pileMelange);
    auto *S10 = new CarteKamil(Pique, Dix, "../imageCarte/s10.ppm", pileMelange);
    auto *S11 = new CarteKamil(Pique, Valet, "../imageCarte/s11.ppm", pileMelange);
    auto *S12 = new CarteKamil(Pique, Dame, "../imageCarte/s12.ppm", pileMelange);
    auto *S13 = new CarteKamil(Pique, Roi, "../imageCarte/s13.ppm", pileMelange);

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