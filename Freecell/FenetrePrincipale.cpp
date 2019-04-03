//
// Created by kamilcaglar on 02/04/19.
//
#include"pch.h"
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

//TODO creer l'affichage principal
FenetrePrincipale::FenetrePrincipale() {

// Declare an image to draw the grid
    //CImg<unsigned char> grid(300,300,1,3,255);
	CImg<unsigned char> image("imageCarte/blank.ppm");//, visu(500, 400, 1, 3, 0);
// Declare a display to draw the scene
    //CImgDisplay disp(grid,"FreeCell",0,false,false);
	CImgDisplay carte(image, "Carte", 0, false, false);
    // Center the window on the screen
    carte.move((CImgDisplay::screen_width() - carte.width())/2,
              (CImgDisplay::screen_height() - carte.height())/2);

// Declare an image to display the scene
    //CImg<unsigned char> scene=grid;
	CImg<unsigned char> scene = image;

// Main loop, exit if the display window is closed or if ESC or Q key is hit
    while (!carte.is_closed() && !carte.is_keyESC() && !carte.is_keyQ()) {

        // Display the scene
        //scene.display(disp);
		scene.display(carte);
        carte.wait();

        // Handle window resize
        if (carte.is_resized()) carte.resize();
    }
}