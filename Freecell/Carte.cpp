#include "pch.h"
#include "Carte.h"
#include "Couleurs.h"
#include "Bouton.h"
#include "stb_implement.h"

using namespace cimg_library;

Carte::Carte(int idCarte, TypeCouleur Couleur, TypeHauteur Hauteur, const char *fileName, PileCarte *pileAppartenance,
             float factorScale, float coeffX, float coeffY) {
    idCarte_ = idCarte;
    Couleur_ = Couleur;
    Hauteur_ = Hauteur;
    chemin = (fileName);
    charger(image_, fileName, Channels::RGBA);
    //image_ = image_.get_crop(1, 1, 0, 222, 323, 0, 0);
    OriginalTailleX_ = image_.width() * factorScale;
    OriginalTailleY_ = image_.height() * factorScale;
    tailleX_ = OriginalTailleX_ * coeffX;
    tailleY_ = OriginalTailleY_ * coeffY;
    image_.resize(tailleX_, tailleY_, 1, 3);
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
    image_.draw_rectangle(0, 0, tailleX_, tailleY_, couleurBordureCartes, 1, ~0U);
}


void Carte::reload(float coeffX, float coeffY) {
    charger(image_, chemin, Channels::RGBA);
    setTailleX(OriginalTailleX_ * coeffX);
    setTailleY(OriginalTailleY_ * coeffY);
    image_.resize(tailleX_, tailleY_);
}

