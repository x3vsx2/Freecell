/*!
 *  @file FenetrePrincipale_menu.cpp
 *  @brief Contient les fonctions d'affichage et de gestion du menu principal
 *  @date 07/05/2019
 *  @authors Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr), Jean-Baptiste JACQUET (jean-Baptiste.jacquet@etu.univ-st-etienne.fr)
*/
#include"pch.h"
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;
using namespace std::chrono;


int FenetrePrincipale::afficherMenu() {
    initialiserFond();

    Bouton boutonNouvellePartie("BoutonNouvellePartie", "icones_et_boutons/bouton_nouvellePartie.png",
                                facteurEchelleBoutons_);
    Bouton boutonChargerPartie("boutonChargerPartie", "icones_et_boutons/bouton_chargerPartie.png",
                               facteurEchelleBoutons_);
    Bouton boutonQuitter("boutonQuitter", "icones_et_boutons/bouton_quitter.png", facteurEchelleBoutons_);
    Bouton boutonParametres("boutonParametres", "icones_et_boutons/parametres.png", facteurEchelleBoutons_ / 2);

    majAffichageMenu(boutonNouvellePartie, boutonChargerPartie, boutonQuitter, boutonParametres);
    do {
        attendre();
        if (disp->button()) {//Test si clique
            int mx = getPosSourisX();
            int my = getPosSourisY();
            if (boutonNouvellePartie.estCliquee(mx, my)) {
                return 0;
            } else if (boutonChargerPartie.estCliquee(mx, my)) {
                return 1;
            } else if (boutonParametres.estCliquee(mx, my)) {
                return 2;
            } else if (boutonQuitter.estCliquee(mx, my)) {
                return 3;
            }
        }
        if (disp->is_resized()) {
            majFenetre();
            boutonNouvellePartie.reload(coeffX_, coeffY_);
            boutonChargerPartie.reload(coeffX_, coeffY_);
            boutonQuitter.reload(coeffX_, coeffY_);
            boutonParametres.reload(coeffX_, coeffY_);
            majAffichageMenu(boutonNouvellePartie, boutonChargerPartie, boutonQuitter, boutonParametres);
        }
    } while (true);
}

void FenetrePrincipale::majAffichageMenu(Bouton &boutonNouvelleP, Bouton &boutonCharger, Bouton &boutonQuitter,
                                         Bouton &boutonParam) {
    visu_->draw_image(*fond_);
    boutonNouvelleP.dessinerBouton(visu_, disp->width() / 2 - boutonNouvelleP.getTailleX() / 2,
                                   disp->height() * 0.10);
    boutonCharger.dessinerBouton(visu_, disp->width() / 2 - boutonCharger.getTailleX() / 2,
                                 disp->height() * 0.40);
    boutonQuitter.dessinerBouton(visu_, disp->width() / 2 - boutonQuitter.getTailleX() / 2,
                                 disp->height() * 0.70);
    boutonParam.dessinerBouton(visu_, disp->width() - boutonParam.getTailleX() * 1.1,
                               disp->height() - boutonParam.getTailleY() * 1.1);
    visu_->display(*disp);
}

void FenetrePrincipale::fenetreParametres() {
    initialiserFond();

    Bouton binstructionsParametres("instructionsParametres", "icones_et_boutons/instructionsParametres.png",
                                   facteurEchelleBoutons_);
    binstructionsParametres.dessinerBouton(visu_, disp->width() / 2 - binstructionsParametres.getTailleX() / 2,
                                           disp->height() / 2 - binstructionsParametres.getTailleY() / 2);
    visu_->display(*disp);

    system(CLEAR);
    cout << "Entrez la nouvelle longeur de la fenetre" << endl;
    int newTailleFenX;
    cin >> newTailleFenX;

    system(CLEAR);
    cout << "Entrez la nouvelle largeur de la fenetre" << endl;
    int newTailleFenY;
    cin >> newTailleFenY;

    system(CLEAR);
    cout << "Entrez la nouvelle echelle de la carte" << endl;
    float newCardsScale;
    cin >> newCardsScale;

    system(CLEAR);
    cout << "Entrez la nouvelle echelle des boutons" << endl;
    float newButtonScale;
    cin >> newButtonScale;

    cout << "Pour utiliser les nouveaux parametres, veuillez relancer FreeCell" << endl;

    sauverFichierSettings(newTailleFenX, newTailleFenY, newCardsScale, newButtonScale);
    quitterFenetre();

}

void FenetrePrincipale::mesurerTemps(const ClockTime &start_time, const ClockTime &end_time,
                                     std::vector<int> &tempsEcoule_) {

    auto execution_time_sec = (duration_cast<seconds>(end_time - start_time).count() + tempsEcouleSauvegarde_[2]) % 60;
    auto execution_time_min = (duration_cast<minutes>(end_time - start_time).count() + tempsEcouleSauvegarde_[1]) % 60 +
                              (duration_cast<seconds>(end_time - start_time).count() + tempsEcouleSauvegarde_[2]) / 60;
    auto execution_time_hour = (duration_cast<hours>(end_time - start_time).count() + tempsEcouleSauvegarde_[0]) % 60 +
                               (duration_cast<minutes>(end_time - start_time).count() + tempsEcouleSauvegarde_[1]) / 60;

    tempsEcoule_[0] = execution_time_hour;
    tempsEcoule_[1] = execution_time_min;
    tempsEcoule_[2] = execution_time_sec;
}
