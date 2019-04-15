#include "pch.h"
#include "PileCarte.h"
#include <algorithm>


using namespace cimg_library;

PileCarte::PileCarte() {
    taille_ = 0;
    positionY_ = 0;
    positionX_ = 0;
    type_ = unknown;
}

PileCarte::PileCarte(int positionX, int positionY, Type type) {
    taille_ = 0;
    positionX_ = positionX;
    positionY_ = positionY;
    type_ = type;
}

PileCarte::PileCarte(PileCarte &pileCopiee) : taille_(pileCopiee.taille_),
                                              positionX_(pileCopiee.positionX_), positionY_(pileCopiee.positionY_) {
    for (unsigned int i = 0; i < pileCopiee.taille_; i++) {
        listeCartes_.push_back(pileCopiee.listeCartes_[i]);
    }
}

PileCarte::~PileCarte() {
    for (unsigned int i = 0; i < taille_; i++) {
        delete listeCartes_[i];
    }
}

void PileCarte::melangerCartes() {
    //TODO fonction melanger
}

/*!
 *Deplace une carte d'une pile à une autre
 * @param pointeur vers la pile retrait
 */
void PileCarte::deplacerCartePile(PileCarte *pileRetrait) {
    //Quand la carte est ajoutée dans une pile sa coordonée en X est celle de la pile, sa coordonnée en Y est celle de
    //la pile multipliée par le nombre de carte dans la pilex20
    if (pileRetrait->getTaille() == 0) { std::cout << "pile vide"; }
    pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPosX(this->getPosX());
    pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPosY(this->getPosY() + this->listeCartes_.size() * 20);

    //Ajout de la carte dans sa nouvelle pile
    this->ajouterCarte(pileRetrait->getCarte(pileRetrait->taille_ - 1));

    //Suppresion de la carte de son ancienne pile
    pileRetrait->listeCartes_.pop_back();
    pileRetrait->taille_--;
}

/*!
 * Change les attributs positions d'une carte
 * @param x position horizontale de la souris
 * @param y position verticale
 */
void PileCarte::changerPositionPile(int x, int y) {
    this->setPosX(x);
    this->setPosY(y);
    for (unsigned int i = 0; i < listeCartes_.size(); i++) {
        listeCartes_[i]->setPosX(this->getPosX());
        listeCartes_[i]->setPosY(this->getPosY() + 20 * i);
    }
}

/*!
 * Change les attributs positions d'une carte
 * @param posX position horizontale
 */
void PileCarte::setPosX(int posX) {
    positionX_ = posX;
}

/*!
 * Change les attributs positions d'une carte
 * @param posY position verticale de la souris
 */
void PileCarte::setPosY(int posY) {
    positionY_ = posY;
}

/*!
 * Renvoie -1 si la souris n'est sur aucune carte
 * Sinon renvoie la position de la carte
 * @param mx position horizontale de la souris
 * @param my position verticale de la souris
 */
int PileCarte::testClicCarte(int mx, int my) {
    int position = -1;
    for (int i = listeCartes_.size() - 1; i >= 0; i--) {
        int imgX1 = listeCartes_[i]->getPosX();
        int imgX2 = listeCartes_[i]->getPosX() + listeCartes_[i]->getTailleX();
        int imgY1 = listeCartes_[i]->getPosY();
        int imgY2 = listeCartes_[i]->getPosY() + listeCartes_[i]->getTailleY();

        if (mx >= imgX1 && mx <= imgX2 && my >= imgY1 && my <= imgY2) {
            position = i;
            break;
        }
    }
    return position;
}

/*!
 * Inverse l'ordre des éléments dans la liste de carte
 */
void PileCarte::inverserListeCartes() {
    std::reverse(listeCartes_.begin(), listeCartes_.end());
}

/*!
 * Ajoute une carte dans une liste
 * @param *carte pointeur sur la carte que l'on veut inclure dans une pile
 */
void PileCarte::ajouterCarte(Carte *carte) {
    listeCartes_.push_back(carte);
    taille_ = listeCartes_.size();
}
