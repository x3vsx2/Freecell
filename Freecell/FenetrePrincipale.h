#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

#include <iostream>
#include <vector>
#include "CImg.h"
#include "PileCarte.h"
#include "Carte.h"

class FenetrePrincipale {

public:
    FenetrePrincipale();

    void initialiserFond();

    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);

    void initialiserCartes();

    std::vector<int> getClicPositions(int mx, int my);

    void initialiserPiles();

    void deplacerPile(int mx, int my);

    void majAffichage();

    bool estSaisieValide(int mx, int my);

    bool estDepotValide(int mx, int my);

    void dessinerEmplacementPiles();

    int afficherMenu();

    void lancerJeu();


private:
    cimg_library::CImg<unsigned char> *visu_;
    cimg_library::CImg<unsigned char> *fond_;
    cimg_library::CImg<unsigned char> *plateau_;
    cimg_library::CImgDisplay *disp;

    std::vector<PileCarte *> *piles;

    PileCarte *pileDeplacement;
    PileCarte *pileMelange;
    PileCarte *pileJeu1;
    PileCarte *pileJeu2;
    PileCarte *pileJeu3;
    PileCarte *pileJeu4;
    PileCarte *pileJeu5;
    PileCarte *pileJeu6;
    PileCarte *pileJeu7;
    PileCarte *pileJeu8;
    PileCarte *pileLibre1;
    PileCarte *pileLibre2;
    PileCarte *pileLibre3;
    PileCarte *pileLibre4;
    PileCarte *pileValide1;
    PileCarte *pileValide2;
    PileCarte *pileValide3;
    PileCarte *pileValide4;
};


#endif //FREECELL_FENETREPRINCIPALE_H
