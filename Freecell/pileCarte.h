//
// Created by kamilcaglar on 05/04/19.
//

#ifndef FREECELL_PILECARTE_H
#define FREECELL_PILECARTE_H

#include "pch.h"
#include "CImg.h"
#include "CarteKamil.h"
#include <vector>

using namespace cimg_library;

typedef enum {
    melange, jeu1, jeu2, jeu3, jeu4, jeu5, libre1, libre2, libre3, libre4, valide1, valide2, valide3, valide4, deplacement
} Type;


class CarteKamil;

class pileCarte {
public:
    pileCarte();

    pileCarte(int positionX, int positionY);

    void ajouterCarte(CarteKamil *carte);

    int getTaille() { return listeCartes_.size(); };

    int getPosX() { return positionX_; };

    int getPosY() { return positionY_; };

    void deplacerPile(int x, int y);

    void setPosX(int posX);

    void setPosY(int posY);

    void melangerCartes();

    void deplacerCartePile(pileCarte *pileRetrait);

    int testClicCarte(int mx, int my);

    CarteKamil *getCarte(int position) { return listeCartes_[position]; };

    ~pileCarte();

private:
    int taille_;
    std::vector<CarteKamil *> listeCartes_;
    int positionX_;
    int positionY_;
};

#endif //FREECELL_PILECARTE_H
