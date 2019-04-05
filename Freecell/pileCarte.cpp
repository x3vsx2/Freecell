#include "pileCarte.h"

using namespace cimg_library;

pileCarte::pileCarte() {
    taille_ = 0;
    listeCartes = new std::vector<CarteKamil>();
    positionY_ = 100;
}

pileCarte::pileCarte(int positionX, int positionY) {
    taille_ = 0;
    listeCartes = new std::vector<CarteKamil>();
    positionX_ = positionX;
    positionY_ = positionY;
}

void pileCarte::ajouterCarte(CarteKamil carte) {
    listeCartes->push_back(carte);
    taille_ = listeCartes->size();
}

void pileCarte::melangerCartes() {
    //TODO fonction melanger
}

void pileCarte::deplacerCartePile(pileCarte *pileRetrait) {
    CarteKamil temp = (*pileRetrait->listeCartes)[(*pileRetrait->listeCartes).size() - 1];
    this->ajouterCarte(temp);
    pileRetrait->listeCartes->pop_back();
    pileRetrait->taille_--;
}