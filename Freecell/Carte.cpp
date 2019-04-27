#include "pch.h"
#include "Carte.h"


using namespace cimg_library;

Carte::Carte(int idCarte, TypeCouleur Couleur, TypeHauteur Hauteur, const char *fileName, PileCarte *pileAppartenance) {
    idCarte_ = idCarte;
    Couleur_ = Couleur;
    Hauteur_ = Hauteur;
    image_ = new CImg<unsigned char>(fileName);
    tailleX_ = image_->width();
    tailleY_ = image_->height();
    pileAppartenance_ = pileAppartenance;
    positionX_ = pileAppartenance->getPosX();
    positionY_ = pileAppartenance->getPosY();
}

Carte::Carte(Carte *CarteAcopier) : idCarte_(CarteAcopier->idCarte_), Couleur_(CarteAcopier->getCouleur()),
                                    Hauteur_(CarteAcopier->getHauteur()),
                                    tailleY_(CarteAcopier->getTailleY()), tailleX_(CarteAcopier->getTailleX()),
                                    positionX_(CarteAcopier->getPosX()), positionY_(CarteAcopier->getPosY()) {
    image_ = new CImg<unsigned char>(*CarteAcopier->getImg());
}

/*!
 *Destructeur, supprime l'image de la carte
 */
Carte::~Carte() {
    delete image_;
}

int Carte::getIdentifiant() {
    return idCarte_;
}

int Carte::getPosX() {
    return positionX_;
}

int Carte::getPosY() {
    return positionY_;
}

Carte::Carte() {

}

void Carte::resize(int tailleX, int tailleY) {
    tailleX_ = tailleX;
    tailleY_ = tailleY;
    image_->resize(tailleX, tailleY);
}

