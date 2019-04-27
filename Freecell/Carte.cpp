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
    charger(image_, fileName, Channels::RGBA);
    tailleX_ = image_.width() * factorScale;
    tailleY_ = image_.height() * factorScale;
    image_.resize(tailleX_, tailleY_);
    CImg<unsigned char> render(image_.width(), image_.height(), couleurFond[0], couleurFond[1], couleurFond[2]);
    cimg_forXY(render, x, y)
    {
        //Rouge
        render(x, y, 0, 0) = couleurFond[0];
        //Vert
        render(x, y, 0, 1) = couleurFond[1];
        //Bleu
        render(x, y, 0, 2) = couleurFond[2];

    }
    render.draw_image(0, 0, 0, 0, image_, image_.get_channel(3), 1, 255);
    image_ = render;
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

void Carte::resize(int tailleX, int tailleY) {
    tailleX_ = tailleX;
    tailleY_ = tailleY;
    image_.resize(tailleX, tailleY);
}

void Carte::dessinerCarte(cimg_library::CImg<unsigned char> *visu) {

    visu->draw_image(this->getPosX(), this->getPosY(), image_);
}

