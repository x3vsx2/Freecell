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

    std::vector<int> testClicCarteFenetre(int mx, int my);

    void placerCartes();

    void deplacerPile(int mx, int my);

    void majAffichage();

    bool mouvementValide(int mx, int my);


private:
    cimg_library::CImg<unsigned char> *visu_;
    cimg_library::CImg<unsigned char> *fond_;
    cimg_library::CImg<unsigned char> *plateau_;

    std::vector<PileCarte *> *pilesJeu;
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
    PileCarte *pileVide2;
    PileCarte *pileVide3;
    PileCarte *pileVide4;
    PileCarte *pileValide1;
    PileCarte *pileValide2;
    PileCarte *pileValide3;
    PileCarte *pileValide4;
};


#endif //FREECELL_FENETREPRINCIPALE_H
