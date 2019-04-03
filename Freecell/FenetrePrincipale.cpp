//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

//TODO creer l'affichage principal
FenetrePrincipale::FenetrePrincipale() {

    //initialiserFond();
    CImg<unsigned char> fond_(1280,720,1,3,255);

    colorierImage(fond_, 26, 83, 92);
    // Declare a display to draw the scene
    CImgDisplay disp(fond_,"FreeCell",0,false,false);
    // Center the window on the screen
    disp.move((CImgDisplay::screen_width() - disp.width())/2,
              (CImgDisplay::screen_height() - disp.height())/2);

// Declare une image pour afficher la scene
	CImg<unsigned char> scene = fond_;

// BOUCLE Principale, ferme la fenetre si ESC or Q key is hit
    while (!disp.is_closed() && !disp.is_keyESC() && !disp.is_keyQ()) {

        // Display the scene
		scene.display(disp);
        disp.wait();

        // Handle window resize
        if (disp.is_resized()) disp.resize();
    }
}

void FenetrePrincipale::initialiserFond() {

    CImg<unsigned char> fond_(1280,720,1,3,255);

    colorierImage(fond_, 26, 83, 92);

}

void FenetrePrincipale::colorierImage(cimg_library::CImg<unsigned char> img, int r, int g, int b) {

    cimg_forXY(img,x,y){
        //Rouge
        img(x,y,0,0) = r;
        //Vert
        img(x,y,0,1) = g;
        //Bleu
        img(x,y,0,2) = b;

    }
}