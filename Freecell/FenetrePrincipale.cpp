//
// Created by kamilcaglar on 02/04/19.
//

#include"pch.h"
#include "FenetrePrincipale.h"

using namespace std;
using namespace cimg_library;

/*!
 * Constructeur qui initialise le display
 */
FenetrePrincipale::FenetrePrincipale(int tailleFenX, int tailleFenY, float factorScaleCards, float factorScaleButtons)
        : tableauxIdentifiants(16, vector<int>(0)), tailleFenX_(tailleFenX), tailleFenY_(tailleFenY),
          facteurEchelleCartes_(factorScaleCards), facteurEchelleBoutons_(factorScaleButtons), coeffX_(1), coeffY_(1),
          nbCoupsJoues_(0) {
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

/*!
 *Renvoie un vecteur avec le numero de la pile suivie du numéro de la carte selon la position du ponteur de la souris
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 * @return vector<int> numero pile et numero carte
 */
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
        int pileX2 = piles_[i]->getPosX() + 74;
        int pileY1 = piles_[i]->getPosY();
        int pileY2 = piles_[i]->getPosY() + 99;
        if (mx >= pileX1 && mx <= pileX2 && my >= pileY1 && my <= pileY2) {
            positions[0] = i;
            positions[1] = -2;
            return positions;
        }
    }
    return positions;
}

/*!
 * Initialise les piles et répartie les cartes entre les différentes piles
 */
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
            for (unsigned int j = 0; j < tableauxIdentifiants[i].size(); j++) {
                int idAchercher = tableauxIdentifiants[i][j];
                if (idAchercher == 0) {
                    break;
                }
                int posPileMelange = -1;
                //On regarde dans la pile Melange pour trouver sa position
                posPileMelange = pileMelange->trouverPosCarteId(idAchercher);
                piles_[i]->deplacerCartePileAvecPosition(piles_[i]->getTaille(), posPileMelange, pileMelange);
                etatChargement();
            }
        }
    }

    delete pileMelange;
}

bool FenetrePrincipale::estSaisieValide(int mx, int my) {

    vector<int> positionsCartecliquee = getClicPositions(mx, my);
    //On verifie si on a clique sur une pile qui serait vide, c'est à dire qu'il n'y a plus de cartes dedans
    //Laisser ce test en PREMIER, sinon on cherche à accéder à des éléments non existants
    if (positionsCartecliquee[0] == -1 || positionsCartecliquee[0]>11)return false;
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
        }// si il y a une seul carte return true
        else {
            bool validite = true;
            for (unsigned int k = piles_[positionsCartecliquee[0]]->getTaille() - 1;
                 k > positionsCartecliquee[1]; k--) {
                validite &= piles_[positionsCartecliquee[0]]->precedentEstValide(k);
            }
            return (validite);
        }
    }
    return false;
}

/*!
* Renvoie si le depot de cartes à l'emplacement indiqué par mx my est valide
* @param mx position horizontale de la souris
* @param my position verticale de la souris
*@return bool
*/
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

/*!
* Renvoie si le joueur à remporter la partie
* @return bool
*/
bool FenetrePrincipale::PartieEstGagnee() {
    //TODO : faire le calcule nombre de carte placee
    unsigned int nombreDeCartePlacee =
            piles_[12]->getTaille() + piles_[13]->getTaille() + piles_[14]->getTaille() + piles_[15]->getTaille();
    if (nombreDeCartePlacee == 52) {
        return true;
    } else {
        return (false);
    }
}

void FenetrePrincipale::quitterFenetre() {
    delete visu_;
    visu_ = nullptr;
    delete plateau_;
    plateau_ = nullptr;
    delete fond_;
    fond_ = nullptr;
}

void FenetrePrincipale::attendre() {
    disp->wait();
}

bool FenetrePrincipale::commandeFermerFenetre() {
    if (disp->is_closed() || disp->is_keyESC() || disp->is_keyQ()) {
        return true;
    } else { return false; }
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

void FenetrePrincipale::clear_screen() {
#ifdef WINDOWS
    std::system("cls");
#else
    // Assume POSIX
    std::system("clear");
#endif
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

