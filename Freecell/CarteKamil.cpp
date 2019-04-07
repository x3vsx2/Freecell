#include "CarteKamil.h"

using namespace cimg_library;

CarteKamil::CarteKamil(TypeCouleur Couleur, TypeHauteur Hauteur, const char *fileName, pileCarte *pileAppartenance) {
    Couleur_ = Couleur;
    Hauteur_ = Hauteur;
    image_ = new CImg<unsigned char>(fileName);
    tailleX_ = image_->width();
    tailleX_ = image_->height();
    pileAppartenance_ = pileAppartenance;
    positionX_ = pileAppartenance->getPosX();
    positionY_ = pileAppartenance->getPosY();
}

CarteKamil::~CarteKamil() {}


int CarteKamil::getPosX() {
    return positionX_;
}

int CarteKamil::getPosY() {
    return positionY_;
}