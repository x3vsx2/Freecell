/*!
 *  @file FenetrePrincipale_affichage.cpp
 *  @brief Contient les fonctions qui gèrent l'affichage du jeu
 *  @date 07/05/2019
 *  @authors Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr), Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr)
*/
#include"pch.h"
#include"FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

bool FenetrePrincipale::lancerJeu(bool nouvellePartie) {
    //INITIALISATION DES ELEMENTS DU JEU
    initialiserFond();
    infoChargement();
    initialiserCartes();
    initialiserPiles(nouvellePartie);
    start_time_ = Clock::now();
    //Memoire clic et pile
    bool click_hold = false;
    int memoirePile = 0;
    Bouton bQuitter("Quitter", "icones_et_boutons/miniQuitter.png", facteurEchelleBoutons_ / 2);
    Bouton bNbCoupJoues("NbCoupsJoues", "icones_et_boutons/nbcoupsjoues.png", facteurEchelleBoutons_ * 1.2);
    Bouton bTime("bTime", "icones_et_boutons/time.png", facteurEchelleBoutons_ * 1.2);

    if (nouvellePartie) {
        nbCoupsJoues_ = 0;
        tempsEcoule_ = {0, 0, 0};
    } else {
        majAffichageJeu(true, bQuitter, bNbCoupJoues, bTime);
    }
    dessinerEmplacementPiles();
    do {
        majAffichageJeu(false, bQuitter, bNbCoupJoues, bTime);
        attendre();
        int mx = getPosSourisX();
        int my = getPosSourisY();
        if (disp->button()) {//Test si clique ET clique sur une carte
            if (!click_hold) {
                //Déplacement des cartes dans la pile pileDeplacement
                if (estSaisieValide(mx, my)) {
                    memoirePile = getClicPositions(mx, my)[0];
                    deplacerPile(mx, my);
                    //On recupere la pile qui a été cliquée, réutilisation si le mouvement n'est pas valide
                    click_hold = true; //on bloque le clic, seulement si il est valide
                }
            } else {//Dépot de la pile pileDeplacement
                if (estDepotValide(mx, my)) {
                    nbCoupsJoues_++;
                    int pileCliquee = getClicPositions(mx, my)[0]; //numéro de la pile sur laquelle il y a eu un clic
                    pileDeplacement->inverserListeCartes();
                    unsigned int nbCartesAEnlever = pileDeplacement->getTaille();
                    //On dépose la carte sur une pile
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        piles_[pileCliquee]->deplacerCartePile(pileDeplacement);
                    }
                } else {//si le mouvement n'est pas valide, on remet la carte ou la pile sur la position de départ
                    pileDeplacement->inverserListeCartes();
                    unsigned int nbCartesAEnlever = pileDeplacement->getTaille();
                    for (unsigned int i = 0; i < nbCartesAEnlever; i++) {
                        piles_[memoirePile]->deplacerCartePile(pileDeplacement);
                    }
                }
                click_hold = false;
            }
            if (bQuitter.estCliquee(mx, my)) {
                break;
            }
        }
        if (disp->is_resized()) {
            majFenetre();
            bQuitter.reload(coeffX_, coeffY_);
            bNbCoupJoues.reload(coeffX_, coeffY_);
            bTime.reload(coeffX_, coeffY_);
            majAffichageJeu(true, bQuitter, bNbCoupJoues, bTime);

        }
        if (click_hold && pileDeplacement->getTaille() != 0) {
            pileDeplacement->changerPositionPile(mx, my); //Met à jour la position de la pileDeplacement
        }
        if (victoireAnticipee()) {
            cout << " Victoire Anticipee" << endl;
            terminerPartie(false, bQuitter, bNbCoupJoues, bTime);
        }
        if (PartieEstGagnee()) {
            supprimerPiles();
            quitterFenetre();
            return true;
        }
    } while (!commandeFermerFenetre());
    quitterFenetre();
    return false;
}

void FenetrePrincipale::infoChargement() {
    Bouton bChargement("Chargement", "icones_et_boutons/chargementJeu.png", 1);
    bChargement.dessinerBouton(visu_, disp->width() / 2 - bChargement.getTailleX() / 2,
                               disp->height() / 2 - bChargement.getTailleY() / 2);
    visu_->display(*disp);
}


void FenetrePrincipale::initialiserFond() {
    //declare le plateau de jeu avec longeurXlargeur
    fond_ = new CImg<unsigned char>(tailleFenX_, tailleFenY_, 1, 3, 0);
    colorierImage(*fond_, couleurFond[0], couleurFond[1], couleurFond[2]);
    visu_ = new CImg<unsigned char>(*fond_);
}

