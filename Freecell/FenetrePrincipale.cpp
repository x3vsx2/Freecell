/*!
 *  @file FenetrePrincipale_menu.cpp
 *  @brief Contient les fonctions d'affichage et de gestion du menu principal
 *  @date 07/05/2019
 *  @authors Kamil CAGLAR (kamil.caglar@etu.univ-st-etienne.fr), Jean-Baptiste JACQUET (jean-Baptiste.jacquet2@etu.univ-st-etienne.fr)
*/
#include"pch.h"
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

FenetrePrincipale::FenetrePrincipale(const int tailleFenX, const int tailleFenY, const float factorScaleCards,
                                     const float factorScaleButtons)
        : tabIdCartesChargement_(16, vector<int>(0)), tailleFenX_(tailleFenX), tailleFenY_(tailleFenY),
          facteurEchelleCartes_(factorScaleCards), facteurEchelleBoutons_(factorScaleButtons), coeffX_(1), coeffY_(1),
          nbCoupsJoues_(0), tempsEcoule_(3), tempsEcouleSauvegarde_(3) {
    initialiserFond();

    //On enregistre les tailles originales pour le cas d'un resize
    tailleFenOriginaleX_ = tailleFenX;
    tailleFenOriginaleY_ = tailleFenY;
    //Declare un display pour afficher le fond
    disp = new CImgDisplay(*fond_, "FreeCell", 0, false, false);
    //Centre la fenetre
    disp->move((CImgDisplay::screen_width() - disp->width()) / 2,
               (CImgDisplay::screen_height() - disp->height()) / 2);
    quitterFenetre();
}

vector<int> FenetrePrincipale::getClicPositions(int mx, int my) {

    vector<int> positions;
    positions.push_back(-1);
    positions.push_back(-1);

    //Cherche si il y a une carte qui correspond à la position de la souris dans les piles_ de Jeu
    for (unsigned int i = 0; i < piles_.size(); i++) {
        positions[1] = piles_[i]->getClicPositionCarte(mx, my);
        if (positions[1] != -1) {
            positions[0] = i;
            return positions;
        }
    }

    //==================Partie utilisée dans le cas d'un dépôt  de carte=================================
    //Cherche si il y a une position Libre qui correspond à la position de la souris dans les piles_ Jeu
    for (unsigned int i = 0; i < piles_.size(); i++) {
        int pileX1 = piles_[i]->getPosX();
        int pileX2 = piles_[i]->getPosX() + piles_[i]->getTailleX();
        int pileY1 = piles_[i]->getPosY();
        int pileY2 = piles_[i]->getPosY() + piles_[i]->getTailleY();
        if (mx >= pileX1 && mx <= pileX2 && my >= pileY1 && my <= pileY2) {
            positions[0] = i;
            positions[1] = -2;
            return positions;
        }
    }
    return positions;
}

void FenetrePrincipale::initialiserPiles(bool nouvellePartie) {
    pileDeplacement = new PileCarte(0, 0, deplacement);
    pileJeu1 = new PileCarte(0.10 * disp->width(), 0.40 * disp->height(), jeu1);
    pileJeu2 = new PileCarte(0.20 * disp->width(), 0.40 * disp->height(), jeu2);
    pileJeu3 = new PileCarte(0.30 * disp->width(), 0.40 * disp->height(), jeu3);
    pileJeu4 = new PileCarte(0.40 * disp->width(), 0.40 * disp->height(), jeu4);
    pileJeu5 = new PileCarte(0.50 * disp->width(), 0.40 * disp->height(), jeu5);
    pileJeu6 = new PileCarte(0.60 * disp->width(), 0.40 * disp->height(), jeu6);
    pileJeu7 = new PileCarte(0.70 * disp->width(), 0.40 * disp->height(), jeu7);
    pileJeu8 = new PileCarte(0.80 * disp->width(), 0.40 * disp->height(), jeu8);

    pileLibre1 = new PileCarte(0.08 * disp->width(), 0.10 * disp->height(), libre1);
    pileLibre2 = new PileCarte(0.18 * disp->width(), 0.10 * disp->height(), libre2);
    pileLibre3 = new PileCarte(0.28 * disp->width(), 0.10 * disp->height(), libre3);
    pileLibre4 = new PileCarte(0.38 * disp->width(), 0.10 * disp->height(), libre4);
    pileValide1 = new PileCarte(0.52 * disp->width(), 0.10 * disp->height(), valide1);
    pileValide2 = new PileCarte(0.62 * disp->width(), 0.10 * disp->height(), valide2);
    pileValide3 = new PileCarte(0.72 * disp->width(), 0.10 * disp->height(), valide3);
    pileValide4 = new PileCarte(0.82 * disp->width(), 0.10 * disp->height(), valide4);

    piles_.clear();
    piles_.push_back(pileJeu1);
    piles_.push_back(pileJeu2);
    piles_.push_back(pileJeu3);
    piles_.push_back(pileJeu4);
    piles_.push_back(pileJeu5);
    piles_.push_back(pileJeu6);
    piles_.push_back(pileJeu7);
    piles_.push_back(pileJeu8);
    piles_.push_back(pileLibre1);
    piles_.push_back(pileLibre2);
    piles_.push_back(pileLibre3);
    piles_.push_back(pileLibre4);
    piles_.push_back(pileValide1);
    piles_.push_back(pileValide2);
    piles_.push_back(pileValide3);
    piles_.push_back(pileValide4);

    if (nouvellePartie) {//On mélange et répartie les cartes seulement si c'est une nouvelle partie
        pileMelange->brassagePile();
        for (unsigned int i = 0; i < 6; i++) {
            pileJeu1->deplacerCartePile(pileMelange);
            pileJeu2->deplacerCartePile(pileMelange);
            pileJeu3->deplacerCartePile(pileMelange);
            pileJeu4->deplacerCartePile(pileMelange);
            pileJeu5->deplacerCartePile(pileMelange);
            pileJeu6->deplacerCartePile(pileMelange);
            pileJeu7->deplacerCartePile(pileMelange);
            pileJeu8->deplacerCartePile(pileMelange);
        }
        pileJeu1->deplacerCartePile(pileMelange);
        pileJeu2->deplacerCartePile(pileMelange);
        pileJeu3->deplacerCartePile(pileMelange);
        pileJeu4->deplacerCartePile(pileMelange);
    } else {//Initialise les piles selon le chargement
        for (unsigned int i = 0; i < 16; i++) {
            for (unsigned int j = 0; j < tabIdCartesChargement_[i].size(); j++) {
                int idAchercher = tabIdCartesChargement_[i][j];
                if (idAchercher == 0) {
                    break;
                }
                int posPileMelange = -1;
                //On regarde dans la pile Melange pour trouver sa position
                posPileMelange = pileMelange->trouverPosCarteId(idAchercher);
                piles_[i]->deplacerCartePileAvecPosition(piles_[i]->getTaille(), posPileMelange, pileMelange);
            }
        }
    }
    delete pileMelange;
}

