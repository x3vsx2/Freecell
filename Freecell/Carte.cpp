#include "pch.h"
#include "Carte.h"
#include "Couleurs.h"
#include "Bouton.h"
#include "stb_implement.h"

using namespace cimg_library;

Carte::Carte(int idCarte, TypeCouleur Couleur, TypeHauteur Hauteur, const char *fileName, PileCarte *pileAppartenance,
             float factorScale) {
    idCarte_ = idCarte;
    Couleur_ = Couleur;
    Hauteur_ = Hauteur;
    image_ = CImg<unsigned char>(fileName);
    image_ = image_.get_crop(1, 1, 0, 222, 323, 0, 0);
    tailleX_ = image_.width() * factorScale;
    tailleY_ = image_.height() * factorScale;
    image_.resize(tailleX_, tailleY_, 1, 3);
    image_.draw_rectangle(0, 0, tailleX_, tailleY_, couleurBordureCartes, 1, ~0U);
    pileAppartenance_ = pileAppartenance;
    positionX_ = pileAppartenance->getPosX();
    positionY_ = pileAppartenance->getPosY();
}


Carte::Carte(Carte *CarteAcopier) : idCarte_(CarteAcopier->idCarte_), Couleur_(CarteAcopier->getCouleur()),
                                    Hauteur_(CarteAcopier->getHauteur()),
                                    tailleY_(CarteAcopier->getTailleY()), tailleX_(CarteAcopier->getTailleX()),
                                    positionX_(CarteAcopier->getPosX()), positionY_(CarteAcopier->getPosY()) {
    image_ * CarteAcopier->getImg();
}

/*!
 *Destructeur, supprime l'image de la carte
 */
Carte::~Carte() {
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

void Carte::dessinerCarte(cimg_library::CImg<unsigned char> *visu) {
    visu->draw_image(this->getPosX(), this->getPosY(), image_);
}

