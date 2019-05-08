#include "pch.h"
#include "Carte.h"
#include "Couleurs.h"
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
    OriginalTailleX_ = static_cast<int>(image_.width() * factorScale);
    OriginalTailleY_ = static_cast<int>(image_.height() * factorScale);
    tailleX_ = static_cast<int>(OriginalTailleX_ * coeffX);
    tailleY_ = static_cast<int>(OriginalTailleY_ * coeffY);
    image_.resize(tailleX_, tailleY_, 1, 3);
    pileAppartenance_ = pileAppartenance;
    positionX_ = pileAppartenance->getPosX();
    positionY_ = pileAppartenance->getPosY();
}

Carte::~Carte() {
    pileAppartenance_ = nullptr;
}

int Carte::getIdentifiant() {
    return idCarte_;
}

void Carte::dessinerCarte(cimg_library::CImg<unsigned char> *visu) {
    visu->draw_image(this->getPosX(), this->getPosY(), image_);
    image_.draw_rectangle(0, 0, tailleX_, tailleY_, couleurBordureCartes, 1, ~0U);
}

void Carte::reload(float coeffX, float coeffY) {
    charger(image_, chemin, Channels::RGBA);
    setTailleX(static_cast<int>(OriginalTailleX_ * coeffX));
    setTailleY(static_cast<int>(OriginalTailleY_ * coeffY));
    image_.resize(tailleX_, tailleY_);
}

Carte::Carte() = default;