bool FenetrePrincipale::estSaisieValide(int mx, int my) {

    vector<int> positionsCartecliquee = getClicPositions(mx, my);
    //On verifie si on a clique sur une pile qui serait vide, c'est à dire qu'il n'y a plus de cartes dedans
    //Laisser ce test en PREMIER, sinon on cherche à accéder à des éléments non existants
    if (positionsCartecliquee[0] == -1 || positionsCartecliquee[0] > 11)return false;
    int nbEmplacementLibreDisponible =
            4 - piles_[8]->getTaille() - piles_[9]->getTaille() - piles_[10]->getTaille() - piles_[11]->getTaille();
    if (piles_[positionsCartecliquee[0]]->getTaille() - 1 - positionsCartecliquee[1] > nbEmplacementLibreDisponible) {
        // si plus de cartes saisie qu'autorisé return false
        return false;
    }
    if (positionsCartecliquee[1] == -2 || positionsCartecliquee[0] == -1) {
        //La pile est VIDE (JEU ou LIBRES), on ne peut pas prendre de carte
        //OU
        //Aucune carte ne correspond à la position de la souris
        return false;
    } else {
        if (positionsCartecliquee[1] ==
            piles_[positionsCartecliquee[0]]->getTaille() - 1) {
            return true;
        }// si il y a une seule carte return true
        else {
            bool validite = true;
            for (unsigned int k = piles_[positionsCartecliquee[0]]->getTaille() - 1;
                 k > positionsCartecliquee[1]; k--) {
                validite &= piles_[positionsCartecliquee[0]]->precedentEstValide(k);
            }// on vérifie que l'assemblage est autorisé
            return (validite);
        }
    }
}

