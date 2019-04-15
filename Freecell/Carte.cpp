#include "pch.h"
#include "Carte.h"


using namespace cimg_library;

Carte::Carte(TypeCouleur Couleur, TypeHauteur Hauteur, const char *fileName, pileCarte *pileAppartenance) {
    Couleur_ = Couleur;
    Hauteur_ = Hauteur;
    image_ = new CImg<unsigned char>(fileName);
    tailleX_ = image_->width();
    tailleY_ = image_->height();
    pileAppartenance_ = pileAppartenance;
    positionX_ = pileAppartenance->getPosX();
    positionY_ = pileAppartenance->getPosY();
}

Carte::~Carte() {}


int Carte::getPosX() {
    return positionX_;
}

int Carte::getPosY() {
    return positionY_;
}

Carte::Carte() {

}

