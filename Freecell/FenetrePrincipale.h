#ifndef FREECELL_FENETREPRINCIPALE_H
#define FREECELL_FENETREPRINCIPALE_H

#include <stdio.h>
#include "PileCarte.h"
#include "Bouton.h"

class FenetrePrincipale {

public:
    FenetrePrincipale(int tailleFenX, int tailleFenY, float factorScaleCards, float factorScaleButtons);

    ~FenetrePrincipale();

    //FONCTIONS MENUS ET FENETRES
    bool lancerJeu(bool nouvellePartie);

    bool fenetreChargement();

    void fenetreSauvegarde();

    void fenetreParametres();

    void fenetreVictoire();
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

    void majAffichageJeu(bool postResize, Bouton &boutonQuitter);

    void majAffichageMenu(Bouton &boutonNouvelleP, Bouton &boutonCharger, Bouton &boutonQuitter, Bouton &boutonParam);

    void colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b);

    void dessinerEmplacementPiles();

    int afficherMenu();

    void majFenetre();

    void quitterFenetre();

    void supprimerPiles();

    static void clear_screen();

    //FONCTIONS SAUVEGARDE ET CHARGEMENT
    void etatChargement();

    void ajouterPartieSauvegardee(std::string nomPartie);

    void sauvegarderPartie(std::string nomPartie);

    void chargerPartie(std::string nomPartie);

    void supprimerPartieChargee(std::string nomPartie);

    void chargerTableauParties();

    void sauverTableauParties();

    void sauverFichierSettings(int dispX, int dispY, float cardScale, float buttonScale);

private:
    int tailleFenOriginaleX_;
    int tailleFenOriginaleY_;
    int tailleFenX_;
    int tailleFenY_;
    float facteurEchelleCartes_;
    float facteurEchelleBoutons_;
    float coeffX_;
    float coeffY_;
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

};


#endif //FREECELL_FENETREPRINCIPALE_H