bool FenetrePrincipale::estDepotValide(int mx, int my) {
    vector<int> positionsCiblee = getClicPositions(mx, my);
    if (positionsCiblee[0] == -1) { return false; }
    else {
        if (piles_[positionsCiblee[0]]->getType() > 1 && piles_[positionsCiblee[0]]->getType() < 10) {
            //si c'est une pile jeu
            if (positionsCiblee[1] == -2) { return true; } // si la pile est vide alors le dépot est autorisé
            if (pileDeplacement->getCarte(0)->getCouleur() % 2 !=
                piles_[positionsCiblee[0]]->getCarte(piles_[positionsCiblee[0]]->getTaille() - 1)->getCouleur() %
                2 && pileDeplacement->getCarte(0)->getHauteur() == piles_[positionsCiblee[0]]->getCarte(
                    piles_[positionsCiblee[0]]->getTaille() - 1)->getHauteur() - 1) {
                // condition 1 : les couleurs sont oppsées
                // condition 2 : les hauteurs se suivent dans le bon ordre
                return true;
            } else { return false; }
        }
        if (piles_[positionsCiblee[0]]->getType() >= 10 && piles_[positionsCiblee[0]]->getType() <= 13) {
            // si c'est une pile libre
            if (pileDeplacement->getTaille() == 1 && piles_[positionsCiblee[0]]->getTaille() == 0) {
                return true;
            } else {
                return false;
            }

        }
        if (piles_[positionsCiblee[0]]->getType() >= 14 && piles_[positionsCiblee[0]]->getType() <= 17) {
            // si c'est une pile valide
            if (pileDeplacement->getTaille() == 1) {
                //si pris une seul carte
                if (piles_[positionsCiblee[0]]->getTaille() == 0) {
                    // si pile valide vide alors on accepte que des as
                    if (pileDeplacement->getCarte(0)->getHauteur() == As) {
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    if (pileDeplacement->getCarte(0)->getHauteur() == piles_[positionsCiblee[0]]->getCarte(
                            piles_[positionsCiblee[0]]->getTaille() - 1)->getHauteur() + 1 &&
                        pileDeplacement->getCarte(0)->getCouleur() == piles_[positionsCiblee[0]]->getCarte(
                                piles_[positionsCiblee[0]]->getTaille() - 1)->getCouleur()) {
                        //condition 1 : les hauteurs se succèdent
                        //condition 2 : les cartes sont de meme couleur
                        return true;
                    } else {
                        return false;
                    }
                }
            } else {
                return false;
            }
        }
        return false;
    }
}

bool FenetrePrincipale::PartieEstGagnee() {
    unsigned int nombreDeCartePlacee =
            piles_[12]->getTaille() + piles_[13]->getTaille() + piles_[14]->getTaille() + piles_[15]->getTaille();
    if (nombreDeCartePlacee == 52) {
        return true;
    } else {
        return (false);
    }
}

bool FenetrePrincipale::victoireAnticipee() {
    bool fin_anticipee = pileDeplacement->getTaille() == 0;
    for (unsigned int k = 0; k < 8; k++) {
        fin_anticipee &= piles_[k]->EstTriee();
    }
    return fin_anticipee;
}

int FenetrePrincipale::trouverCarte(int id) {
    for (unsigned int k = 0; k < piles_.size() - 4; k++) {
        if (piles_[k]->trouverPosCarteId(id) != -1) {
            return (k * 100 + piles_[k]->trouverPosCarteId(id));
        }
    }
    cout << "Echec de l'algorithme : Carte non trouvée " << endl;
    return (-1);
}

void FenetrePrincipale::terminerPartie(bool postResize, Bouton &bQuitter, Bouton &bNbCoupsJoues, Bouton &bTime) {
    int limite = 100; // imposition d'une limite en cas de disfonctionnement de l'algorithme

    while (!PartieEstGagnee() && limite > 0) { // tant que l'on a pas fini la partie
        for (unsigned int k = 12; k < 16; k++) { // pour chaque pile valide
            if (piles_[k]->getTaille() != 0 && piles_[k]->getTaille() != 13) {
                int idchercher = piles_[k]->getCarte(piles_[k]->getTaille() - 1)->getIdentifiant() +
                                 1; //on recupère la carte qu'il faut
                int positions = trouverCarte(idchercher);
                int numPile = int(positions / 100); // donne la pile qui contient la carte
                int position = positions % 100;// donne la position dans la pile
                if (position == piles_[numPile]->getTaille() - 1) { // si la carte est accessible
                    if (idchercher % 13 == 0) {// si c'est un roi
                        piles_[k]->deplacerCartePileAvecPosition(12, position, piles_[numPile]);
                        nbCoupsJoues_++;
                    } else {
                        piles_[k]->deplacerCartePileAvecPosition((idchercher % 13) - 1, position,
                                                                 piles_[numPile]); // on deplace la carte de la position calculée ci-avant vers la pile valide
                        nbCoupsJoues_++;
                    }
                }
            }
            majAffichageJeu(false, bQuitter, bNbCoupsJoues, bTime);
            attendre();
        }
        limite--;
    }
}

void FenetrePrincipale::quitterFenetre() {
    delete visu_;
    visu_ = nullptr;
    delete fond_;
    fond_ = nullptr;
}

void FenetrePrincipale::attendre() {
    disp->wait();
}

bool FenetrePrincipale::commandeFermerFenetre() {
    return disp->is_closed() || disp->is_keyESC() || disp->is_keyQ();
}

void FenetrePrincipale::supprimerPiles() {
    if (!piles_.empty()) {
        for (auto &pile : piles_) {
            delete pile;
        }
        piles_.clear();
    }
    delete pileDeplacement;
}


void FenetrePrincipale::sauverFichierSettings(int newTailleFenX, int newTailleFenY, float newCardsScale,
                                              float newButtonScale) {
    ofstream ofs("settings.txt");
    ofs << newTailleFenX << endl;
    ofs << newTailleFenY << endl;
    ofs << newCardsScale << endl;
    ofs << newButtonScale << endl;
    ofs.close();
}

