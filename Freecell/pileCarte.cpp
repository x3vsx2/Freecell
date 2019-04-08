#include "pileCarte.h"

using namespace cimg_library;

pileCarte::pileCarte() {
    taille_ = 0;
    positionY_ = 0;
    positionX_ = 0;
}

pileCarte::pileCarte(int positionX, int positionY) {
    taille_ = 0;
    positionX_ = positionX;
    positionY_ = positionY;
}

void pileCarte::ajouterCarte(CarteKamil *carte) {
    int test = carte->getPosX();
    listeCartes_.push_back(carte);
    taille_ = listeCartes_.size();
}

void pileCarte::melangerCartes() {
    //TODO fonction melanger
}

void pileCarte::deplacerCartePile(pileCarte *pileRetrait) {
    //Quand la carte est ajoutée dans une pile sa coordonée en X est celle de la pile, sa coordonnée en Y est celle de
    //la pile multipliée par le nombre de carte dans la pilex20
    pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPosX(this->getPosX());
    pileRetrait->getCarte(pileRetrait->taille_ - 1)->setPosY(this->getPosY() + this->listeCartes_.size() * 20);
    this->ajouterCarte(pileRetrait->getCarte(pileRetrait->taille_ - 1));
    pileRetrait->listeCartes_.pop_back();
    pileRetrait->taille_--;

}

void pileCarte::deplacerPile(int x, int y) {
    this->setPosX(x);
    this->setPosY(y);
    for(unsigned int i = 0; i<listeCartes_.size();i++){
        listeCartes_[i]->setPosX(this->getPosX());
        listeCartes_[i]->setPosY(this->getPosY() + 20*i);
    }
}

void pileCarte::setPosX(int posX) {
    positionX_ = posX;
}

void pileCarte::setPosY(int posY){
    positionY_ = posY;
}

CarteKamil* pileCarte::retournerCartePlusProche(int mx, int my) {
    CarteKamil *temp;
    double distX = 1000;
    double distY = 1000;

    for(unsigned int i = 0; i < listeCartes_.size(); i++){
        if((abs(mx - listeCartes_[i]->getPosX()) < abs(distX)) && ((abs(my - listeCartes_[i]->getPosY()) < abs(distY)))){
            temp = listeCartes_[i];
            distX = abs(mx - temp->getPosX());
            distY = abs(mx - temp->getPosY());

        }
    }
    return temp;
}
