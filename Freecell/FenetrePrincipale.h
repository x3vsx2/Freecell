//
// Created by kamilcaglar on 02/04/19.
//

#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

#include <iostream>
#include "CImg.h"

class FenetrePrincipale {

public:
    FenetrePrincipale();
    void initialiserFond();
    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);
    void ajouterImage(cimg_library::CImg<unsigned char> &img);

private:
    cimg_library::CImg<unsigned char> *visu_;
    cimg_library::CImg<unsigned char> *fond_;
    cimg_library::CImg<unsigned char> *plateau_;
    cimg_library::CImg<unsigned char> *nplateau_;
    cimg_library::CImg<unsigned char> *piece_;
    cimg_library::CImg<unsigned char> *next_;
    cimg_library::CImg<unsigned char> *next_mask_;

};


#endif //FREECELL_FENETREPRINCIPALE_H
