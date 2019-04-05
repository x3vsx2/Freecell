//
// Created by kamilcaglar on 02/04/19.
//

#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

#include <iostream>
#include "CImg.h"
#include "Liste.h"

class FenetrePrincipale {

public:
    FenetrePrincipale();
    void initialiserFond();
    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);
    void testClicCarte();
    void initialiserCartes();
    void afficherCartes();
    void placerCartes();


private:
    cimg_library::CImg<unsigned char> *visu_;
    cimg_library::CImg<unsigned char> *fond_;
    cimg_library::CImg<unsigned char> *plateau_;


    Liste toutesLesCartes;


};


#endif //FREECELL_FENETREPRINCIPALE_H
