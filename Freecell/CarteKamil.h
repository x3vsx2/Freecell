//
// Created by kamilcaglar on 05/04/19.
//

#ifndef FREECELL_CARTEKAMIL_H
#define FREECELL_CARTEKAMIL_H

#include "CImg.h"
#include "pileCarte.h"
#include <iostream>

class pileCarte;

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
    pileCarte *pileAppartenance_;

public:
    CarteKamil(TypeCouleur Couleur, TypeHauteur Hauteur,
               const char *fileName,
               pileCarte *pileAppartenance); // on utilise const char à cause du constructeur de CIMG

               CarteKamil();
    ~CarteKamil();

    int getPosX();

    int getPosY();

    int getTailleX(){ return tailleX_;};

    int getTailleY(){ return tailleY_;};

    void setPosX(int posX) { positionX_ = posX; };

    void setPosY(int posY) { positionY_ = posY; };

    CImg<unsigned char> getImg() { return *image_; };

};


#endif //FREECELL_CARTEKAMIL_H

