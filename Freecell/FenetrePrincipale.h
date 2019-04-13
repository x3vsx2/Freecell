#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

#include <iostream>
#include <vector>
#include "CImg.h"
#include "pileCarte.h"
#include "CarteKamil.h"

class FenetrePrincipale {

public:
    FenetrePrincipale();

    void initialiserFond();

    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);

    void initialiserCartes();

    std::vector<int> testClicCarteFenetre(int mx, int my);

    CarteKamil *trouverCarte(std::vector<int> positionCarte);

    void placerCartes();

    void deplacerPile(int mx, int my);

    void majAffichage(int mx,int my);

    bool mouvementValide(int mx, int my);


private:
    cimg_library::CImg<unsigned char> *visu_;
    cimg_library::CImg<unsigned char> *fond_;
    cimg_library::CImg<unsigned char> *plateau_;

    std::vector<pileCarte *> *pilesJeu;
    pileCarte *pileDeplacement;
    pileCarte *pileMelange;
    pileCarte *pileJeu1;
    pileCarte *pileJeu2;
    pileCarte *pileJeu3;
    pileCarte *pileJeu4;
    pileCarte *pileJeu5;
    pileCarte *pileJeu6;
    pileCarte *pileJeu7;
    pileCarte *pileJeu8;
    pileCarte *pileVide2;
    pileCarte *pileVide3;
    pileCarte *pileVide4;
    pileCarte *pileValide1;
    pileCarte *pileValide2;
    pileCarte *pileValide3;
    pileCarte *pileValide4;
};


#endif //FREECELL_FENETREPRINCIPALE_H
