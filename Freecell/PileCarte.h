//
// Created by kamilcaglar on 05/04/19.
//

#ifndef FREECELL_PILECARTE_H
#define FREECELL_PILECARTE_H

#include "pch.h"
#include "CImg.h"
#include "Carte.h"
#include <vector>
#include <algorithm>
#include <fstream>

using namespace cimg_library;

typedef enum {
    // il est strictement interdit de changer l'odre des types
            unknown,
    melange,
    jeu1,
    jeu2,
    jeu3,
    jeu4,
    jeu5,
    jeu6,
    jeu7,
    jeu8,
    libre1,
    libre2,
    libre3,
    libre4,
    valide1,
    valide2,
    valide3,
    valide4,
    deplacement
} Type;


class Carte;

class PileCarte {
public:
    PileCarte();

    PileCarte(int positionX, int positionY, Type type);

    PileCarte(PileCarte &pileCopiee);

    ~PileCarte();

    void ajouterCarte(Carte *carte);

    unsigned int getTaille() { return listeCartes_.size(); };

    int getPosX() { return positionX_; };

    int getPosY() { return positionY_; };

    void changerPositionPile(int x, int y);

    void setPosX(int posX);

    void setPosY(int posY);

    void melangerCartes();

    void deplacerCartePile(PileCarte *pileRetrait, int ecartEntreCartes);

    int getClicPositionCarte(int mx, int my);

    void inverserListeCartes();

    bool precedentEstValide(unsigned int position);

    Carte *getCarte(int position) { return listeCartes_[position]; };

    void brassagePile();

    Type getType() { return type_; }

    void deplacerCartePileAvecPosition(int posCarte1, int posCarte2, PileCarte *pile2);

    int trouverPosCarteId(int id);

    void sauvegarderPile(std::ofstream &ofs);

    void setPositions(int posX, int posY);

private:
    unsigned int taille_;
    std::vector<Carte *> listeCartes_;
    int positionX_;
    int positionY_;
    Type type_;
};

#endif //FREECELL_PILECARTE_H