void FenetrePrincipale::dessinerEmplacementPiles() {

    int c = 0;
    while (true) {//trouve ua moins une carte et récupère sa taille
        if (piles_[c]->getTaille() !=
            0) { // on vérifie que la pile contient des cartes avant de faire un get taille de la première carte
            if (piles_[c]->getCarte(0)->getTailleX() != 0) {
                for (unsigned int i = 0; i < 16; i++) {
                    piles_[i]->setTailleX(piles_[c]->getCarte(0)->getTailleX());
                    piles_[i]->setTailleY(piles_[c]->getCarte(0)->getTailleY());
                }
                break;
            }
        }
        c++;// lol mdr
    }
    //Dessine l'emplacement des piles selon la taille des cartes
    for (unsigned int i = 0; i < 16; i++) {
        fond_->draw_rectangle(piles_[i]->getPosX(), piles_[i]->getPosY(),
                              piles_[i]->getPosX() + piles_[i]->getTailleX(),
                              piles_[i]->getPosY() + piles_[i]->getTailleY(), couleurPiles, 1);
    }
}

void FenetrePrincipale::colorierImage(cimg_library::CImg<unsigned char> &img, int r, int g, int b) {

    cimg_forXY(img, x, y)
    {
        //Rouge
        img(x, y, 0, 0) = r;
        //Vert
        img(x, y, 0, 1) = g;
        //Bleu
        img(x, y, 0, 2) = b;

    }
}

