//
// Created by kamilcaglar on 02/04/19.
//

#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

//TODO creer l'affichage principal
FenetrePrincipale::FenetrePrincipale() {

// Declare an image to draw the grid
    CImg<unsigned char> grid(300,300,1,3,255);
// Declare a display to draw the scene
    CImgDisplay disp(grid,"FreeCell",0,false,false);
    // Center the window on the screen
    disp.move((CImgDisplay::screen_width() - disp.width())/2,
              (CImgDisplay::screen_height() - disp.height())/2);

// Declare an image to display the scene
    CImg<unsigned char> scene=grid;


// Main loop, exit if the display window is closed or if ESC or Q key is hit
    while (!disp.is_closed() && !disp.is_keyESC() && !disp.is_keyQ()) {

        // Display the scene
        scene.display(disp);

        disp.wait();

        // Handle window resize
        if (disp.is_resized()) disp.resize();
    }
}