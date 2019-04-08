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

int pileCarte::testClicCarte(int mx, int my) {
    int position = -1;
    for(int i = listeCartes_.size()-1; i >=0; i--){
        std::cout<<i;
        int imgX1 = listeCartes_[i]->getPosX();
        int imgX2 = listeCartes_[i]->getPosX() + listeCartes_[i]->getTailleX();
        int imgY1 = listeCartes_[i]->getPosY();
        int imgY2 = listeCartes_[i]->getPosY() + listeCartes_[i]->getTailleY();

        if(mx >= imgX1 && mx <= imgX2 && my >= imgY1 && my <= imgY2){
            position = i;
            break;
        }
        else{
            position =-1;
        }
    }
    return position;
}
