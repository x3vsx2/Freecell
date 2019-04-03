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
    void colorierImage(cimg_library::CImg<unsigned char> img, int r, int g, int b);

private:
    cimg_library::CImg<unsigned char> *fond_;
};


#endif //FREECELL_FENETREPRINCIPALE_H
