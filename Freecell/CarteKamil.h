//
// Created by kamilcaglar on 05/04/19.
//

#ifndef FREECELL_CARTEKAMIL_H
#define FREECELL_CARTEKAMIL_H

#include "CImg.h"


typedef enum {
    Coeur, Pique, Carreau, Trefle
} TypeCouleur;
typedef enum {
    As, Roi, Dame, Valet, Dix, Neuf, Huit, Sept, Six, Cinq, Quatre, Trois, Deux
} TypeHauteur;

using namespace cimg_library;

class CarteKamil {

private:
    TypeCouleur Couleur_;
    TypeHauteur Hauteur_;
    int positionX_;
    int positionY_;
    int tailleX_;
    int tailleY_;
    CImg<unsigned char> *image_;

public:
    CarteKamil(TypeCouleur Couleur, TypeHauteur Hauteur,
               const char *fileName); // on utilise const char à cause du constructeur de CIMG
    ~CarteKamil();

    int getPosX();

    int getPosY();

    void setPosX(int posX) { positionX_ = posX; };

    void setPosY(int posY) { positionY_ = posY; };

    CImg<unsigned char> getImg() { return *image_; };

};


#endif //FREECELL_CARTEKAMIL_H

