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
public:
    Carte(int idCarte, TypeCouleur Couleur, TypeHauteur Hauteur,
          const char *fileName,
          PileCarte *pileAppartenance, float factorScale, float coeffX, float coeffY);

    Carte(Carte *CarteAcopier);

    Carte();

    void dessinerCarte(cimg_library::CImg<unsigned char> *visu);

    ~Carte();

    int getIdentifiant();

    int getPosX();

    int getPosY();

    int getTailleX() const { return tailleX_; };

    int getTailleY() const { return tailleY_; };

    void setTailleX(int newTailleX) { tailleX_ = newTailleX; };

    void setTailleY(int newTailleY) { tailleY_ = newTailleY; };

    void setPosX(int posX) { positionX_ = posX; };

    void setPosY(int posY) { positionY_ = posY; };

    CImg<unsigned char> getImg() { return image_; };

    TypeCouleur getCouleur() { return Couleur_; }

    TypeHauteur getHauteur() { return Hauteur_; }

    PileCarte *getPileAppartenance() { return pileAppartenance_; };

    void setPileAppartenance(PileCarte *pile) { pileAppartenance_ = pile; };

    void reload(float coeffX, float coeffY);

private:
    int idCarte_;
    TypeCouleur Couleur_;
    TypeHauteur Hauteur_;
    int positionX_;
    int positionY_;
    int OriginalTailleX_;
    int OriginalTailleY_;
    int tailleX_;
    int tailleY_;
    CImg<unsigned char> image_;
    PileCarte *pileAppartenance_;
    const char *chemin;
};


#endif //FREECELL_CARTE_H

