#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

#include <iostream>
#include <vector>
#include "CImg.h"
#include "PileCarte.h"
#include "Carte.h"
#include "Bouton.h"

class FenetrePrincipale {

public:
    FenetrePrincipale(int tailleFenX, int tailleFenY, float factorScaleCards, float factorScaleButtons);

    //FONCTIONS MENUS ET FENETRES
    void lancerJeu(bool nouvellePartie);

    bool fenetreChargement();

    void fenetreSauvegarde();

    //FONCTIONS D'INITIALISATION
    void initialiserFond();

    void initialiserCartes();

    void initialiserPiles(bool nouvellePartie);

    //FONCTIONS GESTION JEU
    void deplacerPile(int mx, int my);

    std::vector<int> getClicPositions(int mx, int my);

    bool estSaisieValide(int mx, int my);

    bool estDepotValide(int mx, int my);

    bool PartieEstGagnee();

    bool commandeFermerFenetre();

    int getPosSourisX() { return disp->mouse_x(); };

    int getPosSourisY() { return disp->mouse_y(); };

    //FONCTIONS D'AFFICHAGE
    void attendre();

    void majAffichage();

    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);

    void dessinerEmplacementPiles();

    int afficherMenu();

    void majFenetre();

    void quitterFenetre();

    void supprimerPiles();

    //FONCTIONS SAUVEGARDE ET CHARGEMENT
    void etatChargement();

    void ajouterPartieSauvegardee(std::string nomPartie);

    void sauvegarderPartie(std::string nomPartie);

    void chargerPartie(std::string nomPartie);

    void supprimerPartieChargee(std::string nomPartie);

    void chargerTableauParties();

    void sauverTableauParties();


private:
    int tailleFenX_;
    int tailleFenY_;
    float facteurEchelleCartes_;
    float facteurEchelleBoutons_;
    cimg_library::CImg<unsigned char> *visu_;
    cimg_library::CImg<unsigned char> *fond_;
    cimg_library::CImg<unsigned char> *plateau_;
    cimg_library::CImgDisplay *disp;
    std::vector<std::vector<int>> tableauxIdentifiants;
    std::vector<std::string> tableauParties;
    std::vector<PileCarte *> piles_;

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

    //COULEURS

};


#endif //FREECELL_FENETREPRINCIPALE_H
