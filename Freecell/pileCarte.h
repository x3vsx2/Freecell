//
// Created by kamilcaglar on 05/04/19.
//

#ifndef FREECELL_PILECARTE_H
#define FREECELL_PILECARTE_H

#include "CImg.h"
#include "CarteKamil.h"
#include <vector>

typedef enum {
    melange, jeu1, jeu2, jeu3, jeu4, jeu5, libre1, libre2, libre3, libre4, valide1, valide2, valide3, valide4
} Type;

using namespace cimg_library;


class pileCarte {
public:
    pileCarte();

    pileCarte(int positionX, int positionY);

    void ajouterCarte(CarteKamil carte);

    int getTaille() { return taille_; };

    int getPosX() { return positionX_; };

    int getPosY() { return positionY_; };

    int setPosX(int posX);

    int setPosY(int posY);

    void melangerCartes();

    CarteKamil getCarte(int position) { return (*listeCartes)[position]; }

    void deplacerCartePile(pileCarte *pileRetrait);

    CImg<unsigned char> getImg(int positionCartePile) { return (*listeCartes)[positionCartePile].getImg(); };

    ~pileCarte();

private:
    int taille_;
    std::vector<CarteKamil> *listeCartes;
    int positionX_;
    int positionY_;
};


#endif //FREECELL_PILECARTE_H