void FenetrePrincipale::majAffichageJeu(bool postResize, Bouton &bQuitter, Bouton &bNbCoups, Bouton &bTime) {
    visu_->draw_image(*fond_);
    end_time_ = Clock::now();
    mesurerTemps(start_time_, end_time_, tempsEcoule_);

    bQuitter.dessinerBouton(visu_, static_cast<int>(disp->width() * 0.999 - bQuitter.getTailleX()),
                            static_cast<int>(disp->height() * 0.999 - bQuitter.getTailleY()));
    bNbCoups.dessinerBouton(visu_, static_cast<int>(disp->width() * 0.999 - bNbCoups.getTailleX()),
                            static_cast<int>(disp->height() * 0.001));
    visu_->draw_text(static_cast<int>(bNbCoups.getPosX() + bNbCoups.getTailleX() - bNbCoups.getTailleX() * 0.15),
                     static_cast<int>(bNbCoups.getPosY() + bNbCoups.getTailleY() / 2.7),
                     to_string(nbCoupsJoues_).data(),
                     couleurBlanche, couleurBoutons, 1, static_cast<int>(facteurEchelleBoutons_ * coeffX_ * 40));
    bTime.dessinerBouton(visu_, static_cast<int>(disp->width() * 0.001), static_cast<int>(disp->height() * 0.001));
    string temps =
            to_string(tempsEcoule_[0]) + "h " + to_string(tempsEcoule_[1]) + "m " + to_string(tempsEcoule_[2]) + "s";
    visu_->draw_text(static_cast<int>(bTime.getPosX() + bTime.getTailleX() - bTime.getTailleX() * 0.5),
                     static_cast<int>(bTime.getPosY() + bTime.getTailleY() / 2.7), temps.data(),
                     couleurBlanche, couleurBoutons, 1, static_cast<int>(facteurEchelleBoutons_ * coeffY_ * 40));

    if (postResize) {//Si il y a eu un resize il faut modifier la taille des éléments
        pileJeu1->setPositions(static_cast<int>(0.10 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileJeu2->setPositions(static_cast<int>(0.20 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileJeu3->setPositions(static_cast<int>(0.30 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileJeu4->setPositions(static_cast<int>(0.40 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileJeu5->setPositions(static_cast<int>(0.50 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileJeu6->setPositions(static_cast<int>(0.60 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileJeu7->setPositions(static_cast<int>(0.70 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileJeu8->setPositions(static_cast<int>(0.80 * disp->width()), static_cast<int>(0.40 * disp->height()));
        pileLibre1->setPositions(static_cast<int>(0.08 * disp->width()), static_cast<int>(0.10 * disp->height()));
        pileLibre2->setPositions(static_cast<int>(0.18 * disp->width()), static_cast<int>(0.10 * disp->height()));
        pileLibre3->setPositions(static_cast<int>(0.28 * disp->width()), static_cast<int>(0.10 * disp->height()));
        pileLibre4->setPositions(static_cast<int>(0.38 * disp->width()), static_cast<int>(0.10 * disp->height()));
        pileValide1->setPositions(static_cast<int>(0.52 * disp->width()), static_cast<int>(0.10 * disp->height()));
        pileValide2->setPositions(static_cast<int>(0.62 * disp->width()), static_cast<int>(0.10 * disp->height()));
        pileValide3->setPositions(static_cast<int>(0.72 * disp->width()), static_cast<int>(0.10 * disp->height()));
        pileValide4->setPositions(static_cast<int>(0.82 * disp->width()), static_cast<int>(0.10 * disp->height()));
        for (auto &pile : piles_) {
            pile->reload(coeffX_, coeffY_);
        }
        dessinerEmplacementPiles();
        pileDeplacement->reload(coeffX_, coeffY_);
    }

    //On affiche les différentes piles_
    for (unsigned int i = 0; i < piles_.size(); ++i) {
        if (i > 11 && piles_[i]->getTaille() > 0) { //Si c'est une pile valide on affiche que la dernière carte
            int j = piles_[i]->getTaille() - 1;
            piles_[i]->getCarte(j)->dessinerCarte(visu_);
        } else {
            piles_[i]->dessinerPile(visu_);
        }
    }
    pileDeplacement->dessinerPile(visu_);
    visu_->display(*disp);
}

void FenetrePrincipale::initialiserCartes() {
    pileMelange = new PileCarte(0, 0, melange);
    pileMelange->ajouterCarte(
            new Carte(1, Coeur, As, "imageCarte/h01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(2, Coeur, Deux, "imageCarte/h02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(3, Coeur, Trois, "imageCarte/h03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(4, Coeur, Quatre, "imageCarte/h04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(5, Coeur, Cinq, "imageCarte/h05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(6, Coeur, Six, "imageCarte/h06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(7, Coeur, Sept, "imageCarte/h07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(8, Coeur, Huit, "imageCarte/h08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(9, Coeur, Neuf, "imageCarte/h09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(10, Coeur, Dix, "imageCarte/h10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(11, Coeur, Valet, "imageCarte/h11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(12, Coeur, Dame, "imageCarte/h12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(13, Coeur, Roi, "imageCarte/h13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(14, Trefle, As, "imageCarte/c01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(15, Trefle, Deux, "imageCarte/c02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(16, Trefle, Trois, "imageCarte/c03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(17, Trefle, Quatre, "imageCarte/c04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(18, Trefle, Cinq, "imageCarte/c05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(19, Trefle, Six, "imageCarte/c06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(20, Trefle, Sept, "imageCarte/c07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(21, Trefle, Huit, "imageCarte/c08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(22, Trefle, Neuf, "imageCarte/c09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(23, Trefle, Dix, "imageCarte/c10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(24, Trefle, Valet, "imageCarte/c11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(25, Trefle, Dame, "imageCarte/c12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(26, Trefle, Roi, "imageCarte/c13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(27, Carreau, As, "imageCarte/d01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(28, Carreau, Deux, "imageCarte/d02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(29, Carreau, Trois, "imageCarte/d03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(30, Carreau, Quatre, "imageCarte/d04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(31, Carreau, Cinq, "imageCarte/d05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(32, Carreau, Six, "imageCarte/d06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(33, Carreau, Sept, "imageCarte/d07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(34, Carreau, Huit, "imageCarte/d08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(35, Carreau, Neuf, "imageCarte/d09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(36, Carreau, Dix, "imageCarte/d10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(37, Carreau, Valet, "imageCarte/d11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(38, Carreau, Dame, "imageCarte/d12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(39, Carreau, Roi, "imageCarte/d13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(40, Pique, As, "imageCarte/s01.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(41, Pique, Deux, "imageCarte/s02.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(42, Pique, Trois, "imageCarte/s03.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(43, Pique, Quatre, "imageCarte/s04.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(44, Pique, Cinq, "imageCarte/s05.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(45, Pique, Six, "imageCarte/s06.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(46, Pique, Sept, "imageCarte/s07.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(47, Pique, Huit, "imageCarte/s08.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(48, Pique, Neuf, "imageCarte/s09.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(49, Pique, Dix, "imageCarte/s10.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(50, Pique, Valet, "imageCarte/s11.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(51, Pique, Dame, "imageCarte/s12.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
    pileMelange->ajouterCarte(
            new Carte(52, Pique, Roi, "imageCarte/s13.png", pileMelange, facteurEchelleCartes_, coeffX_, coeffY_));
}

void FenetrePrincipale::deplacerPile(int mx, int my) {
    //récupère la position d'une carte dans les piles_
    //Si vector = -1 -1 alors aucune carte n'a été cliquée
    vector<int> positions = getClicPositions(mx, my);

    //On change les cartes de pile si on a cliqué sur une carte
    if (positions[0] != -1) {
        //déplacement d'une ou de plusieurs cartes dans la pile déplacée
        int nbCarteAEnlever = piles_[positions[0]]->getTaille() - positions[1];
        for (unsigned int i = 0; i < nbCarteAEnlever; i++) {
            pileDeplacement->deplacerCartePile(piles_[positions[0]]);
        }
        pileDeplacement->inverserListeCartes();
    }
}

void FenetrePrincipale::majFenetre() {
    attendre();
    disp->resize();//maj des attributs du display
    tailleFenX_ = disp->width();//recupération des nouveaux attributs
    tailleFenY_ = disp->height();
    coeffX_ = float(tailleFenX_) / float(tailleFenOriginaleX_);//Calcul du coefficient de redimensionnement
    coeffY_ = float(tailleFenY_) / float(tailleFenOriginaleY_);
    quitterFenetre();//Supprime fond, plateau et visu
    initialiserFond();//Nouveau fond, plateau et visu à la nouvelle taille
}

FenetrePrincipale::~FenetrePrincipale() {
    delete disp;
}


