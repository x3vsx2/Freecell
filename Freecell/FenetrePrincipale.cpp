//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"
#include "Carte.h"
using namespace std;
using namespace cimg_library;

//TODO creer l'affichage principal
FenetrePrincipale::FenetrePrincipale() {

    initialiserFond();

    Carte carteTest(Trefle, As, "../imageCarte/c01.ppm");

    //Declare un display pour afficher le fond
    CImgDisplay disp(*fond_,"FreeCell",0,false,false);

    //Centrer la fenetre
    disp.move((CImgDisplay::screen_width() - disp.width())/2,
              (CImgDisplay::screen_height() - disp.height())/2);

    initialiserCartes();
    afficherCartes();
    //Boucle Principale, ferme la fenetre si ESC or Q key is hit
    while (!disp.is_closed() && !disp.is_keyESC() && !disp.is_keyQ()) {

        //mx = position souris en x, my = position souris en y
        const int mx = disp.mouse_x()*(*fond_).width()/disp.width(),
        my = disp.mouse_y()*(*fond_).height()/disp.height();

        // Mouvement souris suite à un déplacement
        if (!disp.button()) {
        }

        visu_->draw_image(mx, my, carteTest);


        visu_->display(disp);
        disp.wait();


    }
}

/*!
 *Initialise le plateau, le fond et visu
 */
void FenetrePrincipale::initialiserFond() {
    //declare le plateau de jeu avec longeurxlargeur
    plateau_ = new CImg<unsigned char> (1280,720,1,1,0);
    fond_ = new CImg<unsigned char> ((*plateau_).width(), (*plateau_).height(),1,3,0);
    colorierImage(*fond_, 26, 83, 92);
    visu_ = new CImg<unsigned char> (*fond_);
    //nplateau_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(),1,3,0);
    //next_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(),1,3,0);
    //next_mask_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(),1,3,0);

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

    cimg_forXY(img,x,y){
        //Rouge
        img(x,y,0,0) = r;
        //Vert
        img(x,y,0,1) = g;
        //Bleu
        img(x,y,0,2) = b;

    }
}


void FenetrePrincipale::testClicCarte() {

}

void FenetrePrincipale::afficherCartes(){
    for(unsigned int i = 0; i<toutesLesCartes.size();i++){
        //visu_->draw_image()
    }
}

void FenetrePrincipale::placerCartes() {
    //TODO positionner les cartes correctement au départ
    for(Liste::iterator it = toutesLesCartes.begin(); it < toutesLesCartes.end(); ++it){

    }

}

void FenetrePrincipale::initialiserCartes() {
    /* Liste toutesLesCartes;

    Carte H01(Coeur, As, "../imageCarte/h01.ppm");
    Carte H02(Coeur, Deux, "../imageCarte/h02.ppm");
    Carte H03(Coeur, Trois, "../imageCarte/h03.ppm");
    Carte H04(Coeur, Quatre, "../imageCarte/h04.ppm");
    Carte H05(Coeur, Cinq, "../imageCarte/h05.ppm");
    Carte H06(Coeur, Six, "../imageCarte/h06.ppm");
    Carte H07(Coeur, Sept, "../imageCarte/h07.ppm");
    Carte H08(Coeur, Huit, "../imageCarte/h08.ppm");
    Carte H09(Coeur, Neuf, "../imageCarte/h09.ppm");
    Carte H10(Coeur, Dix, "../imageCarte/h10.ppm");
    Carte H11(Coeur, Valet, "../imageCarte/h11.ppm");
    Carte H12(Coeur, Dame, "../imageCarte/h12.ppm");
    Carte H13(Coeur, Roi, "../imageCarte/h13.ppm");

    toutesLesCartes.push_back(H01);
    toutesLesCartes.push_back(H02);
    toutesLesCartes.push_back(H03);
    toutesLesCartes.push_back(H04);
    toutesLesCartes.push_back(H05);
    toutesLesCartes.push_back(H06);
    toutesLesCartes.push_back(H07);
    toutesLesCartes.push_back(H08);
    toutesLesCartes.push_back(H09);
    toutesLesCartes.push_back(H10);
    toutesLesCartes.push_back(H11);
    toutesLesCartes.push_back(H12);
    toutesLesCartes.push_back(H13);

    toutesLesCartes.begin()
    */
}