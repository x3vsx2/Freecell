//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

//TODO creer l'affichage principal
FenetrePrincipale::FenetrePrincipale() {

    initialiserFond();

    //CImg<unsigned char> img('d10.ppm');

    CImg<unsigned char>img('355.jpg');

    // Declare a display to draw the scene
    CImgDisplay disp(*fond_,"FreeCell",0,false,false);


    // Centrer la fenetre
    disp.move((CImgDisplay::screen_width() - disp.width())/2,
              (CImgDisplay::screen_height() - disp.height())/2);


// BOUCLE Principale, ferme la fenetre si ESC or Q key is hit
    while (!disp.is_closed() && !disp.is_keyESC() && !disp.is_keyQ()) {
        //nplateau_ = plateau_;


        /*
        int x = 0;
        int y=0;
        cimg_forXY(img,x,y){
            if (img(x,y)) {
                (*visu_)(x+100, y+100) = img(x,y);
            }
        }

        cimg_forXY(*plateau_,xx,yy) {
            if ((*nplateau_)(xx,yy)) {
                visu_->draw_image(xx,yy,*nplateau_);
            }
        }*/
        visu_->display(disp);
        disp.wait();


    }
}

void FenetrePrincipale::initialiserFond() {

    plateau_ = new CImg<unsigned char> (1280,720,1,1,0);
    fond_ = new CImg<unsigned char> ((*plateau_).width(), (*plateau_).height(),1,3,0);
    colorierImage(*fond_, 26, 83, 92);
    visu_ = new CImg<unsigned char> (*fond_);
    //nplateau_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(),1,3,0);
    //next_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(),1,3,0);
    //next_mask_ = new CImg<unsigned char>((*plateau_).width(), (*plateau_).height(),1,3,0);

}


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

void FenetrePrincipale::ajouterImage(cimg_library::CImg<unsigned char> &img) {

}