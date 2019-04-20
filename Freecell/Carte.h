//
// Created by kamilcaglar on 05/04/19.
//

#ifndef FREECELL_CARTE_H
#define FREECELL_CARTE_H

#include "pch.h"
#include "CImg.h"
#include "PileCarte.h"
#include <iostream>

class PileCarte;

typedef enum {
    Coeur, Pique, Carreau, Trefle
} TypeCouleur;
typedef enum {
    As, Deux, Trois, Quatre, Cinq, Six, Sept, Huit, Neuf, Dix, Valet, Dame, Roi
} TypeHauteur;

using namespace cimg_library;

class Carte {

private:
    int idCarte_;
    TypeCouleur Couleur_;
    TypeHauteur Hauteur_;
    int positionX_;
    int positionY_;
    int tailleX_;
    int tailleY_;
    CImg<unsigned char> *image_;
    PileCarte *pileAppartenance_;

public:
    Carte(int idCarte, TypeCouleur Couleur, TypeHauteur Hauteur,
          const char *fileName,
          PileCarte *pileAppartenance); // on utilise const char à cause du constructeur de CIMG

    Carte(Carte *CarteAcopier);

    Carte();

    ~Carte();

    int getIdentifiant();

    int getPosX();

    int getPosY();

    int getTailleX() { return tailleX_; };

    int getTailleY() { return tailleY_; };

    void setPosX(int posX) { positionX_ = posX; };

    void setPosY(int posY) { positionY_ = posY; };

    CImg<unsigned char> getImg() { return *image_; };

    TypeCouleur getCouleur() { return Couleur_; }

    TypeHauteur getHauteur() { return Hauteur_; }


};


#endif //FREECELL_CARTE_H

